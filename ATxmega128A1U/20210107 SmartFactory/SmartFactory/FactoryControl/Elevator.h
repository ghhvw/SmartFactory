//
// Elevator.H
//
// Created by Jon_n on 17-3-2021.
// Edited by Sjors
//

#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include <avr/io.h>
#include "Stepperdriver.h"
#include "IO_mappings.h"
#include "UART.h"

#ifdef __cplusplus
extern "C" {
#endif

	//Elevator pin defines
	#define EV_SWITCH_PIN_UP DIO2 // Limit Switch for Elevator DOWN
	#define EV_SWITCH_PIN_DOWN DIO3 // Limit Switch for Elevator UP



	/**
	 * \brief - Move the Elevator up or down
	 * 
	 * \param richting - the direction (true for up, false for down
	 */
	void MoveElevator(bool direction);


	/**
	 * \brief send a Stop command to the Elevator StepperDriver
	 */
	void StopElevator();


	/**
	 * \brief - Stop the elevator if the desired position is reached
	 * DEPRECATED: Stopping is automatically handled by ISR
	 * 
	 * \return bool
	 */
	bool ElevatorIsReady();


    bool ConfigElevator(bool richting);


    /**
     * \brief - 
     * 
     * \param ElevatorIsUp - True for up-switch, false for down switch
     * 
     * \return void
     */
    void ElevatorButtonInISR(bool ElevatorIsUp);
	

	void ElevatorInit();


	void ElevatorInterruptSetup();

#ifdef __cplusplus
}
#endif



#endif // ELEVATOR_H