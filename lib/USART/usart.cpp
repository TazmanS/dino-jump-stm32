#include "usart.hpp"
#include "defines.hpp"

void usart_init(void)
{
  RCC_AHBENR |= (1 << 17);
  RCC_APB1ENR |= (1 << 17);

  GPIOA_MODER &= ~((0b11 << (2 * USART2_TX)) | (0b11 << (2 * USART2_RX)));
  GPIOA_MODER |= (0b10 << (2 * USART2_TX)) | (0b10 << (2 * USART2_RX));
  GPIOA_AFRL &= ~((0xF << (4 * USART2_TX)) | (0xF << (4 * USART2_RX)));
  GPIOA_AFRL |= (0x7 << (4 * USART2_TX)) | (0x7 << (4 * USART2_RX));

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

void usart_send_hex16(uint16_t val)
{
  const char hex[] = "0123456789ABCDEF";
  char buf[7]; // "0x" + 4 цифры + '\n' + '\0'
  buf[0] = '0';
  buf[1] = 'x';
  buf[2] = hex[(val >> 12) & 0xF];
  buf[3] = hex[(val >> 8) & 0xF];
  buf[4] = hex[(val >> 4) & 0xF];
  buf[5] = hex[(val >> 0) & 0xF];
  buf[6] = '\n';
  usart_send_str(buf);
}