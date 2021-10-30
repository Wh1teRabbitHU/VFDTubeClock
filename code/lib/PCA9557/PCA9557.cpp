#include "PCA9557.h"

void PCA9557_init() {
	Wire.begin();
}

uint8_t PCA9557_readPort(uint8_t i2cAddress) {
	return I2C_8Bit_readFromModule(i2cAddress, PCA9557_INPUT_PORT_ADDR);
}

void PCA9557_writePort(uint8_t i2cAddress, uint8_t value) {
	I2C_8Bit_writeToModule(i2cAddress, PCA9557_OUTPUT_PORT_ADDR, value);
}

uint8_t PCA9557_readPin(uint8_t i2cAddress, uint8_t pin) {
	return I2C_8Bit_readFlag(i2cAddress, PCA9557_INPUT_PORT_ADDR, pin);
}

void PCA9557_writePin(uint8_t i2cAddress, uint8_t pin, uint8_t value) {
	I2C_8Bit_writeFlag(i2cAddress, PCA9557_OUTPUT_PORT_ADDR, pin, value);
}

void PCA9557_invertPort(uint8_t i2cAddress, uint8_t value) {
	I2C_8Bit_writeToModule(i2cAddress, PCA9557_POLARITY_INVERSION_ADDR, value);
}

void PCA9557_invertPin(uint8_t i2cAddress, uint8_t pin, uint8_t value) {
	I2C_8Bit_writeFlag(i2cAddress, PCA9557_POLARITY_INVERSION_ADDR, pin, value);
}

void PCA9557_portMode(uint8_t i2cAddress, uint8_t mode) {
	I2C_8Bit_writeToModule(i2cAddress, PCA9557_CONFIGURATION_ADDR, mode);
}

void PCA9557_pinMode(uint8_t i2cAddress, uint8_t pin, uint8_t mode) {
	I2C_8Bit_writeFlag(i2cAddress, PCA9557_CONFIGURATION_ADDR, pin, mode);
}