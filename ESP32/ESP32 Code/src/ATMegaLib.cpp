#include <ATMegaLib.h>
#include <Constants.h>

#define ATMegaAddress 0x20 // HardCoded address needs to be the same as in the ATMega slave code

bool transmissionRunning = false;
uint8_t ATmegaStatus = 1; //wordt 0 vóór transmission
bool    FbFirstReceivedEthernetPacket = true;

void resetATmega() {
    // Reset processor
    DBG_OUT.println("Resetting AVR");

    digitalWrite(RESET_PIN, LOW);
    delay(10);
    digitalWrite(RESET_PIN, HIGH);
}


//------------------------------------------------------------------------------------------------------------------------
// Onderstaande functie wordt bij grotere blocky programma's meerdere malen aangeroepen.
// Dit heeft hoogstwaarschijnlijk te maken met het feit dat maximaal 1518 bytes per ethernet pakket verzonden kunnen
// worden en wanneer de over te zenden data groter is dan worden navenant meerdere pakketten verzonden en wordt dus
// onderstaande functie navenant meer aangeroepen.
// Google: ethernet max packet size
//------------------------------------------------------------------------------------------------------------------------
// Let op: Blockly javascript genereerd en Intel-hex programma bestand genaamd 'program (n).hex' welk hex bestand naar
// de ATMega uC wordt verzonden. Alle data uit dit gewoon leesbare ASCII-Hex bestand wordt naar de ATMega verzonden
// behalve de terugloop-wagen = carriage-return (CR) en volgende-regel = line-feed (LF) karakters.
//------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------
// Voorbeeld van het begin van een Intel hex bestand.
// Dit bestand bevat gewoon leesbare ascii hex.
// Iedere regel wordt afgesloten met een 'onderwater' CR/LF combinatie (0x0A/0x0D)
//------------------------------------------------------------
// :020000040800F2
// :10000000D81E0020FD010008039E00080D9E000878 (CR/Lf)
// :10001000179E0008219E00082B9E0008000000008B (CR/Lf)
// :10002000000000000000000000000000359E0008F5 (CR/Lf)
// :100030003F9E000800000000499E0008539E0008F3 (CR/Lf)
//------------------------------------------------------------
// : <--- start code ':' = 58 = 0x3A
// | || <--- aantal databytes in deze regel
// |  | |||| <--- doel flash adres
// |  |    | || <--- regel/record type
// |  |    |  | |||||||||||||||||||||||||||||||| <--- maximaal 16 databytes per regel
// |  |    |  | |                              | || <--- checksum
// |  |    |  | |                              |  |
// v  v    v  v v                              v  v
// : 02 0000 04 0800                             F2 (verzonden hex data = 0x3A 0x30 0x32 0x30 ...)
// : 10 0000 00 D81E0020FD010008039E00080D9E0008 78
// : 10 0010 00 179E0008219E00082B9E000800000000 8B
// : 10 0020 00 000000000000000000000000359E0008 F5
// : 10 0030 00 3F9E000800000000499E0008539E0008 F3
//------------------------------------------------------------
//============================================================
//  PROGRAM ATMEGA (aangepast: hvw202201271954)
//============================================================
void programATmega(uint8_t *data, size_t length, bool final){
    //reset wat???
    ATmegaStatus = 0;
    //het betreft hier de het allereerste ontvangen ethernet pakket
    if (FbFirstReceivedEthernetPacket){
        //accepteer de melding door deze weg te nemen
        FbFirstReceivedEthernetPacket = false;
        //markeer de i2c communicatie met de atmega als zijnde bezig
        transmissionRunning = true;
        //----------------------------------------------------------------------------------------------------
        // initialiseer de i2c peripheral om data te zenden naar de i2c slave met adress ATMegaAddress (0x20)
        //----------------------------------------------------------------------------------------------------
        //initialiseer de i2c peripheral (beginTransmission verzend niets, zou beter 'Wire.initTransmission()' kunnen heten)
        Wire.beginTransmission(ATMegaAddress);
        //herstart de atmega uC zodat de atmega uC in de i2c ontvangst/flash mode kan komen
        resetATmega();
        //wacht een tijdje na de atmega opstart om de atmega in het 2,5 seconden i2c ontvangst/flash venster te laten aankomen
        delay(500); // origineel commentaar: Give the AVR some time to start up (note: programming should be started within 1 second after the reset)
    }//if
    //dit is niet het laatst ontvangen ethernet pakket
    if (!final){
        //toon een debug mededeling
        DBG_OUT.println("Some ethernet packet received, starting Writing code");
    }//if
    //dit is het laatst ontvangen ethernet pakket
    else{
        //toon een debug mededeling
        DBG_OUT.println("Last ethernet packet received, starting Writing code");
    }//else
    //behandel alle te verzenden i2c bytes van het huidige ethernet pakket uit het door javascript gegenereerde blockly Intel-hex bestand met atmega programmacode
    for (size_t i = 0; i < length; i++){
        //het huidig te verzenden karakter is een carriage-return (terugloop wagen) of een new-line (nieuwe regel) karakter (aan het eind van iedere intel-hex bestands regel)
        if ((data[i] == '\r' || data[i] == '\n')) {
            //toon een debug mededeling
            DBG_OUT.println("crlf");
            //------------------------------------------------------------------------------------------------------------------------
            // blijkbaar wordt een I2C timeout gegenereerd wanneer teveel bytes domweg achter elkaar verzonden worden.
            // Een workaround is om na elke verzonden intel-hex file regel (met maximaal 16 bytes) de verzending te onderbreken zonder
            // daarbij een STOP conditie te genereren. Vermoedelijk wordt de timeout bewaking gereset na uitvoering van een
            // Wire.endtransmission(false) false = geen STOP conditie genereren.
            //------------------------------------------------------------------------------------------------------------------------
            //stop tijdelijk de transmissie maar genereer geen STOP conditie
            Wire.endTransmission(false);
            //ga verder met het volgende te verzenden karakter
            continue;
        }//if
        //het huidige te verzenden karakter is geen carriage-return of new-line karakter
        else{
            //toon het huidige te verzenden karakter in het debug venster
            DBG_OUT.println(data[i]);
            //zend het huidige karakter naar de atmega
            Wire.write(data[i]);
        }//else
    }//for: behandel alle te verzenden i2c bytes
    //--------------------------------------------------
    //op dit punt zijn alle bytes van het huidige ethernet pakket verzonden
    //--------------------------------------------------
    //de i2c communicatie is nog bezig
    if (transmissionRunning){
        //zend wel of niet een stop bericht (false of true) naar de i2c slave afhankelijk of het huidige ethernet pakket wel of niet het laatste pakket is
        Wire.endTransmission(final);
        //dit was het laatste ontvangen ethernet pakket
        if (final){
            //markeer de i2c communicatie als zijnde afgelopen/klaar
            transmissionRunning = false;
            //toon een debug mededeling
            DBG_OUT.println("twi complete");
            //zet alvast weer de eerste ethernet pakket ontvangst vlag voor een eventuele volgende flash actie klaar
            FbFirstReceivedEthernetPacket=true;
        }//if
    }//if
}//programATmega


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