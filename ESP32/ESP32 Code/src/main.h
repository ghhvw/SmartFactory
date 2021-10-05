// Global libraries
#include <WiFi.h>
#include <Wire.h>
#include <ESPmDNS.h>
#include <SD.h>

// Project libraries
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>

// Custom files
#include <WebHelper.h>

//prototypes functions
void initCommunication(void);
void initWifi(void);
void initHTML(void);
void initSDCard(void);

void debugHTML(void);

//Variables
const bool STA_mode = false; //true voor STA mode false voor AP mode

const char *host = "Arexx";

const char* ssid = "Smart-Factory-AP";
const char* password = "0123456789";

const uint32_t spi_speed = 8000000;
const uint8_t max_files = 20; //vergroot dit wanneer je "VFSFileImpl(): fopen(/...) failed" errors krijgt en de webpage slecht laadt

SPIClass spiSD(HSPI);

AsyncWebServer server(80);
DNSServer dns;