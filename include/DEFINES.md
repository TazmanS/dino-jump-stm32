# STM32F3 Registers Cheat Sheet

This document explains each defined register, its abbreviation, and usage context.  
Target MCU: **STM32F3xx** (bare-metal, no HAL).

---

## RCC (Reset and Clock Control)

| Define        | Full Name                                   | Explanation & Usage |
|---------------|---------------------------------------------|---------------------|
| `RCC_AHBENR`  | **AHB peripheral clock enable register**    | Enables clocks for AHB peripherals (e.g., GPIO ports, DMA). Must be enabled before using a peripheral. |
| `RCC_APB1ENR` | **APB1 peripheral clock enable register**   | Enables clocks for APB1 peripherals (e.g., TIM2–TIM7, I2C1, USART2). |

---

## GPIOA (General Purpose I/O Port A)

| Define        | Full Name                                  | Explanation & Usage |
|---------------|--------------------------------------------|---------------------|
| `GPIOA_MODER` | **GPIO port mode register**                | Configures pin mode: input, output, alternate function, or analog. |
| `GPIOA_IDR`   | **Input data register**                    | Reads logic level of input pins. |
| `GPIOA_ODR`   | **Output data register**                   | Sets or clears logic level of output pins. |
| `GPIOA_PUPDR` | **Pull-up/pull-down register**             | Enables pull-up, pull-down, or floating state for input pins. |

---

## GPIOB (General Purpose I/O Port B)

| Define         | Full Name                                      | Explanation & Usage |
|----------------|------------------------------------------------|---------------------|
| `GPIOB_MODER`  | **GPIO port mode register**                    | Same as for GPIOA, but for Port B. |
| `GPIOB_AFRH`   | **Alternate function high register**           | Selects alternate functions for pins **8–15**. Used for UART, I2C, SPI, etc. |
| `GPIOB_OTYPER` | **Output type register**                       | Selects output type: push-pull or open-drain. |
| `GPIOB_OSPEEDR`| **Output speed register**                      | Configures output slew rate (low/medium/high). |
| `GPIOB_PUPDR`  | **Pull-up/pull-down register**                 | Same function as GPIOA_PUPDR. |

---

## EXTI (External Interrupt/Event Controller)

| Define       | Full Name                                   | Explanation & Usage |
|--------------|---------------------------------------------|---------------------|
| `EXTI_IMR`   | **Interrupt mask register**                 | Enables/disables interrupts for each EXTI line. |
| `EXTI_FTSR`  | **Falling trigger selection register**      | Configures interrupts on falling edge (e.g., button press). |
| `EXTI_PR`    | **Pending register**                        | Shows pending interrupt flag. Write `1` to clear. |
| `NVIC_ISER0` | **NVIC Interrupt Set-Enable Register (0–31)** | Enables interrupts in Cortex-M NVIC. |

---

## TIM3 (Timer 3)

| Define       | Full Name                                   | Explanation & Usage |
|--------------|---------------------------------------------|---------------------|
| `TIM3_CR1`   | **Control register 1**                      | Starts/stops the timer, configures counting mode. |
| `TIM3_CR2`   | **Control register 2**                      | Master mode selection, trigger outputs. |
| `TIM3_EGR`   | **Event generation register**               | Forces update events (e.g., reset counter). |
| `TIM3_PSC`   | **Prescaler register**                      | Divides input clock to control timer frequency. |
| `TIM3_ARR`   | **Auto-reload register**                    | Sets the period (overflow value). |
| `TIM3_DIER`  | **DMA/Interrupt enable register**            | Enables update interrupts or DMA requests. |
| `TIM3_SR`    | **Status register**                         | Contains flags (e.g., UIF – update interrupt flag). |

---

## I2C1 (Inter-Integrated Circuit, Peripheral 1)

| Define         | Full Name                                   | Explanation & Usage |
|----------------|---------------------------------------------|---------------------|
| `I2C1_CR1`     | **Control register 1**                      | Enables peripheral, controls interrupts, DMA. |
| `I2C1_CR2`     | **Control register 2**                      | Sets number of bytes, slave address, reload/autoend. |
| `I2C1_TIMINGR` | **Timing register**                         | Configures SCL clock timings (prescaler, high/low periods). |
| `I2C1_ISR`     | **Interrupt and status register**           | Reports status flags (TX ready, RX ready, NACK). |
| `I2C1_TXDR`    | **Transmit data register**                  | Write data here to send via I²C. |
| `I2C1_ICR`     | **Interrupt clear register**                | Clears error/interrupt flags. |
| `PCF8574_ADDR` | **PCF8574 I²C address (0x27<<1)**           | Slave address for LCD I²C expander. |

---

## DMA1 (Direct Memory Access Controller, Channel 1)

| Define         | Full Name                                   | Explanation & Usage |
|----------------|---------------------------------------------|---------------------|
| `DMA1_CCR1`    | **Channel 1 configuration register**        | Configures channel (direction, increment, priority). |
| `DMA1_CNDTR1`  | **Channel 1 number of data register**       | Number of data items to transfer. |
| `DMA1_CPAR1`   | **Channel 1 peripheral address register**   | Holds address of peripheral data register (e.g., ADC_DR). |
| `DMA1_CMAR1`   | **Channel 1 memory address register**       | Holds address of memory buffer. |

---

## ADC1 (Analog-to-Digital Converter 1)

| Define        | Full Name                                   | Explanation & Usage |
|---------------|---------------------------------------------|---------------------|
| `ADC1_ISR`    | **Interrupt and status register**           | Flags: end of conversion, ready, overrun, etc. |
| `ADC1_IER`    | **Interrupt enable register**               | Enables ADC interrupts. |
| `ADC1_CR`     | **Control register**                        | Starts/stops conversion, calibration, deep power-down. |
| `ADC1_CFGR`   | **Configuration register**                  | Configures resolution, alignment, trigger source. |
| `ADC1_SMPR1`  | **Sample time register 1**                  | Sets sampling time for channels 1–9. |
| `ADC1_SQR1`   | **Regular sequence register 1**             | Defines conversion sequence (channel order, length). |
| `ADC1_DR`     | **Data register**                           | Holds conversion result (12/16 bits). |

---

## ADC12_COMMON (Shared Registers for ADC1 + ADC2)

| Define        | Full Name                                   | Explanation & Usage |
|---------------|---------------------------------------------|---------------------|
| `ADC12_CCR`   | **Common control register**                 | Configures clock mode, multi-ADC operation, internal channels. |

---

## Abbreviation Reference

- **CR** = Control Register  
- **SR** = Status Register  
- **EGR** = Event Generation Register  
- **PSC** = Prescaler  
- **ARR** = Auto-Reload Register  
- **DIER** = DMA/Interrupt Enable Register  
- **ISR** = Interrupt and Status Register  
- **ICR** = Interrupt Clear Register  
- **ODR** = Output Data Register  
- **IDR** = Input Data Register  
- **AFR** = Alternate Function Register  
- **SMPR** = Sample Time Register  
- **SQR** = Sequence Register  
- **DR** = Data Register   
