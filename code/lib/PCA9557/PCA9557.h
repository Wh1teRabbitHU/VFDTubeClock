#ifndef PCA9557_HEADER
#define PCA9557_HEADER

#include "I2C_8Bit.h"

/**
 * Device address: 0b0011{A2}{A1}{A0}
 */

#define PCA9557_INPUT_PORT_ADDR				0x0
#define PCA9557_OUTPUT_PORT_ADDR			0x1
#define PCA9557_POLARITY_INVERSION_ADDR		0x2
#define PCA9557_CONFIGURATION_ADDR			0x3

#define PCA9557_VALUE_HIGH					0x1
#define PCA9557_VALUE_LOW					0x0
#define PCA9557_INVERT_PIN					0x1
#define PCA9557_RESET_PIN					0x0
#define PCA9557_INPUT_MODE					0x1
#define PCA9557_OUTPUT_MODE					0x0

void PCA9557_init();
uint8_t PCA9557_readPort(uint8_t i2cAddress);
void PCA9557_writePort(uint8_t i2cAddress, uint8_t value);
uint8_t PCA9557_readPin(uint8_t i2cAddress, uint8_t pin);
void PCA9557_writePin(uint8_t i2cAddress, uint8_t pin, uint8_t value);
void PCA9557_invertPort(uint8_t i2cAddress, uint8_t value);
void PCA9557_invertPin(uint8_t i2cAddress, uint8_t pin, uint8_t value);
void PCA9557_portMode(uint8_t i2cAddress, uint8_t mode);
void PCA9557_pinMode(uint8_t i2cAddress, uint8_t pin, uint8_t mode);

#endif