#include "interrupts.hpp"
#include "defines.hpp"

void interruptors_config(void)
{
  RCC_AHBENR |= (1 << 17);

  GPIOA_MODER &= ~(0b11 << (BUTTON_1 * 2));
  GPIOA_MODER &= ~(0b11 << (BUTTON_2 * 2));

  GPIOA_IDR |= (1 << BUTTON_1);
  GPIOA_IDR |= (1 << BUTTON_2);

  EXTI_IMR |= (1 << BUTTON_1);
  EXTI_FTSR |= (1 << BUTTON_1);

  EXTI_IMR |= (1 << BUTTON_2);
  EXTI_FTSR |= (1 << BUTTON_2);

  NVIC_ISER0 |= (1 << 10);
  NVIC_ISER0 |= (1 << 23);
}

static Callback first_callback = nullptr;
static Callback second_callback = nullptr;

void EXTI4_callback(Callback callback) // prev
{
  first_callback = callback;
};

void EXTI4_callback() // prev
{
  if (first_callback)
    first_callback();
};

void EXTI5_callback(Callback callback) // next
{
  second_callback = callback;
};

void EXTI5_callback() // next
{
  if (second_callback)
    second_callback();
};

extern "C" void EXTI4_IRQHandler() // prev
{
  if (EXTI_PR & (1 << BUTTON_1))
  {
    EXTI_PR |= (1 << BUTTON_1);
    EXTI4_callback();
  }
}

extern "C" void EXTI9_5_IRQHandler() // next
{
  if (EXTI_PR & (1 << BUTTON_2))
  {
    EXTI_PR |= (1 << BUTTON_2);
    EXTI5_callback();
  }
}