#include "delay.hpp"
#include "defines.hpp"

void delay_ms(uint32_t ms)
{
  for (volatile uint32_t i = 0; i < ms * 8000; i++)
    ;
}