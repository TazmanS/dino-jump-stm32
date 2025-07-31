#include "main.h"

int main(void)
{
  i2c1_init();
  delay_ms(10);
  lcd_init();
  delay_ms(10);
  lcd_send_string("Hello, World123");

  while (1)
  {
  }
}

// #include "FreeRTOS.h"
// #include "task.h"

// #define RCC_AHBENR (*(volatile uint32_t *)0x40021014)
// #define GPIOA_MODER (*(volatile uint32_t *)0x48000000)
// #define GPIOB_MODER (*(volatile uint32_t *)0x48000400)

// #define GPIOA_ODR (*(volatile uint32_t *)0x48000014)

// #define PIN_A5 5

// void vTaskBlink(void *params)
// {
//   while (1)
//   {
//     GPIOA_ODR &= ~(1 << PIN_A5);
//     vTaskDelay(pdMS_TO_TICKS(100));

//     GPIOA_ODR |= (1 << PIN_A5);
//     vTaskDelay(pdMS_TO_TICKS(100));
//   }
// }

// int main(void)
// {
//   RCC_AHBENR |= (1 << 17);

//   GPIOA_MODER &= ~(0b11 << (PIN_A5 * 2));
//   GPIOA_MODER |= (0b01 << (PIN_A5 * 2));

//   xTaskCreate(vTaskBlink, "blink", 128, NULL, 1, NULL);
//   vTaskStartScheduler();
//   while (1)
//     ;
// }