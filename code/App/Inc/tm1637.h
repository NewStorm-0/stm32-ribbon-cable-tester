#ifndef TM1637_H
#define TM1637_H

#include <stdint.h>

/* Grid Addresses */
#define TM1637_GRID1 0x00U
#define TM1637_GRID2 0x01U
#define TM1637_GRID3 0x02U
#define TM1637_GRID4 0x03U
#define TM1637_GRID5 0x04U
#define TM1637_GRID6 0x05U

/* Segment codes for 8-segment display */
#define TM1637_SEG_0 0x3FU
#define TM1637_SEG_1 0x06U
#define TM1637_SEG_2 0x5BU
#define TM1637_SEG_3 0x4FU
#define TM1637_SEG_4 0x66U
#define TM1637_SEG_5 0x6DU
#define TM1637_SEG_6 0x7DU
#define TM1637_SEG_7 0x07U
#define TM1637_SEG_8 0x7FU
#define TM1637_SEG_9 0x6FU
#define TM1637_SEG_A 0x77U
#define TM1637_SEG_B 0x7CU
#define TM1637_SEG_C 0x39U
#define TM1637_SEG_D 0x5EU
#define TM1637_SEG_E 0x79U
#define TM1637_SEG_F 0x71U
#define TM1637_SEG_G 0x3DU
#define TM1637_SEG_H 0x76U
#define TM1637_SEG_MINUS 0x40U
#define TM1637_SEG_UNDERSCORE 0x08U

/* TM1637 display duty cycle (pulse width) */
#define TM1637_DUTY_1_16   0x00U
#define TM1637_DUTY_2_16   0x01U
#define TM1637_DUTY_4_16   0x02U
#define TM1637_DUTY_10_16  0x03U
#define TM1637_DUTY_11_16  0x04U
#define TM1637_DUTY_12_16  0x05U
#define TM1637_DUTY_13_16  0x06U
#define TM1637_DUTY_14_16  0x07U

/* TM1637 display control commands */
#define TM1637_DISPLAY_ON  0x08U
#define TM1637_DISPLAY_OFF 0x00U

void TM1637_SetChar(uint8_t left, uint8_t right);
void TM1637_SetBrightness(uint8_t brightness, uint8_t on);

#endif /* TM1637_H */
