#include "lcd.hpp"
#include "i2c1.hpp"
#include "delay.hpp"
#include "interrupts.hpp"
#include "joystick.hpp"
#include "usart.hpp"
#include "components/Screen/screen.hpp"

#include "defines.hpp"

#include "FreeRTOS.h"
#include "task.h"

#include "dma.hpp"
#include <stdio.h>

void vTaskMenu(void *pvParameters)
{
  (void)pvParameters;

  static bool wasPressed = false;
  while (1)
  {
    uint16_t adc_x = adc_get_x();

    if ((adc_x > 3000) & !wasPressed)
    {
      screen.next();

      wasPressed = true;
    }
    else if ((adc_x < 500) & !wasPressed)
    {
      screen.prev();

      wasPressed = true;
    }
    else if ((adc_x < 2500) & (adc_x > 1500))
    {
      wasPressed = false;
    }

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

void init()
{
  usart_init();
  i2c1_init();
  delay_ms(10);
  lcd_init();
  delay_ms(10);

  // interruptors_config();
  joystick_adc_dma_init();
}

int main(void)
{
  init();

  usart_send_str("Terminal ready\r\n");
  // display_print("Hello Worlds1");

  screen.render();

  xTaskCreate((TaskFunction_t)vTaskMenu, "menu", 128, NULL, 1, NULL);
  vTaskStartScheduler();

  while (1)
  {
  }
}

// char buf[16];
// uint16_t val = adc_get_x();
// sprintf(buf, "%u\r\n", val);
// usart_send_str(buf);