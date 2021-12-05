#include <Arduino.h>
#include "NTPClient.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"

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

#define BTN_CHECK_INTERVAL	200
#define BTN_LOCK_TIMEOUT	3000

#define TIME_OFFSET_UNIT	3600

#define GET_BIT_VALUE(binary, pos) (((binary >> pos) & 1) == 1 ? 1 : 0)

const char *ssid     = "MikroTik-2GHz";
const char *password = "31415926";

WiFiUDP ntpUDP;

uint8_t seconds, minutes, hours;
uint16_t counter = 0;
uint8_t buttonLocked = 0;
uint8_t buttonLockCounter = 0;
int8_t timeOffset = 1;

NTPClient timeClient(ntpUDP, "de.pool.ntp.org", TIME_OFFSET_UNIT * timeOffset, 60000 * 60 * 24);

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
	WiFi.begin(ssid, password);

	while ( WiFi.status() != WL_CONNECTED ) {
		delay ( 500 );
		Serial.print(".");
	}

	Serial.print(" Connected");

	timeClient.begin();
	// timeClient.setUpdateInterval(60000 * 60 * 24);
	// timeClient.setTimeOffset(3600);
	timeClient.forceUpdate();
}

void checkButtons() {
	if (counter % BTN_CHECK_INTERVAL != 0) {
		return;
	}

	if (buttonLocked) {
		return;
	}

	uint8_t portValue = PCA9557_readPort(PCA9557_I2C_ADDR);
	// uint8_t prevValue = GET_BIT_VALUE(portValue, 5);
	// uint8_t selectValue = GET_BIT_VALUE(portValue, 6);
	uint8_t nextValue = GET_BIT_VALUE(portValue, 7);

	// if (selectValue == 0) {
	// 	if (timeOffset > -5) {
	// 		timeOffset--;
	// 	}

	// 	timeClient.setTimeOffset(TIME_OFFSET_UNIT * timeOffset);

	// 	buttonLocked = 1;
	// }

	// if (selectValue == 0) {
	// 	PCA9557_writePin(PCA9557_I2C_ADDR, SIGNAL_LED_PIN, 1);
	// 	timeClient.forceUpdate();
	// 	PCA9557_writePin(PCA9557_I2C_ADDR, SIGNAL_LED_PIN, 0);

	// 	buttonLocked = 1;
	// }

	if (nextValue == 1) {
		timeOffset = timeOffset == 2 ? 1 : 2;

		timeClient.setTimeOffset(TIME_OFFSET_UNIT * timeOffset);

		buttonLocked = 1;
	}
}

void loop() {
	// checkButtons();

	seconds = timeClient.getSeconds();
	minutes = timeClient.getMinutes();
	hours = timeClient.getHours();

	if (hours == 0) {
		timeClient.forceUpdate();
	}

	VFDDisplay_setNumber(PCA9557_I2C_ADDR, 0, seconds % 10);
	VFDDisplay_setNumber(PCA9557_I2C_ADDR, 1, seconds / 10);

	VFDDisplay_setNumber(PCA9557_I2C_ADDR, 3, minutes % 10);
	VFDDisplay_setNumber(PCA9557_I2C_ADDR, 4, minutes / 10);

	VFDDisplay_setNumber(PCA9557_I2C_ADDR, 6, hours % 10);
	VFDDisplay_setNumber(PCA9557_I2C_ADDR, 7, hours / 10);

	// delayMicroseconds(100);

	// counter++;

	// if (buttonLocked) {
	// 	buttonLockCounter++;

	// 	if (buttonLockCounter % BTN_LOCK_TIMEOUT == 0) {
	// 		buttonLocked = 0;
	// 		buttonLockCounter = 0;
	// 	}
	// }
}