#include "usart.hpp"
#include "defines.hpp"

void usart_init(void)
{
  RCC_AHBENR |= (1 << 17);
  RCC_APB1ENR |= (1 << 17);

  GPIOA_MODER &= ~((0b11 << (2 * 2)) | (0b11 << (3 * 2)));
  GPIOA_MODER |= (0b10 << (2 * 2)) | (0b10 << (3 * 2));
  GPIOA_AFRL &= ~((0xF << (4 * 2)) | (0xF << (4 * 3)));
  GPIOA_AFRL |= (0x7 << (4 * 2)) | (0x7 << (4 * 3));

  // 8 МГц -> 9600 = 8000000 / 9600 = ~833
  USART2_BRR = 833;

  USART2_CR1 = (1 << 2) | (1 << 3) | (1 << 0);
}

char usart_receive(void)
{
  while (!(USART2_ISR & (1 << 5)))
    ;
  return (char)USART2_RDR;
}

void usart_send(char c)
{
  while (!(USART2_ISR & (1 << 7)))
    ;
  USART2_TDR = c;
}

void usart_send_str(const char *s)
{
  while (*s)
    usart_send(*s++);
}
