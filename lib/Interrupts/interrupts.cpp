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

static Callback first_callback = nullptr;
static Callback second_callback = nullptr;

void EXTI0_callback(Callback callback)
{
  first_callback = callback;
};

void EXTI0_callback()
{
  if (first_callback)
    first_callback();
};

void EXTI1_callback(Callback callback)
{
  second_callback = callback;
};

void EXTI1_callback()
{
  if (second_callback)
    second_callback();
};

extern "C" void EXTI0_IRQHandler()
{
  if (EXTI_PR & (1 << BUTTON_UP))
  {
    EXTI_PR |= (1 << BUTTON_UP);
    EXTI0_callback();
  }
}

extern "C" void EXTI1_IRQHandler()
{
  if (EXTI_PR & (1 << BUTTON_DOWN))
  {
    EXTI_PR |= (1 << BUTTON_DOWN);
    EXTI1_callback();
  }
}