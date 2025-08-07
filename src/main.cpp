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

const uint8_t menuLength = sizeof(menuItems) / sizeof(menuItems[0]);
volatile uint8_t menuIndex = 0;

void initLCDandI2C1()
{
  i2c1_init();
  delay_ms(10);
  lcd_init();
  delay_ms(10);
}

void EXTI0_IRQHandler() // up
{

  if (EXTI_PR & (1 << BUTTON_UP))
  {
    EXTI_PR |= (1 << BUTTON_UP);
    menuIndex = (menuIndex + 1) % menuLength;
  }
}

void EXTI1_IRQHandler() // down
{
  if (EXTI_PR & (1 << BUTTON_DOWN))
  {
    EXTI_PR |= (1 << BUTTON_DOWN);
    if (menuIndex == 0)
      menuIndex = menuLength - 1;
    else
      menuIndex--;
  }
}

void interrupt_buttons_init()
{
  RCC_AHBENR |= (1 << 17);

  GPIOA_MODER &= ~(0b11 << (BUTTON_UP * 2));
  GPIOA_MODER &= ~(0b11 << (BUTTON_DOWN * 2));

  // GPIOA_IDR |= (1 << BUTTON_UP);
  // GPIOA_IDR |= (1 << BUTTON_DOWN);

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
  interrupt_buttons_init();
  display_print(menuItems[menuIndex]);

  xTaskCreate((TaskFunction_t)vTaskMenu, "menu", 128, NULL, 1, NULL);
  vTaskStartScheduler();

  while (1)
  {
  }
}