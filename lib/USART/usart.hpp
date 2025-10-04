#pragma once

#include <stdint.h>

void usart_init(void);
char usart_receive(void);
void usart_send_str(const char *s);
void usart_send_hex16(uint16_t val);