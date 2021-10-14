/*
 *  Kleursensor.cpp
 *
 *  @Created: 14/10/2021 09:13:27
 *  @Author: Yannick
 */ 

#include "Kleursensor.h"

#define DEBUG_OUT(X) USART_TransmitString(USARTD0, X)


<<<<<<< Updated upstream

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
=======
/**
  * @brief  Initializes the color sensor
  * @param  None
  * @retval None
  */
void initColorSensor(void){
    PORTJ_DIR &= ~(PIN6_bm);	//set pin as input
	PORTH_DIR |= PIN6_bm | PIN7_bm;	//set pins as output	
>>>>>>> Stashed changes
}

/**
  * @brief  Read color sensor multiple times and return the 'average color' in frequency
  * @param  None
  * @def    DIFFERENTCOLORS = ammount of different colors (3)
  *         AVERAGECOLORS = ammount of samples taken
  * @retval color (#rrggbb) retreived from the color frequency
  */
uint16_t ReadColourSensor(void){
	uint16_t storeOneColor[AVERAGECOLORS];
	uint8_t RedGreenBlue[DIFFERENTCOLORS];
	
<<<<<<< Updated upstream
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
	DEBUG_OUT("Color: ");
	DEBUG_OUT(ValToColour(colourVal[0], colourVal[1], colourVal[2]));
	DEBUG_OUT("\n");
	return (uint16_t) ColourToIndex(ValToColour(colourVal[0], colourVal[1], colourVal[2]));
	#else
	return ValToColour(colourVal[0], colourVal[1], colourVal[2]);
	#endif
=======
    for (uint8_t desiredColor=0;desiredColor<DIFFERENTCOLORS;desiredColor++){//Read Red Green and Blue apart
        for (uint8_t i=0;i<AVERAGECOLORS;i++){//sample one color 5 times and take the average
            storeOneColor[i] = getColor(desiredColor);
        }
        //map color frequency to RGB and store in array
        /*FrequencyToColourVal(freq, color)
        calcAverageArray(array, size)*/
        RedGreenBlue[desiredColor] = FrequencyToColourVal(calcAverageArray(storeOneColor, AVERAGECOLORS), desiredColor);
    }
    uint8_t redColor     = RedGreenBlue[REDCASE];
    uint8_t greenColor   = RedGreenBlue[GREENCASE];
    uint8_t blueColor    = RedGreenBlue[BLUECASE];

    if (redColor < blueColor && redColor < greenColor && redColor < 20){ //color is red
        DEBUG_OUT("color is RED\n\r");
    }else if (blueColor < redColor && blueColor < greenColor && blueColor>50){  //color is blue
        DEBUG_OUT("color is BLUE\n\r");
    }else if (greenColor < redColor && greenColor < blueColor){ //color is green
        DEBUG_OUT("color is GREEN\n\r");
    }else{
		DEBUG_OUT("NO color found\n\r");
	}
    return 0;
>>>>>>> Stashed changes
}

/**
  * @brief  map the frequency from sensor to RGB value 0-255 (FF)
  * @param  freq    frequency of the color
  *         color   desired color
  * @retval RGB value 
  */
uint8_t FrequencyToColourVal(uint16_t freq, uint8_t color) {
	if (!freq) { return 0; } //bad frequency, don't return a color
	
    uint8_t RGBValue = 0;
	switch (color) {
        //if the frequency is low there is a high color occurance
		case REDCASE: //red
		    RGBValue = map(freq, MINREDFREQ, MAXREDFREQ, 255, 0);
            break;
		case GREENCASE: //green
		    RGBValue = map(freq, MINGREENFREQ, MAXGREENFREQ, 255, 0);
            break;
		case BLUECASE: //blue
		    RGBValue = map(freq, MINBLUEFREQ, MAXBLUEFREQ, 255, 0);
            break;
	}
	//check on out of bounds
    if (RGBValue<0) { RGBValue = 0; }
	if (RGBValue>255) { RGBValue = 255; }
	
    return RGBValue;
}

/**
  * @brief  reads out raw value of the desired color
  * @param  color you want to read out (0 = red, 1 = green, 2 = blue)
  * @retval Selected color (if color = 0 the raw value of red is returned)
  */
uint16_t getColor(uint8_t color){
/**     Select desired color using this table
  * 
  *     =========================
  *     |Photodiode |S2   |S3   |
  *     |-----------|-----|-----|
  *     |Red        |Low  |Low  |
  *     |Green      |HiGH |High |
  *     |Blue       |Low  |High |
  *     |No filter  |High |Low  |
  *     =========================
 */
<<<<<<< Updated upstream
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
=======
    switch (color) {
        case REDCASE: //red
		    PORTH_OUTCLR = (1<<PIN_S2); //S2, to LOW
		    PORTH_OUTCLR = (1<<PIN_S3); //S3, to LOW
		    break;
		
		case GREENCASE: //green
		    PORTH_OUTSET = (1<<PIN_S2); //S2, to HIGH
		    PORTH_OUTSET = (1<<PIN_S3); //S3, to HIGH
    		break;
		
		case BLUECASE: //blue
	    	PORTH_OUTCLR = (1<<PIN_S2); //S2, to LOW
    		PORTH_OUTSET = (1<<PIN_S3); //S3, to HIGH
		    break;
    }
    return (uint16_t) pulseIn(&PORTJ, PIN6_bm, 0, 10000); //pin 10
>>>>>>> Stashed changes
}

/**
  * @brief  calculate average value in array
  * @param  a       array
  *         size    size of the array
  * @retval sum = average of the array
  */
uint16_t calcAverageArray(uint16_t *a, uint8_t size) {
	unsigned long sum = 0;
	for (uint8_t i=0; i<size; i++) {
		sum += a[i];
	}
	sum /= size;
	return sum;
}

/* blockly functie - functie ter vervanging van werking met char* omdat blockly problemen met kleuren => assembly heeft */
uint16_t SelectColour(uint16_t i) { return i; }

/* blockly functie */
bool CompareColours(uint16_t c1, uint16_t c2) {
	return (c1 == c2);
}

/**
  * @brief  map value (arduino function)
  * @reference https://www.arduino.cc/reference/en/language/functions/math/map/ 
  * @retval the mapped value
  */
long map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}