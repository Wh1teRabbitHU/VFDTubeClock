#ifndef VFD_DISPLAY_HEADER
#define VFD_DISPLAY_HEADER

#include "Arduino.h"
#include "PCA9557.h"

#define GET_BIT_VALUE(binary, pos) (((binary >> pos) & 1) == 1 ? 1 : 0)

#define SEG_A_W_POS		2
#define SEG_B_POS		14
#define SEG_C_S_POS		13
#define SEG_D_POS		12
#define SEG_E_POS		1
#define SEG_F_POS		3
#define SEG_G_M_POS		15
#define SEG_P_POS		11

#define GRID_1_POS		22
#define GRID_2_POS		19
#define GRID_3_POS		24
#define GRID_4_POS		23
#define GRID_5_POS		25
#define GRID_6_POS		20
#define GRID_7_POS		21
#define GRID_8_POS		8
#define GRID_9_POS		7
#define GRID_10_POS		6
#define GRID_11_POS		5
#define GRID_12_POS		4
#define GRID_13_POS		9
#define GRID_14_POS		10

void VFDDisplay_init(uint8_t clockPin, uint8_t loadPin, uint8_t dataPin);
void VFDDisplay_setDisplay(uint8_t i2cAddress, uint32_t positions);
void VFDDisplay_setNumber(uint8_t i2cAddress, uint8_t pos, uint8_t number);

#endif