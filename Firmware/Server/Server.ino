/*******************************************************************************
* Title                 :   Server Module for Burn in Test   
* Filename              :   Server.ino
* Author                :   Luciano Aguerre
* Origin Date           :   13/07/2021
* Version               :   0.1.0
* Compiler              :   Arduino 1.8.13
* Target                :   ESP-WROOM-32
* Notes                 :   None
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
#include <BLEDevice.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "API.hpp"
#include "WebSockets.hpp"
#include "Server.hpp"
#include "ESP32_Utils.hpp"
#include "ESP32_Utils_AWS.hpp"
#include "BLE_Utils.hpp"

/******************************************************************************
* Variable Definitions
*******************************************************************************/
//byte   dev_state[100];

/******************************************************************************
* Functions Declarations
*******************************************************************************/
void InitDEVstates(void);

/******************************************************************************
* Setup
*******************************************************************************/
void setup(void)
{
	Serial.begin(115200);
	SPIFFS.begin();
	
	ConnectWiFi_STA();

	InitServer();
	InitWebSockets();
  InitDEVstates();
}

/******************************************************************************
* Loop
* 
*******************************************************************************/
void loop(void)
{
}

/******************************************************************************
* Functions Definitions
*******************************************************************************/
void InitDEVstates(void)
{
  for (byte i = 0; i < 100;i++)
  {
    dev_state[i] = random(0,4);
  }
}
//**** END OF FILE **********************************************************************
