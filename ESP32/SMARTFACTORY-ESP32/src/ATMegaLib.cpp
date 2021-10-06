#include <ATMegaLib.h>
#include <Constants.h>

#define ATMegaAddress 0x20 // HardCoded address needs to be the same as in the ATMega slave code

bool transmissionRunning = false;
uint8_t ATmegaStatus = 1; //wordt 0 vóór transmission


void resetATmega() {
    // Reset processor
    DBG_OUT.println("Resetting AVR");

    digitalWrite(RESET_PIN, LOW);
    delay(10);
    digitalWrite(RESET_PIN, HIGH);
}


void programATmega(uint8_t *data, size_t length)
{
    ATmegaStatus = 0;
    if (transmissionRunning)
        return;

    resetATmega();

    delay(500); // Give the AVR some time to start up (note: programming should be started within 1 second after the reset)

    DBG_OUT.println("Writing code");

    for (size_t i = 0; i < length; i++)
    {
        if (data[i] == ':' && transmissionRunning == false)
        {
            Wire.beginTransmission(ATMegaAddress);
            transmissionRunning = true;
        }

        if ((data[i] == '\r' || data[i] == '\n'))
        {
            if (transmissionRunning)
            {
                DBG_OUT.println("stopping twi");
                //delay(20);
                Wire.endTransmission(true);
                transmissionRunning = false;
                delay(20);
            }
            continue;
        }
        else
        {
            DBG_OUT.println(data[i]);
            Wire.write(data[i]);
        }
    }
    if (transmissionRunning)
    {
        //delay(20);
        Wire.endTransmission(true);
        transmissionRunning = false;
        DBG_OUT.print("twi complete");
    }

    DBG_OUT.print("Writing complete");
}


uint8_t getATmegaStatus() { return ATmegaStatus; }
void setATmegaStatus(uint8_t i) { ATmegaStatus = i; }
bool getTransmissionRunning() { return transmissionRunning; }
void setTransmissionRunning(bool i) { transmissionRunning = i; }


/*
 * Onderstaande functie stuurt, in plaats van de te draaien blockly code de char 's'. 
 * Bij het ontvangen komt de ATmega in een endless loop waarin het wacht op commando's 
 * voor het aansturen van de stepperdrivers. 
 */
void testStepperDrivers() {
    resetATmega();

    delay(500); // Give the AVR some time to start up

    transmissionRunning = true; //check is niet nodig door reset
    DBG_OUT.println("Entering stepper-test mode");
    Wire.beginTransmission(ATMegaAddress);
    DBG_OUT.println('s');
    Wire.write('s');
    DBG_OUT.println("stopping twi");
    Wire.endTransmission();
    DBG_OUT.println("twi complete");
    transmissionRunning = false;

    /*
     * De ATmega zal weer blockly code draaien wanneer deze restart of als er nieuwe 
     * blockly code geuploaded wordt. 
     */
}


bool writeATmegaIfAvailable(uint8_t* buffer, uint8_t bufferLength) {
    if (transmissionRunning) { return false; }
    transmissionRunning = true;
    writeATmega(buffer, bufferLength);
    transmissionRunning = false;
    return true;
}


void writeATmega(uint8_t* buffer, uint8_t bufferLength) {
    Wire.beginTransmission(ATMegaAddress);
    for (int i=0; i<bufferLength; i++) {
        Wire.write((uint8_t) buffer[i]);
    }
    Wire.endTransmission();
}


void requestATmegaStatus() {
    if (transmissionRunning) { return; }
    transmissionRunning = true;
    DBG_OUT.print("Requesting ATMegaStarted\n\r");
    ATmegaStatus = readATmegaReply();
    transmissionRunning = false;
}


/* lees 1 byte van ATmega, TODO vervang deze functie met een dynamische */
uint8_t readATmegaReply() {
    uint8_t reply = 0;
    Wire.requestFrom(ATMegaAddress, 1); //request 1 byte
    while (Wire.available()) { //buffer leegmaken en enige of laatste byte gebruiken
        reply = Wire.read();
        DBG_OUT.printf("TWI feedback: %d\n\r", reply);
    }
    return reply;
}