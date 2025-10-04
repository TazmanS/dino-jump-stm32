#include "defines.hpp"
#include "tim3.hpp"

volatile uint32_t ms_ticks = 0;

void tim3_trgo_init(void)
{
  RCC_APB1ENR |= (1 << 1); // TIM3EN

  TIM3_CR1 = 0;
  TIM3_PSC = 7199; // 72 MHz / (7199+1) = 10 kHz
  TIM3_ARR = 49;   // 10 kHz / (49+1) = 200 Hz
  TIM3_EGR = 1;
  // TRGO = Update
  TIM3_CR2 &= ~(7u << 4);
  TIM3_CR2 |= (2u << 4); // MMS=010

  TIM3_CNT = 0;
  TIM3_EGR = 1; // UG

  TIM3_CR1 |= 1; // CEN
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