#include "defines.hpp"

#define ADC_CR_ADEN (1 << 0)
#define ADC_CR_ADDIS (1 << 1)
#define ADC_CR_ADSTART (1 << 2)
#define ADC_CR_ADCAL (1 << 31)
#define ADC_CR_ADVREGEN_Pos 28
#define ADC_CR_ADVREGEN_Msk (3 << ADC_CR_ADVREGEN_Pos)

// ADC_ISR
#define ADC_ISR_ADRDY (1 << 0)

void adc_gpio_init(void)
{
  RCC_AHBENR |= (1 << 17);
  GPIOA_MODER |= (0b11 << (ANALOG_PIN_0 * 2)) | (0b11 << (ANALOG_PIN_1 * 2)); // PA0,PA1 analog
  GPIOA_PUPDR &= ~((0b11 << (ANALOG_PIN_0 * 2)) | (0b11 << (ANALOG_PIN_1 * 2)));
}

void adc1_init_scan_dma_trgo(void)
{
  RCC_AHBENR |= (1 << 28);
  ADC12_CCR = (ADC12_CCR & ~(3u << 16)) | (1u << 16);

  if (ADC1_CR & ADC_CR_ADEN)
  {
    ADC1_CR |= ADC_CR_ADDIS;
    while (ADC1_CR & ADC_CR_ADEN)
    {
    }
  }

  ADC1_CR = (ADC1_CR & ~ADC_CR_ADVREGEN_Msk) | (1u << ADC_CR_ADVREGEN_Pos);
  for (volatile int i = 0; i < 8000; i++)
    __asm volatile("nop");

  ADC1_CR |= ADC_CR_ADCAL;
  while (ADC1_CR & ADC_CR_ADCAL)
  {
  }

  const uint32_t SMP = 0b101;
  ADC1_SMPR1 &= ~((7u << 3) | (7u << 6));
  ADC1_SMPR1 |= ((SMP << 3) | (SMP << 6));

  ADC1_SQR1 = 0;
  ADC1_SQR1 |= 1;
  ADC1_SQR1 |= (1 << 6);
  ADC1_SQR1 |= (2 << 12);

  ADC1_CFGR = 0;
  ADC1_CFGR |= (1 << 0) | (1 << 1);
  ADC1_CFGR |= (4 << 6);
  ADC1_CFGR |= (1 << 10);

  ADC1_CR |= ADC_CR_ADEN;
  while (!(ADC1_ISR & ADC_ISR_ADRDY))
  {
  }

  ADC1_CR |= ADC_CR_ADSTART;
}