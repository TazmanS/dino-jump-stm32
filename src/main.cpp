#include "lcd.hpp"
#include "i2c1.hpp"
#include "delay.hpp"
#include "interrupts.hpp"
#include "joystick.hpp"
#include "usart.hpp"

#include "defines.hpp"

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
  joystick_adc_dma_init();
  usart_init();
}

int main(void)
{
  // RCC_AHBENR |= (1 << 17);

  // GPIOA_MODER &= ~(0b11 << (5 * 2));
  // GPIOA_MODER |= (0b01 << (5 * 2));

  // GPIOA_ODR |= (1 << 5);
  init();

  display_print("Hello Worlds");
  usart_send_str("Terminal ready\r\n");

  // xTaskCreate((TaskFunction_t)vTaskMenu, "menu", 128, NULL, 1, NULL);
  // vTaskStartScheduler();

  while (1)
  {
  }
}
