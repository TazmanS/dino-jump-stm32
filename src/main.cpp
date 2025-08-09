#include "main.h"

#include "FreeRTOS.h"
#include "task.h"

#include <string>

const char *menuItems[] = {
    "Start",
    "Settings",
    "About"};

#define BUTTON_UP 0   // Button pin (PA0)
#define BUTTON_DOWN 1 // Button pin (PA1)

#define LED_PIN 5

const uint8_t menuLength = sizeof(menuItems) / sizeof(menuItems[0]);
volatile uint8_t menuIndex = 1;

void initLCDandI2C1()
{
  i2c1_init();
  delay_ms(10);
  lcd_init();
  delay_ms(10);
}

extern "C" void EXTI0_IRQHandler() // up
{
  if (EXTI_PR & (1 << BUTTON_UP))
  {
    GPIOA_ODR &= ~(1 << LED_PIN);
    EXTI_PR |= (1 << BUTTON_UP);
    menuIndex = (menuIndex + 1) % menuLength;

    display_clear();
    display_print(menuItems[menuIndex]);
  }
}

extern "C" void EXTI1_IRQHandler() // down
{
  if (EXTI_PR & (1 << BUTTON_DOWN))
  {
    GPIOA_ODR &= ~(1 << LED_PIN);
    EXTI_PR |= (1 << BUTTON_DOWN);
    if (menuIndex == 0)
      menuIndex = menuLength - 1;
    else
      menuIndex--;

    display_clear();
    display_print(menuItems[menuIndex]);
  }
}

void interruptors_config(void)
{
  RCC_AHBENR |= (1 << 17);

  GPIOA_MODER &= ~(0b11 << (BUTTON_UP * 2));
  GPIOA_MODER &= ~(0b11 << (BUTTON_DOWN * 2));

  GPIOA_IDR |= (1 << BUTTON_UP);
  GPIOA_IDR |= (1 << BUTTON_DOWN);

  EXTI_IMR |= (1 << BUTTON_UP);
  EXTI_FTSR |= (1 << BUTTON_UP);

  EXTI_IMR |= (1 << BUTTON_DOWN);
  EXTI_FTSR |= (1 << BUTTON_DOWN);

  NVIC_ISER0 |= (1 << 6);
  NVIC_ISER0 |= (1 << 7);
}

void vTaskMenu()
{
  while (1)
  {
    display_clear();
    display_print(menuItems[menuIndex]);
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

int main(void)
{

  initLCDandI2C1();

  display_print(menuItems[menuIndex]);

  RCC_AHBENR |= (1 << 17);

  GPIOA_MODER &= ~(0b11 << (LED_PIN * 2));
  GPIOA_MODER |= (0b01 << (LED_PIN * 2));

  GPIOA_ODR |= (1 << LED_PIN);

  interruptors_config();

  // xTaskCreate((TaskFunction_t)vTaskMenu, "menu", 128, NULL, 1, NULL);
  // vTaskStartScheduler();

  while (1)
  {
  }
}
