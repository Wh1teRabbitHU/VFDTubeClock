#include <Arduino.h>

#include "PCA9557.h"
#include "VFDDisplay.h"

#define PCA9557_I2C_ADDR	0x18

#define BLANK_PIN 			0

#define CLK_PIN 			14
#define LOAD_PIN 			12
#define DIN_PIN 			13

#define PREV_BTN_PIN		5
#define SELECT_BTN_PIN		6
#define NEXT_BTN_PIN		7
#define SIGNAL_LED_PIN		4

void setup() {
	pinMode(CLK_PIN, OUTPUT);
	pinMode(LOAD_PIN, OUTPUT);
	pinMode(DIN_PIN, OUTPUT);

	PCA9557_init();

	PCA9557_pinMode(PCA9557_I2C_ADDR, BLANK_PIN, PCA9557_OUTPUT_MODE);
	PCA9557_pinMode(PCA9557_I2C_ADDR, 1, PCA9557_INPUT_MODE);
	PCA9557_pinMode(PCA9557_I2C_ADDR, 2, PCA9557_INPUT_MODE);
	PCA9557_pinMode(PCA9557_I2C_ADDR, 3, PCA9557_INPUT_MODE);

	PCA9557_pinMode(PCA9557_I2C_ADDR, PREV_BTN_PIN, PCA9557_INPUT_MODE);
	PCA9557_pinMode(PCA9557_I2C_ADDR, SELECT_BTN_PIN, PCA9557_INPUT_MODE);
	PCA9557_pinMode(PCA9557_I2C_ADDR, NEXT_BTN_PIN, PCA9557_INPUT_MODE);
	PCA9557_pinMode(PCA9557_I2C_ADDR, SIGNAL_LED_PIN, PCA9557_OUTPUT_MODE);

	PCA9557_writePin(PCA9557_I2C_ADDR, BLANK_PIN, 1);
	delay(10);
	PCA9557_writePin(PCA9557_I2C_ADDR, BLANK_PIN, 0);
	// PCA9557_writePin(PCA9557_I2C_ADDR, CLK_PIN, 0);
	// PCA9557_writePin(PCA9557_I2C_ADDR, LOAD_PIN, 0);
	// PCA9557_writePin(PCA9557_I2C_ADDR, DIN_PIN, 0);

	VFDDisplay_init(CLK_PIN, LOAD_PIN, DIN_PIN);

	Serial.begin(9600);
}

uint8_t number = 0;
uint8_t digit = 0;

uint8_t iteration = 0;

void loop() {
	for (uint8_t i = 0; i < 14; i++) {
		VFDDisplay_setNumber(PCA9557_I2C_ADDR, i, i % 9);
		delay(1);
	}
}