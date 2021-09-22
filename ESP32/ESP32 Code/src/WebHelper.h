// Global libraries
#include <SD.h>

// Project libraries
#include <ESPAsyncWebServer.h>

// Custom files
#include <ATMegaLib.h>

// Methods
void returnOK(AsyncWebServerRequest *request);
void returnFail(AsyncWebServerRequest *request, String msg);
void HandleDefault(AsyncWebServerRequest *request);
void HandleSDUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final);
