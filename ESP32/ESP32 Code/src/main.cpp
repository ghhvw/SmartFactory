#include <main.h>

/**
 * ===========================================
 * Arexx Engineering - Smart Factory ESP32 Code
 * 
 * 15-7-2021
 * 
 * TODO:
 * -Implement Network STA timeout and switch to AP mode
 * -Implement hardware button to switch from AP<->STA mode, instead of only on-website toggle
 */


void setup()
{
    //Disable WDT to stop AsyncTCP from crashing the CPU (TODO: find a better way to do this?)
    disableCore0WDT();
    disableCore1WDT();
    disableLoopWDT();

    initI2C();  //set pins for I2C
    initDebug();

    //Setup Preferences (Non volatile Storage)
    preferences.begin("smartFactory", false);
    
    setWifiMode(CHANGE_WIFI_MODE);  //choose between AP and STA (Can be changed in main.h)
    checkStatus(); 

    //Upload new program to Atmega
    server.on("/edit", HTTP_POST, returnOK, HandleSDUpload);

    switchWifi();//possibility to switch between AP and STA

    //Default handler:
    server.onNotFound(HandleDefault);

    //Start the server:
    server.begin();
    DBG_OUT.println("HTTP server started");

    initSDCard();   //keep checking on SD card until it's initialized

    //When debugging lauch the debug functions:
    #if LOG_LOCAL_LEVEL > 3
        xTaskCreatePinnedToCore(heapTask, "heap debug", 2048, NULL, 1, NULL, 1);
    #endif
}

void loop(void)
{

    delay(1000);

    if (!getATmegaStatus() && !getTransmissionRunning())
    {
        setATmegaStatus(true);
        //start-feedback wordt bij de eerstvolgende HTTP_GET geupdated in de browser
    }
    
    /*
    if (!getATmegaStatus())
    {
        while (getTransmissionRunning())
            ;
        delay(500); //voorkom vastlopen i2c bus na upload
        requestATmegaStatus();
        //start-feedback wordt bij de eerstvolgende HTTP_GET geupdated in de browser
    }
    */
}

void initI2C(void)
{
    // Enable I2C
    pinMode(RESET_PIN, OUTPUT);
    pinMode(SD_CS, OUTPUT);
    digitalWrite(RESET_PIN, HIGH);
    Wire.begin(SDA_PIN, SCL_PIN, 2000);
}

void initDebug(void)
{
    esp_log_level_set("*", ESP_LOG_DEBUG);
    DBG_OUT.begin(BAUD_RATE);
    DBG_OUT.setDebugOutput(true);
}

void initSDCard(void)
{
    //Ïnitialise the SPI bus for the SD card:
    spiSD.begin(SD_SCLK, SD_MISO, SD_MOSI);

    // Initialise the SD card:
    while (!SD.begin(SD_CS, spiSD, spi_speed, "/sd", max_files))
    {
        DBG_OUT.println("SD initiatization failed. Retrying.");
        delay(250);
    }
    DBG_OUT.println("SD Initialized.");
}

void heapTask(void *args)
{
    while (1)
    {
        DBG_OUT.printf("RSSI = %d dbm\n\r", WiFi.RSSI());
        DBG_OUT.printf("Heap Size: %d bytes\n\r", esp_get_free_heap_size());
        vTaskDelay(HEAP_DEBUG_DELAY / portTICK_PERIOD_MS);
    }
}

