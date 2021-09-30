/*
 * SorterArm.h
 *
 * Created: 29-3-2021 11:35:52
 *  Author: Jon_n
 */ 


#ifndef SORTERARM_H_
#define SORTERARM_H_


#include "Stepperdriver.h"
#include "IO_mappings.h"

#ifdef __cplusplus
extern "C" {
#endif

// #define SA_SWITCH_PIN_LEFT PIN0_bm
// #define SA_SWITCH_PIN_RIGHT PIN1_bm

//MOTOR_ID defines in Stepperdriver.h

typedef const struct SorterArm {
    uint8_t switch_pin_left;  // left pin
    uint8_t switch_pin_right; // right pin
    unsigned int minpos;			//Needs to be a positive number (review, why not make it unsigned?)
    unsigned int maxpos;			//Needs to be larger than minpos (review, should an internal check for this be made?)
	unsigned int position;		//Position of the arm
    int steps_per_position;	//(maxpos-minpos)*steps_per_position needs to fit in an int16
    uint8_t motor_id;
    uint16_t motor_speed;
} SorterArm_t;

SorterArm_t sa1 = {
        DIO4, // Default pin voor limit switch left
        DIO5, // Default pin voor limit switch right
        0, // Laagste aantal stappen
        2, // Hoogste aantal stappen
		0, // Default to zero
        2000, // Tussenwaarde per positie
        SORTER_MOTOR_ID, // Motor ID
        0x02FF // Motor speed
};

void SorterArmISR();
void MoveSorterArmTo(uint16_t toPosition);
void MoveSorterArmDistance(bool direction, uint16_t steps);
bool SorterarmIsFinnished();
bool ConfigSorterArm();
void StopSorterArm();
void MoveSorterArm(bool direction);
void HomeSorterArm();
void SaSetInput(uint8_t switch_pin_left, uint8_t switch_pin_right);
void SaSetInterrupt(uint8_t switch_pin_left, uint8_t switch_pin_right);

#ifdef __cplusplus
}
#endif

#endif /* SORTERARM_H_ */