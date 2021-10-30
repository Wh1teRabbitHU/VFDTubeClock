#include "VFDDisplay.h"

static uint8_t _clockPin, _loadPin, _dataPin = 0;
static uint32_t currentPositions = 0;

void VFDDisplay_updateDisplay(uint8_t i2cAddress) {
	PCA9557_writePin(i2cAddress, _loadPin, 0);
	PCA9557_writePin(i2cAddress, 0, 1);
	delay(1);
	PCA9557_writePin(i2cAddress, 0, 0);

	Serial.print("Decode: ");

	// currentPositions =    0b00000000000000000000000000100010;
	// currentPositions = 0b00000011111110001111111111111110;

	for (uint8_t pos = 0; pos < 32; pos++) {
		uint8_t posValue = GET_BIT_VALUE(currentPositions, pos);

		Serial.print(posValue);

		PCA9557_writePin(i2cAddress, _dataPin,  posValue);
		delay(1);
		PCA9557_writePin(i2cAddress, _clockPin, 1);
		delay(1);
		PCA9557_writePin(i2cAddress, _clockPin, 0);
		delay(1);
	}

	Serial.println("");

	PCA9557_writePin(i2cAddress, _loadPin, 1);
	delay(1);
	PCA9557_writePin(i2cAddress, _loadPin, 0);
}

void VFDDisplay_setSinglePosition(uint32_t pos, uint8_t value) {
	if (value == 1) {
		currentPositions = currentPositions | (1 << pos);
	} else {
		currentPositions = currentPositions & (~(1 << pos));
	}
}

void VFDDisplay_init(uint8_t clockPin, uint8_t loadPin, uint8_t dataPin) {
	_clockPin = clockPin;
	_loadPin = loadPin;
	_dataPin = dataPin;
}

void VFDDisplay_setDisplay(uint8_t i2cAddress, uint32_t positions) {
	currentPositions = positions;

	VFDDisplay_updateDisplay(i2cAddress);
}

/**
 *  aaa
 * f   b
 * f   b
 *  ggg
 * e   c
 * e   c
 *  ddd dp
 */

