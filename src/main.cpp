#include "lcd.hpp"
#include "i2c1.hpp"
#include "delay.hpp"
#include "interrupts.hpp"

#include "FreeRTOS.h"
#include "task.h"

void vTaskMenu()
{
  while (1)
  {

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void init()
{
  i2c1_init();
  delay_ms(10);
  lcd_init();
  delay_ms(10);

  interruptors_config();
}

int main(void)
{
  init();

  display_print("Hello Worlds");

  // xTaskCreate((TaskFunction_t)vTaskMenu, "menu", 128, NULL, 1, NULL);
  // vTaskStartScheduler();

  while (1)
  {
  }
}
