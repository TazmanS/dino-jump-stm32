#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdint.h>
#include "pins.h"

#define RCC_AHBENR (*(volatile uint32_t *)0x40021014)
#define RCC_APB1ENR (*(volatile uint32_t *)0x4002101C)

#define GPIOB_MODER (*(volatile uint32_t *)0x48000400)
#define GPIOB_AFRH (*(volatile uint32_t *)0x48000424)
#define GPIOB_OTYPER (*(volatile uint32_t *)0x48000404)
#define GPIOB_OSPEEDR (*(volatile uint32_t *)0x48000408)
#define GPIOB_PUPDR (*(volatile uint32_t *)0x4800040C)

// LCD
#define I2C1_CR1 (*(volatile uint32_t *)0x40005400)
#define I2C1_CR2 (*(volatile uint32_t *)0x40005404)
#define I2C1_TIMINGR (*(volatile uint32_t *)0x40005410)
#define I2C1_ISR (*(volatile uint32_t *)0x40005418)
#define I2C1_TXDR (*(volatile uint32_t *)0x40005428)
#define I2C1_ICR (*(volatile uint32_t *)0x4000541C)

#endif