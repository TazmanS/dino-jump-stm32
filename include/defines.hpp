#pragma once

#include <stdint.h>
#include "pins.hpp"

#define RCC_AHBENR (*(volatile uint32_t *)0x40021014)
#define RCC_APB1ENR (*(volatile uint32_t *)0x4002101C)

#define GPIOA_MODER (*(volatile uint32_t *)0x48000000) // GPIOA pin configuration register
#define GPIOA_IDR (*(volatile uint32_t *)0x48000010)   // GPIOA input data register
#define GPIOA_ODR (*(volatile uint32_t *)0x48000014)   // GPIOA output data register

#define EXTI_IMR (*(volatile uint32_t *)0x40010400)   // EXTI interrupt mask register
#define EXTI_FTSR (*(volatile uint32_t *)0x4001040C)  // EXTI falling trigger selection register
#define EXTI_PR (*(volatile uint32_t *)0x40010414)    // EXTI pending register
#define NVIC_ISER0 (*(volatile uint32_t *)0xE000E100) // NVIC interrupt set-enable register 0

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
#define PCF8574_ADDR (0x27 << 1)
