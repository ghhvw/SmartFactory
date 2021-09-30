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

//============================================================
//	RECEIVE PACKET : HVWI VERSIE
//============================================================
bool TWI_ReceivePacket(TWI_struct &TWI, uint8_t* buffer, uint8_t bufferLength) {
	//variabelen
	volatile static bool bResult;
	volatile static int i;
	//begin bij de eerste ontvangst databuffer index
	i=0;
	//uitgangspunt: het correct ontvangen van data door de slave vanaf de master is niet gelukt
	bResult = false;
	//----------------------------------------------------------------------------------------------------
	// Bij functie binnenkomst is er door de slave een geldig slave-adres vanaf de master ontvangen.
	// Echter om de master data te laten verzenden dient de slave eerst een adres-ACK naar de master te
	// verzenden. Dit geschiedt door de adres interrupt vlag bit APIF te wissen.
	// Het wissen van deze vlag kan door:
	//   TWI.SLAVE.STATUS=TWI_SLAVE_APIF_bm; //hier wordt een '1' weggeschreven in het APIF bit waardoor
	//                                       //dit bit wordt gewist(!), zie datasheet. Alle overige 0-bits
	//                                       //hebben geen invloed op de overige register bits inhoud(!)
	//----------------------------------------------------------------------------------------------------
	//genereer een ack op het ontvangen adres, de master zal nu een eerste databyte zenden
	TWI.SLAVE.STATUS=TWI_SLAVE_APIF_bm;
	//voor altijd doe
	while ( true ) {
		//er is een door de master gegenereerde stop conditie gedetecteerd (want TWI_SLAVE_PIEN_bm in CTRLA is gezet)
		if ( TWI.SLAVE.STATUS & TWI_SLAVE_APIF_bm ) {
			//meld een pass
			bResult = true ;
			//verlaat de lus
			break;
		}//if
		//er is een databyte ontvangen
		if ( TWI.SLAVE.STATUS & TWI_SLAVE_DIF_bm ) {
			//er is nog ruimte in de ontvangst buffer
			if ( i <= bufferLength ) {
				//noteer het ontvangen databyte
				buffer[i++] = TWI.SLAVE.DATA;
			}//if
			//er is geen ruimte meer in de ontvangst buffer
			else {
				//verlaat de lus (met foutstatus)
				break;
			}//else
			//genereer een ack op het ontvangen databyte, de master zal nu eventueel een volgende databyte zenden
			TWI.SLAVE.STATUS=TWI_SLAVE_DIF_bm;
		}//if
	}//while
	//rapporteer het resultaat
	return bResult ;
} //TWI_ReceivePacket


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
