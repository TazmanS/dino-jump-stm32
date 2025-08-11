#include "i2c1.hpp"
#include "defines.hpp"

void i2c1_write(uint8_t data)
{
  while (!(I2C1_ISR & (1 << 1)))
    ;
  I2C1_TXDR = data;
}

void i2c1_init()
{
  RCC_AHBENR |= (1 << 18);
  RCC_APB1ENR |= (1 << 21);

  GPIOB_MODER &= ~((3 << (2 * SDA_PIN)) | (3 << (2 * SCL_PIN)));
  GPIOB_MODER |= (2 << (2 * SDA_PIN)) | (2 << (2 * SCL_PIN));

  GPIOB_OTYPER |= (1 << SDA_PIN) | (1 << SCL_PIN);
  GPIOB_OSPEEDR |= (3 << (2 * SDA_PIN)) | (3 << (2 * SCL_PIN));

  GPIOB_AFRH &= ~((0xF << ((SDA_PIN - 8) * 4)) | (0xF << ((SCL_PIN - 8) * 4)));
  GPIOB_AFRH |= (0x4 << ((SDA_PIN - 8) * 4)) | (0x4 << ((SCL_PIN - 8) * 4));

  GPIOB_PUPDR &= ~((3 << (2 * SDA_PIN)) | (3 << (2 * SCL_PIN)));
  GPIOB_PUPDR |= (1 << (2 * SDA_PIN)) | (1 << (2 * SCL_PIN));

  I2C1_CR1 &= ~(1 << 0); // disable
  I2C1_TIMINGR = 0x00303D5B;
  I2C1_CR1 |= (1 << 0); // enable
}