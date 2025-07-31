#ifndef __LCD_H__
#define __LCD_H__

#include "defines.h"
#include "i2c1.h"
#include "delay.h"

void lcd_init();
void lcd_send_string(const char *str);
void lcd_send_data(uint8_t data);
void lcd_send_cmd(uint8_t cmd);
void lcd_write(uint8_t data, uint8_t rs);

#endif