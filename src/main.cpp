#include "defines.h"

#define PCF8574_ADDR (0x27 << 1)

void delay_ms(uint32_t ms)
{
  for (volatile uint32_t i = 0; i < ms * 8000; i++)
    ;
}

static void i2c1_write(uint8_t data)
{
  while (!(I2C1_ISR & (1 << 1)))
    ;
  I2C1_TXDR = data;
}

static void lcd_write(uint8_t data, uint8_t rs)
{
  uint8_t high = data & 0xF0;
  uint8_t low = (data << 4) & 0xF0;
  uint8_t ctrl = rs ? 0x01 : 0x00;

  uint8_t out[4] = {
      high | 0x08 | ctrl | 0x04,
      high | 0x08 | ctrl,
      low | 0x08 | ctrl | 0x04,
      low | 0x08 | ctrl};

  I2C1_CR2 = (PCF8574_ADDR & 0xFE) | (4 << 16) | (1 << 13) | (1 << 25);

  for (int i = 0; i < 4; i++)
    i2c1_write(out[i]);

  while (!(I2C1_ISR & (1 << 5)))
    ;
  I2C1_ICR |= (1 << 5);
  delay_ms(1);
}

void lcd_send_cmd(uint8_t cmd)
{
  lcd_write(cmd, 0);
}

void lcd_send_data(uint8_t data)
{
  lcd_write(data, 1);
}

void lcd_send_string(const char *str)
{
  while (*str)
    lcd_send_data(*str++);
}

void lcd_init(void)
{
  delay_ms(50);
  lcd_send_cmd(0x30);
  delay_ms(5);
  lcd_send_cmd(0x30);
  delay_ms(1);
  lcd_send_cmd(0x30);
  delay_ms(10);
  lcd_send_cmd(0x20); // 4-bit

  lcd_send_cmd(0x28); // 2 line, 5x8
  lcd_send_cmd(0x08); // LCD off
  lcd_send_cmd(0x01); // reset
  delay_ms(2);
  lcd_send_cmd(0x06); // cursor right
  lcd_send_cmd(0x0C); // LCD on, cursor off.
}

void i2c1_init()
{
  RCC_AHBENR |= (1 << 18);
  RCC_APB1ENR |= (1 << 21);

  GPIOB_MODER &= ~((3 << (2 * SDA_PIN_PB)) | (3 << (2 * SCL_PIN_PB)));
  GPIOB_MODER |= (2 << (2 * SDA_PIN_PB)) | (2 << (2 * SCL_PIN_PB));

  GPIOB_OTYPER |= (1 << SDA_PIN_PB) | (1 << SCL_PIN_PB);
  GPIOB_OSPEEDR |= (3 << (2 * SDA_PIN_PB)) | (3 << (2 * SCL_PIN_PB));

  GPIOB_AFRH &= ~((0xF << ((SDA_PIN_PB - 8) * 4)) | (0xF << ((SCL_PIN_PB - 8) * 4)));
  GPIOB_AFRH |= (0x4 << ((SDA_PIN_PB - 8) * 4)) | (0x4 << ((SCL_PIN_PB - 8) * 4));

  GPIOB_PUPDR &= ~((3 << (2 * SDA_PIN_PB)) | (3 << (2 * SCL_PIN_PB)));
  GPIOB_PUPDR |= (1 << (2 * SDA_PIN_PB)) | (1 << (2 * SCL_PIN_PB));

  I2C1_CR1 &= ~(1 << 0); // disable
  I2C1_TIMINGR = 0x00303D5B;
  I2C1_CR1 |= (1 << 0); // enable
}

// === main ===
int main(void)
{
  i2c1_init();
  delay_ms(10);
  lcd_init();
  delay_ms(10);
  lcd_send_string("Hello, World");

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