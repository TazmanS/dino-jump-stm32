#pragma once

#include <stdint.h>
#include "pins.hpp"

// ===== RCC =====
#define RCC_BASE 0x40021000
#define RCC_AHBENR (*(volatile uint32_t *)(RCC_BASE + 0x14))
#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x1C))

// ===== GPIOA =====
#define GPIOA_BASE 0x48000000
#define GPIOA_MODER (*(volatile uint32_t *)(GPIOA_BASE + 0x00)) // GPIOA pin configuration register
#define GPIOA_IDR (*(volatile uint32_t *)(GPIOA_BASE + 0x10))   // GPIOA input data register
#define GPIOA_ODR (*(volatile uint32_t *)(GPIOA_BASE + 0x14))   // GPIOA output data register
#define GPIOA_PUPDR (*(volatile uint32_t *)(GPIOA_BASE + 0x0C))

// ===== GPIOB =====
#define GPIOB_BASE 0x48000400
#define GPIOB_MODER (*(volatile uint32_t *)(GPIOB_BASE + 0x00))
#define GPIOB_AFRH (*(volatile uint32_t *)(GPIOB_BASE + 0x24))
#define GPIOB_OTYPER (*(volatile uint32_t *)(GPIOB_BASE + 0x04))
#define GPIOB_OSPEEDR (*(volatile uint32_t *)(GPIOB_BASE + 0x08))
#define GPIOB_PUPDR (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))

// Interrupt
#define EXTI_BASE 0x40010400
#define EXTI_IMR (*(volatile uint32_t *)(EXTI_BASE + 0x00))  // EXTI interrupt mask register
#define EXTI_FTSR (*(volatile uint32_t *)(EXTI_BASE + 0x0C)) // EXTI falling trigger selection register
#define EXTI_PR (*(volatile uint32_t *)(EXTI_BASE + 0x14))   // EXTI pending register
#define NVIC_ISER0 (*(volatile uint32_t *)0xE000E100)        // NVIC interrupt set-enable register 0

// ===== TIM3 =====
#define TIM3_BASE 0x40000400
#define TIM3_CR1 (*(volatile uint32_t *)(TIM3_BASE + 0x00))
#define TIM3_CR2 (*(volatile uint32_t *)(TIM3_BASE + 0x04))
#define TIM3_EGR (*(volatile uint32_t *)(TIM3_BASE + 0x14))
#define TIM3_PSC (*(volatile uint32_t *)(TIM3_BASE + 0x28))
#define TIM3_ARR (*(volatile uint32_t *)(TIM3_BASE + 0x2C))
#define TIM3_DIER (*(volatile uint32_t *)(TIM3_BASE + 0x0C))
#define TIM3_SR (*(volatile uint32_t *)(TIM3_BASE + 0x10))

// LCD
#define I2C1_BASE 0x40005400
#define I2C1_CR1 (*(volatile uint32_t *)(I2C1_BASE + 0x00))
#define I2C1_CR2 (*(volatile uint32_t *)(I2C1_BASE + 0x04))
#define I2C1_TIMINGR (*(volatile uint32_t *)(I2C1_BASE + 0x10))
#define I2C1_ISR (*(volatile uint32_t *)(I2C1_BASE + 0x18))
#define I2C1_TXDR (*(volatile uint32_t *)(I2C1_BASE + 0x28))
#define I2C1_ICR (*(volatile uint32_t *)(I2C1_BASE + 0x1C))
#define PCF8574_ADDR (0x27 << 1)

// ===== DMA (Direct Memory Access 1 (Channel 1) =====
#define DMA1_BASE 0x40020000u
#define DMA1_CCR1 (*(volatile uint32_t *)(DMA1_BASE + 0x08))
#define DMA1_CNDTR1 (*(volatile uint32_t *)(DMA1_BASE + 0x0C))
#define DMA1_CPAR1 (*(volatile uint32_t *)(DMA1_BASE + 0x10))
#define DMA1_CMAR1 (*(volatile uint32_t *)(DMA1_BASE + 0x14))

// ===== ADC1 / COMMON =====
#define ADC1_BASE 0x50000000
#define ADC1_ISR (*(volatile uint32_t *)(ADC1_BASE + 0x00))
#define ADC1_IER (*(volatile uint32_t *)(ADC1_BASE + 0x04))
#define ADC1_CR (*(volatile uint32_t *)(ADC1_BASE + 0x08))
#define ADC1_CFGR (*(volatile uint32_t *)(ADC1_BASE + 0x0C))
#define ADC1_SMPR1 (*(volatile uint32_t *)(ADC1_BASE + 0x14))
#define ADC1_SQR1 (*(volatile uint32_t *)(ADC1_BASE + 0x30))
#define ADC1_DR (*(volatile uint32_t *)(ADC1_BASE + 0x40))

#define ADC12_COMMON_BASE 0x50000300u
#define ADC12_CCR (*(volatile uint32_t *)(ADC12_COMMON_BASE + 0x08)) // опц.
