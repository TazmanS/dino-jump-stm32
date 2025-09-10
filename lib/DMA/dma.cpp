#include "defines.hpp"

volatile uint16_t adc_buf[2]; // [0]=PA0/CH1, [1]=PA1/CH2

void dma_for_adc_init()
{
  RCC_AHBENR |= (1 << 0); // ВКЛЮЧИЛИ DMA1 тактирование
  DMA1_CCR1 &= ~1u;       // EN=0
  DMA1_CPAR1 = (uint32_t)&ADC1_DR;
  DMA1_CMAR1 = (uint32_t)adc_buf;
  DMA1_CNDTR1 = 2;

  // PL=10 (High), MSIZE=01 (16b), PSIZE=01 (16b), MINC=1, CIRC=1, DIR=0
  DMA1_CCR1 = (2u << 12) | (1u << 10) | (1u << 8) | (1u << 7) | (1u << 5);
  // PINC=0 по умолчанию
}