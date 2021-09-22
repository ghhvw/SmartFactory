/*
 * TWI.cpp
 *
 * Created: 19-3-2020 12:42:57
 *  Author: Nick & Wout
 */ 

/*
 * ATmega is slave
 */

#include "TWI.h"
#include "UART.h"

const int TWIC_ptr = (int) &TWIC; //pointers voor TWI_onRequest() en TWI_onReceive()
const int TWID_ptr = (int) &TWID;
const int TWIE_ptr = (int) &TWIE;
const int TWIF_ptr = (int) &TWIF;
void (*TWIC_TxCallback)(); //onRequest, data terugsturen naar master
void (*TWID_TxCallback)();
void (*TWIE_TxCallback)();
void (*TWIF_TxCallback)();
void (*TWIC_RxCallback)(uint8_t); //onReceive, data wordt/is ontvangen van master
void (*TWID_RxCallback)(uint8_t); //via callbacks ongetest
void (*TWIE_RxCallback)(uint8_t);
void (*TWIF_RxCallback)(uint8_t);
ISR(TWIC_TWIS_vect) { //slave
	TWI_HandleISR(TWIC_TxCallback, TWIC_RxCallback, TWIC);
}
ISR(TWID_TWIS_vect) { //slave
	TWI_HandleISR(TWID_TxCallback, TWID_RxCallback, TWID);
}
ISR(TWIE_TWIS_vect) { //slave
	TWI_HandleISR(TWIE_TxCallback, TWIE_RxCallback, TWIE);
}
ISR(TWIF_TWIS_vect) { //slave
	TWI_HandleISR(TWIF_TxCallback, TWIF_RxCallback, TWIF);
}


void TWI_HandleISR(void (*TxCallback)(), void (*RxCallback)(uint8_t), TWI_struct &TWI) {
	if((TWI.SLAVE.STATUS &(1<<TWI_SLAVE_DIR_bp))) { //read operation
		if (!TxCallback) { return; } //callback is niet ingesteld
		TxCallback();
	} else { //write operation
		if (!RxCallback) { return; } //callback is niet ingesteld
		RxCallback(TWI.SLAVE.DATA); //ongetest
	}
}


void TWI_init(TWI_struct &TWI) //als slave
{
	TWI.SLAVE.CTRLA = (1<<TWI_SLAVE_APIEN_bp)|(1<<TWI_SLAVE_ENABLE_bp)|(1<<TWI_SLAVE_PIEN_bp)|(1<<TWI_SLAVE_PMEN_bp);
	TWI.SLAVE.CTRLA |= (1<<TWI_SLAVE_DIEN_bp);
	
	//toegevoegd voor TWI_Write(), clear deze bits om het springen naar ISRs uit te schakelen
	TWI.SLAVE.CTRLA |= TWI_MASTER_INTLVL0_bm | TWI_MASTER_INTLVL1_bm; //enable port interrupt high level
}


bool TWI_RecievedAddress(TWI_struct &TWI)
{	
	//valid address received and write operation
	return ((TWI.SLAVE.STATUS &(1<<TWI_SLAVE_APIF_bp)) && !(TWI.SLAVE.STATUS &(1<<TWI_SLAVE_DIR_bp)));
}


bool TWI_ReceivePacket(TWI_struct &TWI, uint8_t* buffer, uint8_t bufferLength) //als slave
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

		//stop if stop interrupt flag
		if(TWI.SLAVE.STATUS &(1<< TWI_SLAVE_APIF_bp))
			break;
			
		//receive data and acknowledge		
		buffer[i] = TWI.SLAVE.DATA;
		TWI.SLAVE.CTRLB |= (1<<TWI_SLAVE_CMD0_bp)|(1<<TWI_SLAVE_CMD1_bp);
		USART_Transmit(USARTD0, buffer[i]);
	}
	_delay_us(1);
	TWI.SLAVE.STATUS |= (1<<TWI_SLAVE_DIF_bp)|(1<<TWI_SLAVE_APIF_bp); //clear interrupts
	return true;
}


bool TWI_Write(TWI_struct &TWI, uint8_t byte) //als slave
{
	//wait for address received interrupt
	while(!(TWI.SLAVE.STATUS &(1<< TWI_SLAVE_APIF_bp)));
	
	//check if master read operation
	if( !(TWI.SLAVE.STATUS &(1<<TWI_SLAVE_DIR_bp)) ) {
		return false; //master write operation
	}
	
	while(1) {
		TWI.SLAVE.STATUS |= (1<<TWI_SLAVE_DIF_bp)|(1<<TWI_SLAVE_APIF_bp); //clear interrupts
		
		TWI.SLAVE.DATA = byte;
		
		//acknowledge and send byte
		TWI.SLAVE.CTRLB &= ~(TWI_SLAVE_ACKACT_bm); //ACK
//		TWI.SLAVE.CTRLB |= (1<<TWI_SLAVE_CMD0_bp)|(1<<TWI_SLAVE_CMD1_bp); //RESPONSE, er komen meer bytes	//<<< gebruik deze voor een toekomstige TWI_SendPacket functie
		TWI.SLAVE.CTRLB |= (1<<TWI_SLAVE_CMD1_bp); //COMPLETE, enige byte wordt verzonden
		
		//wait for transmission completed
		while(TWI.SLAVE.STATUS &(1<<TWI_SLAVE_DIF_bp)) {
			//check for collisions or bus errors
			if (TWI.SLAVE.STATUS &(1<<TWI_SLAVE_COLL_bp) || TWI.SLAVE.STATUS &(1<<TWI_SLAVE_BUSERR_bp)) {
				TWI.SLAVE.STATUS |= (1<<TWI_SLAVE_BUSERR_bp); //clear buserror, collision is cleared automatically
				TWI.SLAVE.STATUS |= (1<<TWI_SLAVE_DIF_bp)|(1<<TWI_SLAVE_APIF_bp); //clear interrupts
				return false;
			}
		}
		
		_delay_us(10);
		
//		if (TWI.SLAVE.STATUS &(1<<TWI_SLAVE_RXACK_bp)) {	//<<< op een of andere manier komt de NACK flag voorafgaand van de STOP conditie nooit aan bod
			//NACK, expect STOP or repeated START condition
			if ((TWI.SLAVE.STATUS &(1<<TWI_SLAVE_APIF_bp)) && !(TWI.SLAVE.STATUS &(1<<TWI_SLAVE_AP_bp))) {
				//received stop condition
				TWI.SLAVE.STATUS |= (1<<TWI_SLAVE_DIF_bp)|(1<<TWI_SLAVE_APIF_bp); //clear interrupts
				return true;
			}
//		} //ACK, continue transmitting
	}
}


//tx callbacks, set function call at interrupt
void TWI_onRequest(void (*f)(), TWI_struct &twi) {
	switch ((int) (&twi)) {
		case TWIC_ptr: TWIC_TxCallback = f; break;
		case TWID_ptr: TWID_TxCallback = f; break;
		case TWIE_ptr: TWIE_TxCallback = f; break;
		case TWIF_ptr: TWIF_TxCallback = f; break;
		default: //geef error ofzo
		while(1); break;
	}
}


//rx callbacks, set function call at interrupt
void TWI_onReceive(void (*f)(uint8_t), TWI_struct &twi) {
	switch ((int) &twi) {
		case TWIC_ptr: TWIC_RxCallback = f; break;
		case TWID_ptr: TWID_RxCallback = f; break;
		case TWIE_ptr: TWIE_RxCallback = f; break;
		case TWIF_ptr: TWIF_RxCallback = f; break;
		default: //geef error ofzo
		while(1); break;
	}
}