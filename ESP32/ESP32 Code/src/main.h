#ifndef __MAIN_H__
#define __MAIN_H__

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

//constant variables
const char *host = "arexx";
const uint32_t spi_speed = 4000000; //DO NOT TOUCH
const uint8_t max_files = 20;       //vergroot dit wanneer je "VFSFileImpl(): fopen(/...) failed" errors krijgt en de webpage slecht laadt

SPIClass spiSD(HSPI);

AsyncWebServer server(80);
DNSServer dns;

Preferences preferences; //for using non-volatile storage on ESP32

//Function prototypes:
#define HEAP_DEBUG_DELAY 30000
void heapTask(void *args); //For debugging print free heap memory

void initCommunication(void);
void initWifi(void);
void initHTML(void);
void initServer(void);
void initSDCard(void);

void switchWifiMode(void);

#endif //end if __MAIN_H__