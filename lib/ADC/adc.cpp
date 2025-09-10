#include "defines.hpp"

// ADC_CR bits/fields
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

  // (опц.) Тактирование ADC от AHB/синхронно: CKMODE=01
  // ADC12_CCR = (ADC12_CCR & ~(3u << 16)) | (1u << 16);

  // Отключить ADC если был включён
  if (ADC1_CR & ADC_CR_ADEN)
  {
    ADC1_CR |= ADC_CR_ADDIS;
    while (ADC1_CR & ADC_CR_ADEN)
    {
    }
  }

  // Включение регулятора: ADVREGEN=0b01 -> задержка -> 0b11
  ADC1_CR = (ADC1_CR & ~ADC_CR_ADVREGEN_Msk) | (1u << ADC_CR_ADVREGEN_Pos);
  for (volatile int i = 0; i < 1000; i++)
    __asm volatile("nop");
  ADC1_CR = (ADC1_CR & ~ADC_CR_ADVREGEN_Msk) | (3u << ADC_CR_ADVREGEN_Pos);
  for (volatile int i = 0; i < 1000; i++)
    __asm volatile("nop");

  // Калибровка
  ADC1_CR |= ADC_CR_ADCAL;
  while (ADC1_CR & ADC_CR_ADCAL)
  {
  }

  // SMPR: CH1 и CH2, 19.5 циклов (001)
  const uint32_t SMP_19_5 = 0b001;
  ADC1_SMPR1 &= ~((7 << 3) | (7u << 6));
  ADC1_SMPR1 |= ((SMP_19_5 << 3) | (SMP_19_5 << 6));

  // SQR1: L=1 (2 конверсии), SQ1=1 (CH1), SQ2=2 (CH2)
  ADC1_SQR1 = 0;
  ADC1_SQR1 |= 1;         // L=1 → 2 conversions
  ADC1_SQR1 |= (1 << 6);  // SQ1 = 1
  ADC1_SQR1 |= (2 << 12); // SQ2 = 2

  // CFGR: DMAEN, DMACFG, EXTSEL=TIM3_TRGO(0100), EXTEN=01 (rising)
  ADC1_CFGR = 0;
  ADC1_CFGR |= (1 << 0) | (1 << 1); // DMAEN, DMACFG
  ADC1_CFGR |= (4 << 6);            // EXTSEL = 0100 (TIM3 TRGO)
  ADC1_CFGR |= (1 << 10);           // EXTEN = 01 (rising)

  // Включить ADC и дождаться ADRDY
  ADC1_CR |= ADC_CR_ADEN;
  while (!(ADC1_ISR & ADC_ISR_ADRDY))
  {
  }

  // Запустить DMA
  DMA1_CCR1 |= 1; // EN
}