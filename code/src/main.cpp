#include <Arduino.h>

#include "PCA9557.h"
#include "VFDDisplay.h"

#define PCA9557_I2C_ADDR	0x18

#define GPIO_RESET_PIN		12

#define BLANK_PIN 			0x0
#define CLK_PIN 			0x1
#define LOAD_PIN 			0x2
#define DIN_PIN 			0x3
#define PREV_BTN_PIN		0x5
#define SELECT_BTN_PIN		0x6
#define NEXT_BTN_PIN		0x7
#define SIGNAL_LED_PIN		0x4

void setup() {
	pinMode(GPIO_RESET_PIN, OUTPUT);
	digitalWrite(GPIO_RESET_PIN, LOW);
	delay(10);
	digitalWrite(GPIO_RESET_PIN, HIGH);

	PCA9557_init();

	PCA9557_pinMode(PCA9557_I2C_ADDR, BLANK_PIN, PCA9557_OUTPUT_MODE);
	PCA9557_pinMode(PCA9557_I2C_ADDR, CLK_PIN, PCA9557_OUTPUT_MODE);
	PCA9557_pinMode(PCA9557_I2C_ADDR, LOAD_PIN, PCA9557_OUTPUT_MODE);
	PCA9557_pinMode(PCA9557_I2C_ADDR, DIN_PIN, PCA9557_OUTPUT_MODE);

	PCA9557_pinMode(PCA9557_I2C_ADDR, PREV_BTN_PIN, PCA9557_INPUT_MODE);
	PCA9557_pinMode(PCA9557_I2C_ADDR, SELECT_BTN_PIN, PCA9557_INPUT_MODE);
	PCA9557_pinMode(PCA9557_I2C_ADDR, NEXT_BTN_PIN, PCA9557_INPUT_MODE);
	PCA9557_pinMode(PCA9557_I2C_ADDR, SIGNAL_LED_PIN, PCA9557_OUTPUT_MODE);

	PCA9557_writePin(PCA9557_I2C_ADDR, BLANK_PIN, 0);
	PCA9557_writePin(PCA9557_I2C_ADDR, CLK_PIN, 0);
	PCA9557_writePin(PCA9557_I2C_ADDR, LOAD_PIN, 0);
	PCA9557_writePin(PCA9557_I2C_ADDR, DIN_PIN, 0);

	VFDDisplay_init(CLK_PIN, LOAD_PIN, DIN_PIN);

	Serial.begin(9600);
}

uint8_t number = 0;
uint8_t digit = 0;

void loop() {
	VFDDisplay_setNumber(PCA9557_I2C_ADDR, digit, number++);

	if (number == 10) {
		number = 0;
		digit++;

		if (digit == 14) {
			digit = 0;
		}
	}

	//PCA9557_writePin(PCA9557_I2C_ADDR, SIGNAL_LED_PIN, number % 2);

	delay(300);
}