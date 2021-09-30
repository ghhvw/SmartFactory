/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	PORTA_DIR = 0;//set all IO's to input
	PORTB_DIR = 0;//set all IO's to input
	PORTC_DIR = (1<<4)|(1<<5)|(1<<7); //set SS, MOSI and SPCK as output
	PORTD_DIR = (1<<0)|(1<<1)|(1<<3)|(1<<4); //set CAN and Ethernet SS and TXD2 as output
	PORTE_DIR = (1<<4)|(1<<5)|(1<<7); //set DE, RE and TXD1 as output
	PORTF_DIR = (1<<3)|(1<<4)|(1<<5); //set DE, RE and TXD1 as output
	PORTH_DIR = (1<<4)|(1<<5); //set LED1 and LED2 as output
	PORTJ_DIR = 0;//set all IO's to input
	PORTK_DIR = 0;//set all IO's to input
	PORTQ_DIR = (1<<0)|(1<<1)|(1<<2)|(1<<3); //set relays to output
	PORTR_DIR = (1<<0)|(1<<1); //set relays to output
	

	PORTA_PIN0CTRL = (1<<PORT_OPC0_bp )|(1<<PORT_OPC1_bp);
	
	
	//Init UARTS
	
	
	
}
