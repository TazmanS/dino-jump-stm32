#include "defines.hpp"
#include "adc.hpp"
#include "tim3.hpp"
#include "dma.hpp"

void joystick_adc_dma_init(void)
{
  adc_gpio_init();
  tim3_trgo_init();
  dma_for_adc_init();
  adc1_init_scan_dma_trgo();
}
