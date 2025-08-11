#pragma once

#include <stdint.h>

void lcd_init();
void display_print(const char *str);
void display_clear();
void lcd_send_data(uint8_t data);
void lcd_send_cmd(uint8_t cmd);
void lcd_write(uint8_t data, uint8_t rs);
