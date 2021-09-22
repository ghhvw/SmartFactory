/*
 * TWI.cpp
 *
 * Created: 19-3-2020 12:42:57
 *  Author: Nick
 */ 

#include "TWI.h"
#include "UART.h"

void TWI_init(TWI_struct &TWI, uint8_t address)
{
	TWI.SLAVE.CTRLA = (1<<TWI_SLAVE_DIEN_bp)|(1<<TWI_SLAVE_APIEN_bp)|(1<<TWI_SLAVE_ENABLE_bp)|(1<<TWI_SLAVE_PMEN_bp)|(1<<TWI_SLAVE_PIEN_bp);
}


bool TWI_RecievedAddress(TWI_struct &TWI)
{	
	//valid address received and write operation
	return ((TWI.SLAVE.STATUS &(1<<TWI_SLAVE_APIF_bp)) && !(TWI.SLAVE.STATUS &(1<<TWI_SLAVE_DIR_bp)));
}


bool TWI_ReceivePacket(TWI_struct &TWI, uint8_t* buffer, uint8_t bufferLength)
{
	//wait for address received interrupt
	while(!(TWI.SLAVE.STATUS &(1<< TWI_SLAVE_APIF_bp)));
	
	//check if write operation
	if((TWI.SLAVE.STATUS &(1<<TWI_SLAVE_DIR_bp)))
		return false;
	
	//acknowledge and wait for next package
	TWI.SLAVE.CTRLB |= (1<<TWI_SLAVE_CMD0_bp)|(1<<TWI_SLAVE_CMD1_bp);
	
	for (uint8_t i = 0;i<bufferLength;i++)
	{	
		USART_TransmitString(USARTD0, "\n\r7\n\r");
		//wait for received interrupt
		while(!(TWI.SLAVE.STATUS &(1<< TWI_SLAVE_DIF_bp)||TWI.SLAVE.STATUS &(1<< TWI_SLAVE_APIF_bp)));

		if(TWI.SLAVE.STATUS &(1<< TWI_SLAVE_APIF_bp))
			break;
			
		//receive data and acknowledge		
		buffer[i] = TWI.SLAVE.DATA;
		TWI.SLAVE.CTRLB |= (1<<TWI_SLAVE_CMD0_bp)|(1<<TWI_SLAVE_CMD1_bp);
		USART_Transmit(USARTD0, buffer[i]);
	}
	TWI.SLAVE.STATUS |= (1<<TWI_SLAVE_DIF_bp)|(1<<TWI_SLAVE_APIF_bp);
	return true;
}