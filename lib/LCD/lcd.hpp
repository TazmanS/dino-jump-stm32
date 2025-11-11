#pragma once

#include <stdint.h>

void lcd_init();
void display_print(const char *str);
void display_clear();
void lcd_send_data(uint8_t data);
void lcd_send_cmd(uint8_t cmd);
void lcd_write(uint8_t data, uint8_t rs);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_write_char_at(uint8_t row, uint8_t col, uint8_t ch);
void display_print_mix(const char *str);
void display_uint(uint16_t value);

const uint8_t HEART_INDEX = 0;
const uint8_t DINO_INDEX = 1;
const uint8_t DINO_STEP_INDEX = 2;