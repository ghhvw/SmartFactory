/*
 * Kleursensor.cpp
 *
 * Created: 05/12/2020 21:51:58
 *  Author: Wout
 */ 

#include "Kleursensor.h"

#if DEBUG
#define DEBUG_OUT(X) USART_TransmitString(USARTD0, X)
#else
#define DEBUG_OUT(X)
#endif

char colour[] = {'#','0','0','0','0','0','0'};


/* blockly functie - functie ter vervanging van werking met char* omdat blockly problemen met kleuren => assembly heeft */
uint16_t SelectColour(uint16_t i) { return i; }


/* blockly functie */
#ifdef COLOUR_AS_INDEX
bool CompareColours(uint16_t c1, uint16_t c2) {
	return (c1 == c2);
#else
bool CompareColours(char *c1, char *c2) {
	return CompareStrings(c1,c2,7); //"#rrggbb"
#endif
}


/* blockly functie - ga R G & B een aantal keer langs en lees kleur */
#define READVALTIMES 5
#ifdef COLOUR_AS_INDEX
uint16_t ReadColourSensor() {
#else
char* ReadColourSensor() {
#endif
	uint16_t buf[READVALTIMES];
	uint8_t colourVal[3];
	
	//elke kleur READVALTIMES keer lezen en gemiddelde opslaan
	for (uint8_t j=0; j<3; j++) {
		for (uint8_t i=0; i<READVALTIMES; i++) {
			buf[i] = ReadOneColour(j);
		}
		//frequency mappen naar RGB value defined in blockly
		colourVal[j] = RoundColourVal(FrequencyToColourVal(ArrAvg(buf, READVALTIMES), j));
//		colourVal[j] = FrequencyToColourVal(ArrAvg(buf, READVALTIMES), j);
	}
	
	#ifdef COLOUR_AS_INDEX
	DEBUG_OUT("Colour: #");
	DEBUG_OUT(ValToColour(colourVal[0], colourVal[1], colourVal[2]));
	DEBUG_OUT("\n");
	return (uint16_t) ColourToIndex(ValToColour(colourVal[0], colourVal[1], colourVal[2]));
	#else
	return ValToColour(colourVal[0], colourVal[1], colourVal[2]);
	#endif
}


/* stel de kleursensor in en lees 1x een kleur */
uint16_t ReadOneColour(uint8_t colour) {
//	PORTJ_DIR &= ~(PIN6_bm);	//set pin as input
	PORTH_DIR |= PIN6_bm | PIN7_bm;	//set pins as output	
	switch (colour) {
		case 0: //red
		PORTH_OUTCLR = (1<<PIN7_bp); //S2, pin 11, schrijf LOW
		PORTH_OUTCLR = (1<<PIN6_bp); //S3, pin 12, schrijf LOW
		break;
		
		case 1: //green
		PORTH_OUTSET = (1<<PIN7_bp); //S2, pin 11, schrijf HIGH
		PORTH_OUTSET = (1<<PIN6_bp); //S3, pin 12, schrijf HIGH
		break;
		
		case 2: //blue
		PORTH_OUTCLR = (1<<PIN7_bp); //S2, pin 11, schrijf LOW
		PORTH_OUTSET = (1<<PIN6_bp); //S3, pin 12, schrijf HIGH
		break;
	}
	
	return (uint16_t) pulseIn(&PORTJ, PIN6_bm, 0, 10000); //pin 10
}


/*
 * functie ter vervanging van werking met char* omdat blockly problemen met kleuren => assembly heeft, 
 * uiteindelijk moet ReadColourSensor() een char* teruggeven die met CompareStrings wordt vergeleken. 
 */
uint8_t ColourToIndex(char *colour) {
	//'#000000' = 0, '#0000ff' = 1, '#00ff00' = 2, '#00ffff' = 3, etc. 
	uint8_t val = 0;
	
	if (ColourToRed(colour) > 0) {
		val |= (1<<2);
	}
	if (ColourToGreen(colour) > 0) {
		val |= (1<<1);
	}
	if (ColourToBlue(colour) > 0) {
		val |= (1<<0);
	}
	return val;
}


/* van \#rrggbb string naar int */
uint8_t ColourToRed(char *colour) {
	char i[] = "00";
	memcpy(i, colour + 1, 2);
	return (uint8_t) hex2int(i);
}


/* van \#rrggbb string naar int */
uint8_t ColourToGreen(char *colour) {
	char i[] = "00";
	memcpy(i, colour + 3, 2);
	return (uint8_t) hex2int(i);
}


/* van \#rrggbb string naar int */
uint8_t ColourToBlue(char *colour) {
	char i[] = "00";
	memcpy(i, colour + 5, 2);
	return (uint8_t) hex2int(i);
}


/* van integers naar \#rrggbb string */
char* ValToColour(uint8_t r, uint8_t g, uint8_t b) {
	colour[1] = HexToASCII(r>>4);
	colour[2] = HexToASCII(r);
	colour[3] = HexToASCII(g>>4);
	colour[4] = HexToASCII(g);
	colour[5] = HexToASCII(b>>4);
	colour[6] = HexToASCII(b);
	_delay_ms(5); //zodat i[6] goed wordt opgeslagen
	char *i_ptr = colour;
	return i_ptr; //var mag na het vergelijken meteen overschreven worden
}


/* convert RGB value 0...255 to 0, 128 or 255 (colours from blockly) */
uint8_t RoundColourVal(uint8_t val) {
	switch (val) {
		#if defined ALLOW_COLOURV_128 && !defined COLOUR_AS_INDEX
		case 0 ... 84:		return 0;
		case 85 ... 169:	return 128;
		case 170 ... 255:	return 255;
		#else
		case 0 ... 127:		return 0;
		case 128 ... 255:	return 255;
		#endif
		default:
		if (val>255) {
			return 255;
		} else {
			return 0;
		}
	}
}


/* map the frequency from sensor to RGB value 0...255 */
uint8_t FrequencyToColourVal(uint16_t freq, uint8_t colour) {
	if (0 == freq) { return 0; } //slechte frequentie read niet als 255 returnen
	long val = 0;
	switch (colour) {
		case 0: //red
		val = map(freq, MINREDFREQ, MAXREDFREQ, 0, 255);
		
		case 1: //green
		val = map(freq, MINGREENFREQ, MAXGREENFREQ, 0, 255);
		
		case 2: //blue
		val = map(freq, MINBLUEFREQ, MAXBLUEFREQ, 0, 255);
	}
	if (val<0) { val = 0; }
	if (val>255) { val = 255; }
	return (uint8_t) val;
}


/* calculate average value in array */
uint16_t ArrAvg(uint16_t *a, uint8_t size) {
	unsigned long sum = 0;
	for (uint8_t i=0; i<size; i++) {
		sum += a[i];
	}
	sum /= size;
	return sum;
}


bool CompareStrings(char *c1, char *c2, uint8_t length) {
	for (uint8_t i=0; i<length; i++) {
		if (c1+i != c2+i) {
			return 0;
		}
	}
	return 1;
}


/*
 * https://stackoverflow.com/questions/10156409/convert-hex-string-char-to-int 
 */
uint32_t hex2int(char *hex) {
    uint32_t val = 0;
    while (*hex) {
        // get current character then increment
        uint8_t byte = *hex++; 
        // transform hex character to the 4bit equivalent number, using the ascii table indexes
        if (byte >= '0' && byte <= '9') byte = byte - '0';
        else if (byte >= 'a' && byte <='f') byte = byte - 'a' + 10;
        else if (byte >= 'A' && byte <='F') byte = byte - 'A' + 10;    
        // shift 4 to make space for new digit, and add the 4 bits of the new digit 
        val = (val << 4) | (byte & 0xF);
    }
    return val;
}


/*
 * https://www.arduino.cc/reference/en/language/functions/math/map/ 
 */
long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}