#include "defines.hpp"
#include "dma.hpp"

__attribute__((aligned(4))) volatile uint16_t adc_buf[2]; // [0]=PA0/CH1, [1]=PA1/CH2

void dma_for_adc_init()
{
  RCC_AHBENR |= (1 << 0);
  DMA1_CCR1 &= ~1u;
  DMA1_CPAR1 = (uint32_t)&ADC1_DR;
  DMA1_CMAR1 = (uint32_t)adc_buf;
  DMA1_CNDTR1 = 2;

  DMA1_CCR1 = (2u << 12) | (1u << 10) | (1u << 8) | (1u << 7) | (1u << 5);

  DMA1_CCR1 |= 1u;
}

uint16_t adc_get_x(void)
{
  uint16_t v = adc_buf[0];
  return v;
}

uint16_t adc_get_y(void)
{
  uint16_t v = adc_buf[1];
  return v;
}

void adc_get_xy(uint16_t *x, uint16_t *y)
{
  if (!x || !y)
    return;

  uint16_t x1, y1, x2, y2;
  for (int i = 0; i < 4; ++i)
  {
    x1 = adc_buf[0];
    y1 = adc_buf[1];
    x2 = adc_buf[0];
    y2 = adc_buf[1];
    if (x1 == x2 && y1 == y2)
    {
      *x = x1;
      *y = y1;
      return;
    }
  }

  *x = x2;
  *y = y2;
}