#include <main.h>
#include <Constants.h>

<<<<<<< Updated upstream
const char *host = "Arexx";
=======
const bool STA_mode = false; //true voor STA mode false voor AP mode

const char* ssid = "Smart-Factory-AP";
const char* password = "0123456789";

>>>>>>> Stashed changes
const uint32_t spi_speed = 8000000;
const uint8_t max_files = 20; //vergroot dit wanneer je "VFSFileImpl(): fopen(/...) failed" errors krijgt en de webpage slecht laadt

SPIClass spiSD(HSPI);

AsyncWebServer server(80);
<<<<<<< Updated upstream
=======

const char *host = "arexx";
>>>>>>> Stashed changes
DNSServer dns;

void setup()
{
    // Enable I2C
    pinMode(RESET_PIN, OUTPUT);
    digitalWrite(RESET_PIN, HIGH);
    Wire.begin(SDA_PIN, SCL_PIN, 2000);

    // Debugging setup
    esp_log_level_set("*", ESP_LOG_DEBUG);
    DBG_OUT.begin(BAUD_RATE);
    DBG_OUT.setDebugOutput(true);

    // Wifi manager
<<<<<<< Updated upstream
    AsyncWiFiManager wifiManager(&server, &dns);
    wifiManager.autoConnect();
=======
    
    #if STA_mode /*STA mode*/
    AsyncWiFiManager wifiManager(&server, &dns);
    wifiManager.autoConnect();
    #else /*AP mode*/
    //AsyncWiFiManager wifiManager(&server, &dns);
    //wifiManager.autoConnect(ssid, password);

    //??????wifiManager.startConfigPortal(ssid, password);
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    DBG_OUT.print("AP IP address: ");
    DBG_OUT.println(IP);
    #endif
>>>>>>> Stashed changes

    // Custom DNS settings
    if (MDNS.begin(host))
    {
        MDNS.addService("http", "tcp", 80);
        DBG_OUT.println("MDNS responder started");
        DBG_OUT.print("You can now connect to http://");
        DBG_OUT.print(host);
        DBG_OUT.println(".local");
    }


    //verzend status naar browser (connected/disconnected)
    server.on("/status", HTTP_GET, [] (AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(1).c_str()); //1: ESP32 is nog verbonden (en ATmega bereikbaar?)
        /* als de browser bovenstaande reactie niet ontvangt plaatst het "disconnected" op de pagina */
    });


    //verzend start-feedback naar browser (start-button)
    server.on("/startfeedback", HTTP_GET, [] (AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(getATmegaStatus()).c_str());
    });


    //zet ATmega in stepper-test mode
    server.on("/test", HTTP_GET, [] (AsyncWebServerRequest *request) {
        uint8_t reply = 0;
        if (getTransmissionRunning()) {
            returnOK(request);
            return;
        }
        setTransmissionRunning(true);

        //act=0 test steppermotors, act=1 read analog port, ... TODO implement more
        if (request->hasParam("act")) { // /test?act=0&p1=0&p2=0
            uint8_t act = (uint8_t) request->getParam("act")->value().toInt();
            uint8_t p1 = 0;
            uint8_t p2 = 0;
            if (request->hasParam("p1")) {
                p1 = (uint8_t) request->getParam("p1")->value().toInt();
            }
            if (request->hasParam("p2")) {
                p2 = (uint8_t) request->getParam("p2")->value().toInt();
            }
            DBG_OUT.printf("Send act=%d p1=%d p2=%d\n\r", act, p1, p2);
            uint8_t buffer[] = {act, p1, p2};
            writeATmega((uint8_t*) buffer, 3);
            if (1 == act) { //read analog port
                delay(100); //voorkom vastlopen i2c bus
                reply = readATmegaReply();
            }
            delay(200); //delay om te voorkomen dat i2c bus (te snel) vastloopt
            setTransmissionRunning(false);
        } else {
            testStepperDrivers();
            //transmissionRunning wordt binnen testStepperDrivers() false
        }
        request->send(200, "text/plain", String(reply).c_str());
    });


    // TODO: add more handlers?
    server.on("/edit", HTTP_POST, returnOK, HandleSDUpload);
    server.onNotFound(HandleDefault);

    server.begin();
    DBG_OUT.println("HTTP server started");

    spiSD.begin(14,2,15,13);

    // SD initializer
    while (!SD.begin(SDCard_CS_PIN, spiSD, spi_speed, "/sd", max_files))
    {
        DBG_OUT.println("SD initiatization failed. Retrying.");
        delay(250);
    }
    DBG_OUT.println("SD Initialized.");
}

void loop(void)
{
    DBG_OUT.printf("RSSI = %d dbm\n\r", WiFi.RSSI());
    DBG_OUT.printf("Heap Size: %d bytes\n\r", esp_get_free_heap_size());
    delay(1000);

    #if 1
    if (!getATmegaStatus() && !getTransmissionRunning()) {
        setATmegaStatus(true);
        //start-feedback wordt bij de eerstvolgende HTTP_GET geupdated in de browser
    }
    #else
    if (!getATmegaStatus()) {
        while(getTransmissionRunning());
        delay(500); //voorkom vastlopen i2c bus na upload
        requestATmegaStatus();
        //start-feedback wordt bij de eerstvolgende HTTP_GET geupdated in de browser
    }
    #endif
}
