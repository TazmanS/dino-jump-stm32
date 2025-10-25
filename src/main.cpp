#include "lcd.hpp"
#include "i2c1.hpp"
#include "delay.hpp"
#include "interrupts.hpp"
#include "joystick.hpp"
#include "usart.hpp"
#include "components/DinoJump/dino-jump.hpp"

#include "defines.hpp"

#include "FreeRTOS.h"
#include "task.h"

#include "dma.hpp"
#include <stdio.h>

void vTaskMenu(void *pvParameters)
{
  (void)pvParameters;

  while (1)
  {
    uint16_t adc_x = adc_get_x();
    uint16_t adc_y = adc_get_y();

    dino_jump.calculateMovement(adc_x, adc_y);

    vTaskDelay(pdMS_TO_TICKS(50));
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
  // display_print("Hello Worlds");

  dino_jump.start();

  xTaskCreate((TaskFunction_t)vTaskMenu, "menu", 128, NULL, 1, NULL);
  vTaskStartScheduler();

  while (1)
  {
    // char buf[16];
    // uint16_t val = adc_get_x();
    // sprintf(buf, "%u\r\n", val);
    // usart_send_str(buf);

    // for (volatile int i = 0; i < 500000; i++)
    //   __asm volatile("nop");
  }
}