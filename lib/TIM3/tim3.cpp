#include "defines.hpp"
#include "tim3.hpp"

volatile uint32_t ms_ticks = 0;

static void tim3_trgo_init(void)
{
  RCC_APB1ENR |= (1 << 1);
  TIM3_CR1 = 0;
  TIM3_PSC = 7199; // 72 MHz -> 10 kHz
  TIM3_ARR = 49;   // 10 kHz / 50 = 200 Hz
  TIM3_EGR = 1;    // UG
  TIM3_DIER |= (1 << 0);
  TIM3_CR2 &= ~(7 << 4);
  TIM3_CR2 |= (2 << 4); // MMS=010: Update -> TRGO
  TIM3_CR1 |= 1;        // CEN
}

void TIM3_IRQHandler(void)
{
  if (TIM3_SR & 0x1)
  {
    TIM3_SR &= ~0x1;
    ms_ticks++;
  }
}

uint32_t millis(void)
{
  return ms_ticks;
}