#include "main.h"

#include "FreeRTOS.h"
#include "task.h"

#include <string>

const char *menuItems[] = {
    "Start",
    "Settings",
    "About"};

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
  menuIndex = (menuIndex + 1) % menuLength;
}

void EXTI1_IRQHandler()
{ // down
  if (menuIndex == 0)
    menuIndex = menuLength - 1;
  else
    menuIndex--;
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

  // xTaskCreate(vTaskBlink, "blink", 48, NULL, 1, NULL);
  // vTaskStartScheduler();

  while (1)
  {
  }
}