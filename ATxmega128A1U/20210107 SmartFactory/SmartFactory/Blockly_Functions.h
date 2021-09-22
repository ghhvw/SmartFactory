/*
 * Blockly_Functions.h
 *
 * Created: 2-6-2020 15:15:48
 *  Author: Nick
 */ 


#ifndef BLOCKLY_FUNCTIONS_H_
#define BLOCKLY_FUNCTIONS_H_

#ifndef F_CPU
#define F_CPU 24000000
#endif

#include <stdint.h>
#include <util/delay.h>
#include "UART.h"

// functions that are accessible to blockly
void delay_ms(uint16_t ms);
void delay1sec();
void printNumber(uint16_t num);
uint16_t invert(uint16_t num);

int16_t add(int16_t A, int16_t B);
int16_t subtract(int16_t A, int16_t B);
int16_t multiply(int16_t A, int16_t B);
int16_t divide(int16_t A, int16_t B);

bool isEqual(int16_t A, int16_t B);
bool isBigger(int16_t A, int16_t B);
bool isSmaller(int16_t A, int16_t B);
bool isBiggerOrEqual(int16_t A, int16_t B);
bool isSmallerOrEqual(int16_t A, int16_t B);

bool logic_or(bool A, bool B);
bool logic_and(bool A, bool B);
bool logic_xor(bool A, bool B);



#endif /* BLOCKLY_FUNCTIONS_H_ */