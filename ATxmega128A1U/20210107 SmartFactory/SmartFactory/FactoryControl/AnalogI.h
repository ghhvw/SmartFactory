/*
 * AnalogI.h
 *
 * Created: 20-11-2020 15:11:42
 *  Author: Wout
 */ 


#ifndef ANALOGI_H_
#define ANALOGI_H_


uint8_t I_AnalogRead(ADC_struct &ADC, uint8_t pin);

uint8_t ReadSignatureByte(uint16_t Address)
{
	NVM_CMD = NVM_CMD_READ_CALIB_ROW_gc;
	uint8_t Result;
	__asm__ ("lpm %0, Z\n" : "=r" (Result) : "z" (Address));
	NVM_CMD = NVM_CMD_NO_OPERATION_gc;
	return Result;
}

void ADC_Init(ADC_struct &ADC) {
	/* http://ww1.microchip.com/downloads/en/DeviceDoc/doc8077.pdf page 296 */

	//calibration data from signature row
	if (&ADC == &ADCA) {
		ADC.CALL = ReadSignatureByte(PRODSIGNATURES_ADCACAL0); //effect onbekend maar staat in datasheet
		ADC.CALH = ReadSignatureByte(PRODSIGNATURES_ADCACAL1);
	} else if (&ADC == &ADCB) {
		ADC.CALL = ReadSignatureByte(PRODSIGNATURES_ADCBCAL0);
		ADC.CALH = ReadSignatureByte(PRODSIGNATURES_ADCBCAL1);
	} else {
		//geef error ofzo
		while(true){}
	}
	
	//cancel any pending conversions, disable ADC
	ADC.CTRLA = ADC_FLUSH_bm;
	
	//external reference on PORT A (voltage dat op AREF pin wordt gezet, het te meten voltage mag hier niet boven komen)
	ADC.REFCTRL = ADC_REFSEL_AREFA_gc;
	
	//8-bit right-adjusted result
	ADC.CTRLB = (ADC_RESOLUTION_8BIT_gc | (1<<ADC_CONMODE_bm));
	
	//prescaler 128						// !willekeurig gekozen
	ADC.PRESCALER = ADC_PRESCALER_DIV64_gc;

	//enable ADC
	ADC.CTRLA |= ADC_ENABLE_bm;
	
	//result at ch0
//	ADC.CTRLA |= (0x0<<2);

	//single ended input no gain
	ADC.CH0.CTRL = ADC_CH_INPUTMODE_SINGLEENDED_gc;

	//disable interrupts
	ADCA.CH0.INTCTRL = 0;
	
	//2 dummy reads
	for (int i=0; i<2; i++) {
		I_AnalogRead(ADC, 1);
	}
}

uint8_t I_AnalogRead(ADC_CH_struct &CH, uint8_t pin) {
	switch(pin)
	{
		//ADC_CH_MUXPOS_PIN0_gc is AREF pin (op 5v), pin lezen returned altijd >252
		case 1:
		CH.MUXCTRL = ADC_CH_MUXPOS_PIN1_gc; //select pin
		break;
		
		case 2:
		CH.MUXCTRL = ADC_CH_MUXPOS_PIN2_gc; //select pin
		break;
		
		case 3:
		CH.MUXCTRL = ADC_CH_MUXPOS_PIN3_gc; //select pin
		break;
		
		case 4:
		CH.MUXCTRL = ADC_CH_MUXPOS_PIN4_gc; //select pin
		break;
		
		case 5:
		CH.MUXCTRL = ADC_CH_MUXPOS_PIN5_gc; //select pin
		break;
		
		default:
		return 0;
		break;
	}
	
	CH.CTRL |= ADC_CH_START_bm; //start conversion channel
	while ((CH.INTFLAGS & ADC_CH0IF_bm) == 0); //wacht op interrupt bit
	CH.INTFLAGS = ADC_CH0IF_bm; //clear interrupt flag by writing one to it
	return CH.RESL; //return lower byte result from channel (8 bit result)
}

//defaults to ch0
uint8_t I_AnalogRead(ADC_struct &ADC, uint8_t pin) {
	return I_AnalogRead(ADC.CH0, pin);
}


#endif /* ANALOGI_H_ */