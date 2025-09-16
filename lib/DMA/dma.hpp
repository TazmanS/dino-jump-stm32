#pragma once

#include <stdint.h>

void dma_for_adc_init();
void adc_get_xy(uint16_t *x, uint16_t *y);
uint16_t adc_get_x(void);
uint16_t adc_get_y(void);