void VFDDisplay_setNumber(uint8_t i2cAddress, uint8_t pos, uint8_t number) {
	currentPositions = 0;

	switch (pos) {
		case 0:
			VFDDisplay_setSinglePosition(GRID_1_POS, 1);
			break;
		case 1:
			VFDDisplay_setSinglePosition(GRID_2_POS, 1);
			break;
		case 2:
			VFDDisplay_setSinglePosition(GRID_3_POS, 1);
			break;
		case 3:
			VFDDisplay_setSinglePosition(GRID_4_POS, 1);
			break;
		case 4:
			VFDDisplay_setSinglePosition(GRID_5_POS, 1);
			break;
		case 5:
			VFDDisplay_setSinglePosition(GRID_6_POS, 1);
			break;
		case 6:
			VFDDisplay_setSinglePosition(GRID_7_POS, 1);
			break;
		case 7:
			VFDDisplay_setSinglePosition(GRID_8_POS, 1);
			break;
		case 8:
			VFDDisplay_setSinglePosition(GRID_9_POS, 1);
			break;
		case 9:
			VFDDisplay_setSinglePosition(GRID_10_POS, 1);
			break;
		case 10:
			VFDDisplay_setSinglePosition(GRID_11_POS, 1);
			break;
		case 11:
			VFDDisplay_setSinglePosition(GRID_12_POS, 1);
			break;
		case 12:
			VFDDisplay_setSinglePosition(GRID_13_POS, 1);
			break;
		case 13:
			VFDDisplay_setSinglePosition(GRID_14_POS, 1);
			break;
		default:
			break;
	}

	switch (number) {
		case 0:
			VFDDisplay_setSinglePosition(SEG_A_W_POS, 1);
			VFDDisplay_setSinglePosition(SEG_B_POS, 1);
			VFDDisplay_setSinglePosition(SEG_C_S_POS, 1);
			VFDDisplay_setSinglePosition(SEG_D_POS, 1);
			VFDDisplay_setSinglePosition(SEG_E_POS, 1);
			VFDDisplay_setSinglePosition(SEG_F_POS, 1);
			break;
		case 1:
			VFDDisplay_setSinglePosition(SEG_B_POS, 1);
			VFDDisplay_setSinglePosition(SEG_C_S_POS, 1);
			break;
		case 2:
			VFDDisplay_setSinglePosition(SEG_A_W_POS, 1);
			VFDDisplay_setSinglePosition(SEG_B_POS, 1);
			VFDDisplay_setSinglePosition(SEG_D_POS, 1);
			VFDDisplay_setSinglePosition(SEG_E_POS, 1);
			VFDDisplay_setSinglePosition(SEG_G_M_POS, 1);
			break;
		case 3:
			VFDDisplay_setSinglePosition(SEG_A_W_POS, 1);
			VFDDisplay_setSinglePosition(SEG_B_POS, 1);
			VFDDisplay_setSinglePosition(SEG_C_S_POS, 1);
			VFDDisplay_setSinglePosition(SEG_D_POS, 1);
			VFDDisplay_setSinglePosition(SEG_G_M_POS, 1);
			break;
		case 4:
			VFDDisplay_setSinglePosition(SEG_B_POS, 1);
			VFDDisplay_setSinglePosition(SEG_C_S_POS, 1);
			VFDDisplay_setSinglePosition(SEG_F_POS, 1);
			VFDDisplay_setSinglePosition(SEG_G_M_POS, 1);
			break;
		case 5:
			VFDDisplay_setSinglePosition(SEG_A_W_POS, 1);
			VFDDisplay_setSinglePosition(SEG_C_S_POS, 1);
			VFDDisplay_setSinglePosition(SEG_D_POS, 1);
			VFDDisplay_setSinglePosition(SEG_F_POS, 1);
			VFDDisplay_setSinglePosition(SEG_G_M_POS, 1);
			break;
		case 6:
			VFDDisplay_setSinglePosition(SEG_A_W_POS, 1);
			VFDDisplay_setSinglePosition(SEG_C_S_POS, 1);
			VFDDisplay_setSinglePosition(SEG_D_POS, 1);
			VFDDisplay_setSinglePosition(SEG_E_POS, 1);
			VFDDisplay_setSinglePosition(SEG_F_POS, 1);
			VFDDisplay_setSinglePosition(SEG_G_M_POS, 1);
			break;
		case 7:
			VFDDisplay_setSinglePosition(SEG_A_W_POS, 1);
			VFDDisplay_setSinglePosition(SEG_B_POS, 1);
			VFDDisplay_setSinglePosition(SEG_C_S_POS, 1);
			break;
		case 8:
			VFDDisplay_setSinglePosition(SEG_A_W_POS, 1);
			VFDDisplay_setSinglePosition(SEG_B_POS, 1);
			VFDDisplay_setSinglePosition(SEG_C_S_POS, 1);
			VFDDisplay_setSinglePosition(SEG_D_POS, 1);
			VFDDisplay_setSinglePosition(SEG_E_POS, 1);
			VFDDisplay_setSinglePosition(SEG_F_POS, 1);
			VFDDisplay_setSinglePosition(SEG_G_M_POS, 1);
			break;
		case 9:
			VFDDisplay_setSinglePosition(SEG_A_W_POS, 1);
			VFDDisplay_setSinglePosition(SEG_B_POS, 1);
			VFDDisplay_setSinglePosition(SEG_C_S_POS, 1);
			VFDDisplay_setSinglePosition(SEG_D_POS, 1);
			VFDDisplay_setSinglePosition(SEG_F_POS, 1);
			VFDDisplay_setSinglePosition(SEG_G_M_POS, 1);
			break;
		default:
			break;
	}

	VFDDisplay_updateDisplay(i2cAddress);
}