void setWifiMode(wifi_mode_t wifi_mode)
{
    //read NVS, Set default value to be AP:
    // wifi_mode_t wifi_mode = (wifi_mode_t)preferences.getUInt("wifimode", (uint32_t)WIFI_MODE_AP);

    // Wifi manager
    AsyncWiFiManager wifiManager(&server, &dns);
    if (wifi_mode == WIFI_MODE_STA)
    {
        ESP_LOGI("WiFi-Mode", "Starting in Wifi STATION mode!");
        wifiManager.autoConnect();
    }
    else if (wifi_mode == WIFI_MODE_AP)
    {
        ESP_LOGI("WiFi-Mode", "Starting in Wifi AP mode");
        WiFi.softAP("Arexx Factory AP");
    }
    else
    {
        ESP_LOGI("WiFi-Mode", "Invalid Wi-Fi mode read! Writing AP mode in NVS");
        preferences.putUInt("wifimode", (uint32_t)WIFI_MODE_AP);
    }

    // Custom DNS settings
    if (MDNS.begin(host))
    {
        MDNS.addService("http", "tcp", 80);
        DBG_OUT.println("MDNS responder started");
        DBG_OUT.print("You can now connect to http://");
        DBG_OUT.print(host);
        DBG_OUT.println(".local/");
    }
}

void checkStatus(void)
{
    //verzend status naar browser (connected/disconnected)
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->send(200, "text/plain", String(1).c_str()); //1: ESP32 is nog verbonden (en ATmega bereikbaar?)
                  /* als de browser bovenstaande reactie niet ontvangt plaatst het "disconnected" op de pagina */
              });

    //verzend start-feedback naar browser (start-button)
    server.on("/startfeedback", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", String(getATmegaStatus()).c_str()); });

    //zet ATmega in stepper-test mode
    server.on("/test", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  uint8_t reply = 0;
                  if (getTransmissionRunning())
                  {
                      returnOK(request);
                      return;
                  }
                  setTransmissionRunning(true);

                  //act=0 test steppermotors, act=1 read analog port, ... TODO implement more
                  if (request->hasParam("act"))
                  { // /test?act=0&p1=0&p2=0
                      uint8_t act = (uint8_t)request->getParam("act")->value().toInt();
                      uint8_t p1 = 0;
                      uint8_t p2 = 0;
                      if (request->hasParam("p1"))
                      {
                          p1 = (uint8_t)request->getParam("p1")->value().toInt();
                      }
                      if (request->hasParam("p2"))
                      {
                          p2 = (uint8_t)request->getParam("p2")->value().toInt();
                      }
                      DBG_OUT.printf("Send act=%d p1=%d p2=%d\n\r", act, p1, p2);
                      uint8_t buffer[] = {act, p1, p2};
                      writeATmega((uint8_t *)buffer, 3);
                      if (1 == act)
                      {               //read analog port
                          delay(100); //voorkom vastlopen i2c bus
                          reply = readATmegaReply();
                      }
                      delay(200); //delay om te voorkomen dat i2c bus (te snel) vastloopt
                      setTransmissionRunning(false);
                  }
                  else
                  {
                      testStepperDrivers();
                      //transmissionRunning wordt binnen testStepperDrivers() false
                  }
                  request->send(200, "text/plain", String(reply).c_str());
              });
}

void switchWifi(void)
{
    //Switch between AP/STA mode:
    server.on("/switchWiFi", HTTP_POST, [](AsyncWebServerRequest *request)
              {
                  DBG_OUT.println("WiFi Button Was Pressed");
                  wifi_mode_t wifi_current_mode = (wifi_mode_t)preferences.getUInt("wifimode", (uint32_t)WIFI_MODE_AP);
                  if (wifi_current_mode == WIFI_MODE_AP)
                  {
                      ESP_LOGI("WifiMode", "Switching from AP to STA!");
                      preferences.putUInt("wifimode", (uint32_t)WIFI_MODE_STA);
                      vTaskDelay(1000 / portTICK_PERIOD_MS);
                      esp_restart();
                  }
                  else
                  {
                      ESP_LOGI("WifiMode", "Switching from STA to AP!");
                      preferences.putUInt("wifimode", (uint32_t)WIFI_MODE_AP);
                      vTaskDelay(1000 / portTICK_PERIOD_MS);
                      esp_restart();
                  }
              });
}