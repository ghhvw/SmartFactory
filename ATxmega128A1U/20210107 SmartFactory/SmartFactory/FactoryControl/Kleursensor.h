/*
 * Kleursensor.h
 *
 * Created: 14/10/2021 09:15:38
 *  Author: Yannick
 */ 


#ifndef KLEURSENSOR_H_
<<<<<<< Updated upstream
#define KLEURSENSOR_H_

#include "UART.h" //voor char HexToASCII(uint8_t i)

#ifdef __cplusplus
extern "C" {
#endif

#ifndef F_CPU
#define F_CPU 24000000
#endif

#define COLOUR_AS_INDEX		//als dit is defined wordt er niet met char* (\#rrggbb) maar met integers gewerkt om kleuren te identificeren
//#define ALLOW_COLOURV_128	//als dit defined is is 128 toegestaan als kleurwaarde naast 0 en 255, dit werkt niet wanneer COLOUR_AS_INDEX is defined
#define COLORDEVIATION 10	//toegestane afwijking van kleuren per waarde om nog gelijk aan elkaar te zijn
#define MAXREDFREQ 19		//corresponds to R 255
#define MINREDFREQ 129		//corresponds to R 0
#define MAXGREENFREQ 60		//corresponds to G 255
#define MINGREENFREQ 160	//corresponds to G 0
#define MAXBLUEFREQ 14		//corresponds to B 255
#define MINBLUEFREQ 124		//corresponds to B 0

#include "pulseIn.h"
#include <string.h>
#include "DigitalIO.h" //voor IO_ReadWrite()


uint16_t SelectColour(uint16_t i);
#ifdef COLOUR_AS_INDEX
bool CompareColours(uint16_t c1, uint16_t c2);
uint16_t ReadColourSensor();
#else
bool CompareColours(char *c1, char *c2);
char* ReadColourSensor();
#endif
uint16_t ReadOneColour(uint8_t colour);
uint8_t ColourToIndex(char *colour);
uint8_t ColourToRed(char *colour);
uint8_t ColourToGreen(char *colour);
uint8_t ColourToBlue(char *colour);
char* ValToColour(uint8_t r, uint8_t g, uint8_t b);
uint8_t RoundColourVal(uint8_t val);
uint8_t FrequencyToColourVal(uint16_t freq, uint8_t colour);

uint16_t ArrAvg(uint16_t *a, uint8_t size);
bool CompareStrings(char *c1, char *c2, uint8_t length);
uint32_t hex2int(char *hex);
long map(long x, long in_min, long in_max, long out_min, long out_max);


#ifdef __cplusplus
}
#endif
=======
    #define KLEURSENSOR_H_

    #include "UART.h" //voor char HexToASCII(uint8_t i)

    #ifdef __cplusplus
        extern "C" {
    #endif

    #ifndef F_CPU
        #define F_CPU 24000000
    #endif
	
	//includes
    #include "pulseIn.h"

    //defines
    #define PIN_S2          PIN7_bp //S2, pin 11
    #define PIN_S3          PIN6_bp //S3, pin 12

    #define REDCASE         0
    #define GREENCASE       1
    #define BLUECASE        2

    #define AVERAGECOLORS   5
    #define DIFFERENTCOLORS 3

    #define MAXREDFREQ 129		    //corresponds to R 255
    #define MINREDFREQ 19		    //corresponds to R 0
    #define MAXGREENFREQ 160		//corresponds to G 255
    #define MINGREENFREQ 60	        //corresponds to G 0
    #define MAXBLUEFREQ 124		    //corresponds to B 255
    #define MINBLUEFREQ 14		    //corresponds to B 0

    //function prototypes
    void initColorSensor(void);//initialize pins
    uint16_t ReadColourSensor(void); //get colors from colorsensor
    uint16_t getColor(uint8_t color); //get one color in return

    uint8_t FrequencyToColourVal(uint16_t freq, uint8_t color);
    uint16_t calcAverageArray(uint16_t *a, uint8_t size);
	
	uint16_t SelectColour(uint16_t i);
	bool CompareColours(uint16_t c1, uint16_t c2);
	
	long map(long x, long in_min, long in_max, long out_min, long out_max);

    #ifdef __cplusplus
        }
    #endif
>>>>>>> Stashed changes

#endif /* KLEURSENSOR_H_ */