#include "defines.hpp"
#include "dma.hpp"

__attribute__((aligned(4))) volatile uint16_t adc_buf[2]; // [0]=PA0/CH1, [1]=PA1/CH2

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

// X = канал 0 (PA0/CH1)
uint16_t adc_get_x(void)
{
  uint16_t v = adc_buf[0]; // читаем в локальную (снимаем одно чтение volatile)
  return v;
}

// Y = канал 1 (PA1/CH2)
uint16_t adc_get_y(void)
{
  uint16_t v = adc_buf[1];
  return v;
}

/* Согласованное чтение пары (микроснимок):
 * читаем X,Y дважды и сверяем; если совпало — считаем, что не поймали момент "разрыва".
 * Это простой способ без HT/TC прерываний.
 */
void adc_get_xy(uint16_t *x, uint16_t *y)
{
  if (!x || !y)
    return;

  uint16_t x1, y1, x2, y2;
  // Небольшое число попыток на случай, если попали в границу DMA-записи
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
  // Если так и не совпало (редко), возвращаем последние считанные
  *x = x2;
  *y = y2;
}