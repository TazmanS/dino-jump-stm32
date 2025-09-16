#pragma once

#include <stdint.h>
#include "pins.hpp"

// ===== RCC (Reset and Clock Control) =====
#define RCC_BASE 0x40021000
#define RCC_AHBENR (*(volatile uint32_t *)(RCC_BASE + 0x14))  // AHB peripheral clock enable register
#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x1C)) // APB1 peripheral clock enable register

// ===== GPIOA (General-Purpose I/O Port A) =====
#define GPIOA_BASE 0x48000000
#define GPIOA_MODER (*(volatile uint32_t *)(GPIOA_BASE + 0x00)) // GPIO port mode register
#define GPIOA_IDR (*(volatile uint32_t *)(GPIOA_BASE + 0x10))   // GPIO port input data register
#define GPIOA_ODR (*(volatile uint32_t *)(GPIOA_BASE + 0x14))   // GPIO port output data register
#define GPIOA_PUPDR (*(volatile uint32_t *)(GPIOA_BASE + 0x0C)) // GPIO port pull-up/pull-down register
#define GPIOA_AFRL (*(volatile uint32_t *)(GPIOA_BASE + 0x20))

// ===== GPIOB (General-Purpose I/O Port B) =====
#define GPIOB_BASE 0x48000400
#define GPIOB_MODER (*(volatile uint32_t *)(GPIOB_BASE + 0x00))   // GPIO port mode register
#define GPIOB_AFRH (*(volatile uint32_t *)(GPIOB_BASE + 0x24))    // GPIO alternate function high register
#define GPIOB_OTYPER (*(volatile uint32_t *)(GPIOB_BASE + 0x04))  // GPIO port output type register
#define GPIOB_OSPEEDR (*(volatile uint32_t *)(GPIOB_BASE + 0x08)) // GPIO port output speed register
#define GPIOB_PUPDR (*(volatile uint32_t *)(GPIOB_BASE + 0x0C))   // GPIO port pull-up/pull-down register

// ===== EXTI (External Interrupt/Event Controller) =====
#define EXTI_BASE 0x40010400
#define EXTI_IMR (*(volatile uint32_t *)(EXTI_BASE + 0x00))  // Interrupt mask register
#define EXTI_FTSR (*(volatile uint32_t *)(EXTI_BASE + 0x0C)) // Falling trigger selection register
#define EXTI_PR (*(volatile uint32_t *)(EXTI_BASE + 0x14))   // Pending register (clear by writing 1)
#define NVIC_ISER0 (*(volatile uint32_t *)0xE000E100)        // NVIC interrupt set-enable register (IRQ 0–31)

// ===== TIM3 (Timer 3) =====
#define TIM3_BASE 0x40000400
#define TIM3_CR1 (*(volatile uint32_t *)(TIM3_BASE + 0x00))  // Control register 1
#define TIM3_CR2 (*(volatile uint32_t *)(TIM3_BASE + 0x04))  // Control register 2
#define TIM3_EGR (*(volatile uint32_t *)(TIM3_BASE + 0x14))  // Event generation register
#define TIM3_PSC (*(volatile uint32_t *)(TIM3_BASE + 0x28))  // Prescaler register
#define TIM3_ARR (*(volatile uint32_t *)(TIM3_BASE + 0x2C))  // Auto-reload register
#define TIM3_DIER (*(volatile uint32_t *)(TIM3_BASE + 0x0C)) // DMA/interrupt enable register
#define TIM3_SR (*(volatile uint32_t *)(TIM3_BASE + 0x10))   // Status register (flags like UIF)

// ===== I2C1 (Inter-Integrated Circuit 1) =====
#define I2C1_BASE 0x40005400
#define I2C1_CR1 (*(volatile uint32_t *)(I2C1_BASE + 0x00))     // Control register 1
#define I2C1_CR2 (*(volatile uint32_t *)(I2C1_BASE + 0x04))     // Control register 2
#define I2C1_TIMINGR (*(volatile uint32_t *)(I2C1_BASE + 0x10)) // Timing register (prescalers, SCL high/low)
#define I2C1_ISR (*(volatile uint32_t *)(I2C1_BASE + 0x18))     // Interrupt and status register
#define I2C1_TXDR (*(volatile uint32_t *)(I2C1_BASE + 0x28))    // Transmit data register
#define I2C1_ICR (*(volatile uint32_t *)(I2C1_BASE + 0x1C))     // Interrupt clear register
#define PCF8574_ADDR (0x27 << 1)                                // I²C address of PCF8574 (LCD expander)

// ===== DMA1 (Direct Memory Access Controller 1, Channel 1) =====
#define DMA1_BASE 0x40020000u
#define DMA1_CCR1 (*(volatile uint32_t *)(DMA1_BASE + 0x08))   // Channel 1 configuration register
#define DMA1_CNDTR1 (*(volatile uint32_t *)(DMA1_BASE + 0x0C)) // Channel 1 number of data register
#define DMA1_CPAR1 (*(volatile uint32_t *)(DMA1_BASE + 0x10))  // Channel 1 peripheral address register
#define DMA1_CMAR1 (*(volatile uint32_t *)(DMA1_BASE + 0x14))  // Channel 1 memory address register

// ===== ADC1 (Analog-to-Digital Converter 1) =====
#define ADC1_BASE 0x50000000
#define ADC1_ISR (*(volatile uint32_t *)(ADC1_BASE + 0x00))   // Interrupt and status register
#define ADC1_IER (*(volatile uint32_t *)(ADC1_BASE + 0x04))   // Interrupt enable register
#define ADC1_CR (*(volatile uint32_t *)(ADC1_BASE + 0x08))    // Control register
#define ADC1_CFGR (*(volatile uint32_t *)(ADC1_BASE + 0x0C))  // Configuration register
#define ADC1_SMPR1 (*(volatile uint32_t *)(ADC1_BASE + 0x14)) // Sample time register 1
#define ADC1_SQR1 (*(volatile uint32_t *)(ADC1_BASE + 0x30))  // Regular sequence register 1
#define ADC1_DR (*(volatile uint32_t *)(ADC1_BASE + 0x40))    // Data register (conversion result)

// ===== ADC12_COMMON (Shared registers for ADC1 and ADC2) =====
#define ADC12_COMMON_BASE 0x50000300u
#define ADC12_CCR (*(volatile uint32_t *)(ADC12_COMMON_BASE + 0x08)) // Common control register (clock mode, multi ADC config)

// ===== USART2 (Universal Synchronous/Asynchronous Receiver/Transmitter) =====
#define USART_BASE 0x40004400
#define USART2_CR1 (*(volatile uint32_t *)(USART_BASE + 0x00)) // Control register 1 (включение USART, включение RX/TX, задание формата кадра, разрешение прерываний)
#define USART2_BRR (*(volatile uint32_t *)(USART_BASE + 0x0C)) // Baud rate register (коэффициенты для установки скорости передачи, зависят от частоты шины APB1)
#define USART2_ISR (*(volatile uint32_t *)(USART_BASE + 0x1C)) // Interrupt and status register (флаги: TX пуст, RX полный, ошибки и т.п.)
#define USART2_RDR (*(volatile uint32_t *)(USART_BASE + 0x24)) // Receive data register (регистр приёма; из него читается байт, принятый с линии RX)
#define USART2_TDR (*(volatile uint32_t *)(USART_BASE + 0x28)) // Transmit data register (регистр передачи; в него пишется байт, чтобы отправить через TX)
