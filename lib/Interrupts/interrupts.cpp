#include "interrupts.hpp"
#include "defines.hpp"

#include "components/Screen/screen.hpp"

void interruptors_config(void)
{
  RCC_AHBENR |= (1 << 17);

  GPIOA_MODER &= ~(0b11 << (BUTTON_UP * 2));
  GPIOA_MODER &= ~(0b11 << (BUTTON_DOWN * 2));

  GPIOA_IDR |= (1 << BUTTON_UP);
  GPIOA_IDR |= (1 << BUTTON_DOWN);

  EXTI_IMR |= (1 << BUTTON_UP);
  EXTI_FTSR |= (1 << BUTTON_UP);

  EXTI_IMR |= (1 << BUTTON_DOWN);
  EXTI_FTSR |= (1 << BUTTON_DOWN);

  NVIC_ISER0 |= (1 << 6);
  NVIC_ISER0 |= (1 << 7);
}

extern "C" void EXTI0_IRQHandler() // up
{
  if (EXTI_PR & (1 << BUTTON_UP))
  {
    EXTI_PR |= (1 << BUTTON_UP);
    screen.next();
  }
}

extern "C" void EXTI1_IRQHandler() // down
{
  if (EXTI_PR & (1 << BUTTON_DOWN))
  {
    EXTI_PR |= (1 << BUTTON_DOWN);
    screen.prev();
  }
}