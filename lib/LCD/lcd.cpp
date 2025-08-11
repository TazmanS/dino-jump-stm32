#include "lcd.hpp"
#include "defines.hpp"
#include "i2c1.hpp"
#include "delay.hpp"

void lcd_write(uint8_t data, uint8_t rs)
{
  uint8_t high = data & 0xF0;
  uint8_t low = (data << 4) & 0xF0;
  uint8_t ctrl = rs ? 0x01 : 0x00;

  uint8_t out[4] = {
      static_cast<uint8_t>(high | 0x08 | ctrl | 0x04),
      static_cast<uint8_t>(high | 0x08 | ctrl),
      static_cast<uint8_t>(low | 0x08 | ctrl | 0x04),
      static_cast<uint8_t>(low | 0x08 | ctrl)};

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

void display_print(const char *str)
{
  while (*str)
    lcd_send_data(*str++);
}

void display_clear()
{
  lcd_write(0x01, 0);
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
  display_clear();    // reset
  delay_ms(2);
  lcd_send_cmd(0x06); // cursor right
  lcd_send_cmd(0x0C); // LCD on, cursor off.
}