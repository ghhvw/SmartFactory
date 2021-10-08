#include <Constants.h>

// Global libraries
#include <WiFi.h>
#include <Wire.h>
#include <ESPmDNS.h>
#include <SD.h>
#include <Preferences.h>

// Project libraries
#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>

// Custom files
#include <WebHelper.h>

//Debug level:
#define LOG_LOCAL_LEVEL 4

const char *host = "arexx";
const uint32_t spi_speed = 4000000;
const uint8_t max_files = 20; //vergroot dit wanneer je "VFSFileImpl(): fopen(/...) failed" errors krijgt en de webpage slecht laadt

SPIClass spiSD(HSPI);

AsyncWebServer server(80);
DNSServer dns;

Preferences preferences; //for using non-volatile storage on ESP32

/**
 * PIN DEFINITIONS
 */
//I2C pins:
#define RESET_PIN 27
#define SDA_PIN 16
#define SCL_PIN 17

//Sd SPI pins:
#define SD_CS 5U
#define SD_MOSI 23
#define SD_MISO 19
#define SD_SCLK 18

#define DBG_OUT Serial
#define BAUD_RATE 115200

#define HEAP_DEBUG_DELAY 30000

#define CHANGE_WIFI_MODE WIFI_MODE_STA

//Function prototypes:
void heapTask(void *args); //For debugging print free heap memory

void initI2C(void);
void initDebug(void);
void initSDCard(void);
void setWifiMode(wifi_mode_t wifi_mode);
void checkStatus(void);
void switchWifi(void);

