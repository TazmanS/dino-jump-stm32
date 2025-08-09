# **Interrupts in Embedded Systems (STM32 / ARM Cortex-M)**

## **What is an Interrupt?**

An **interrupt** is a mechanism that allows the CPU to pause its current task and immediately execute a special function (called an **Interrupt Service Routine**, or **ISR**) in response to an **event** (external or internal). After handling the interrupt, the CPU resumes its previous execution.

---

## **Common Abbreviations**

* **IRQ** – *Interrupt Request*: Hardware-level signal to the NVIC to trigger an interrupt.
* **ISR** – *Interrupt Service Routine*: Function that handles the interrupt event.
* **NVIC** – *Nested Vectored Interrupt Controller*: Manages and prioritizes interrupts on ARM Cortex-M.
* **EXTI** – *External Interrupt*: Peripheral that detects external edge-triggered events.
* **SYSCFG** – *System Configuration*: Used to route EXTI lines to specific GPIO ports.

---

## **How an Interrupt Works**

1. A peripheral (e.g., GPIO, Timer, USART) raises an **IRQ (Interrupt Request)**.
2. The **NVIC (Nested Vectored Interrupt Controller)** receives and evaluates the IRQ.
3. If allowed, the CPU:

   * Pauses current execution.
   * Saves context.
   * Jumps to the corresponding **ISR (Interrupt Service Routine)**.
4. ISR executes the required logic.
5. CPU returns to the interrupted task.

---

## **Key Modules in STM32 Interrupts**

* **GPIO** – General-purpose input/output. Source of external events.
* **EXTI** – External interrupt lines. Detect edge-triggered changes.
* **SYSCFG** – Maps EXTI lines to GPIO pins.
* **NVIC** – ARM interrupt controller that enables, disables, prioritizes interrupts.

---

## **Example: Button on Pin PA1 Using EXTI1**

1. Configure **PA1** as input.
2. Route **EXTI1** to **PA1** using `SYSCFG->EXTICR[0]`.
3. Enable falling edge trigger: `EXTI->FTSR |= (1 << 1)`.
4. Unmask EXTI1: `EXTI->IMR |= (1 << 1)`.
5. Enable EXTI1 IRQ in NVIC: `NVIC_EnableIRQ(EXTI1_IRQn)`.
6. Write the ISR:

```c
void EXTI1_IRQHandler(void) {
    if (EXTI->PR & (1 << 1)) {
        EXTI->PR |= (1 << 1); // Clear interrupt pending bit
        // Handle button press logic here
    }
}
```

---

## **NVIC ISER (Interrupt Set-Enable Registers)**

* **`NVIC_ISER0 (0xE000E100)`** – Enables IRQ 0 to 31.
* **`NVIC_ISER1 (0xE000E104)`** – Enables IRQ 32 to 63.
* **`NVIC_ISER2 (0xE000E108)`** – Enables IRQ 64 to 95.

To enable any IRQ manually:

```c
NVIC->ISER[IRQn / 32] |= (1 << (IRQn % 32));
```

---

## **IRQ Number Table (STM32F3 Examples)**

| Peripheral     | IRQn Constant        | IRQ Number | ISR Function Name                 |
| -------------- | -------------------- | ---------- | --------------------------------- |
| EXTI0          | `EXTI0_IRQn`         | 6          | `void EXTI0_IRQHandler()`         |
| EXTI1          | `EXTI1_IRQn`         | 7          | `void EXTI1_IRQHandler()`         |
| EXTI2          | `EXTI2_IRQn`         | 8          | `void EXTI2_IRQHandler()`         |
| TIM2           | `TIM2_IRQn`          | 28         | `void TIM2_IRQHandler()`          |
| USART1         | `USART1_IRQn`        | 37         | `void USART1_IRQHandler()`        |
| I2C1\_EV       | `I2C1_EV_IRQn`       | 31         | `void I2C1_EV_IRQHandler()`       |
| DMA1\_Channel1 | `DMA1_Channel1_IRQn` | 11         | `void DMA1_Channel1_IRQHandler()` |

---

## **Practical Examples**

### 🔘 External Interrupt on Button (EXTI1)

```c
void setup_button_interrupt() {
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA->MODER &= ~(0b11 << (1 * 2)); // PA1 input

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    SYSCFG->EXTICR[0] &= ~(0xF << 4); // EXTI1 = PA1

    EXTI->IMR  |= (1 << 1);   // Unmask line 1
    EXTI->FTSR |= (1 << 1);   // Falling edge

    NVIC_EnableIRQ(EXTI1_IRQn);
}

void EXTI1_IRQHandler(void) {
    if (EXTI->PR & (1 << 1)) {
        EXTI->PR |= (1 << 1); // Clear flag
        // Handle button logic
    }
}
```

### ⏱ Timer Interrupt (TIM2)

```c
void setup_tim2_interrupt() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = 7999;
    TIM2->ARR = 1000;
    TIM2->DIER |= TIM_DIER_UIE;
    TIM2->CR1 |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void) {
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &= ~TIM_SR_UIF; // Clear flag
        // Handle timer event (e.g. toggle LED)
    }
}
```

### 📡 USART Receive Interrupt (USART1)

```c
void setup_usart1_interrupt() {
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    USART1->CR1 |= USART_CR1_RXNEIE; // Enable RX interrupt
    USART1->CR1 |= USART_CR1_UE | USART_CR1_RE; // Enable USART

    NVIC_EnableIRQ(USART1_IRQn);
}

void USART1_IRQHandler(void) {
    if (USART1->ISR & USART_ISR_RXNE) {
        char received = USART1->RDR; // Read received byte
        // Process received data
    }
}
```

---

## **Notes and Best Practices**

* ISR functions must be named correctly (`EXTI0_IRQHandler`, `USART1_IRQHandler`, etc.).
* Always clear the interrupt flag in `EXTI->PR`, `TIMx->SR`, etc.
* Avoid long operations inside ISRs. Use flags or FreeRTOS mechanisms.
* Prioritize important ISRs using `NVIC_SetPriority()`.
* Never use `printf()` inside ISRs — it's not safe.


