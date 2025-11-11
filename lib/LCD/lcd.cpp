#include "lcd.hpp"
#include "defines.hpp"
#include "i2c1.hpp"
#include "delay.hpp"

#include "custom.cpp" // custom characters

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

void lcd_set_cursor(uint8_t row, uint8_t col)
{
  uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
  lcd_send_cmd(addr);
}

void lcd_write_char_at(uint8_t row, uint8_t col, uint8_t ch)
{
  lcd_set_cursor(row, col);
  lcd_send_data(ch);
}

// "Player \x00 ready!"
void display_print_mix(const char *str)
{
  while (*str)
    lcd_send_data(*str++);
}

void lcd_create_char(uint8_t index, const uint8_t pixels[8][5]) // register custom char
{
  if (index > 7)
    return;
  lcd_send_cmd(0x40 | (index << 3));
  for (int i = 0; i < 8; i++)
  {
    uint8_t row = 0;
    for (int j = 0; j < 5; j++)
      row |= (pixels[i][j] << (4 - j));
    lcd_send_data(row);
  }
}

void display_uint(uint16_t value)
{
  char buf[6];
  int i = 0;
  if (value == 0)
  {
    buf[i++] = '0';
  }
  else
  {
    while (value > 0 && i < 5)
    {
      buf[i++] = (value % 10) + '0';
      value /= 10;
    }
  }
  buf[i] = '\0';

  for (int j = i - 1; j >= 0; j--)
    lcd_send_data(buf[j]);
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

  lcd_create_char(HEART_INDEX, heart);
  lcd_create_char(DINO_INDEX, dino);
  lcd_create_char(DINO_STEP_INDEX, dino_step);
}