/*******************************************************************************
* Title                 :   Module for Burn in Test   
* Filename              :   test-module.ino
* Author                :   Luciano Aguerre
* Origin Date           :   19/05/2021
* Version               :   0.1.0
* Compiler              :   Arduino 1.8.13
* Target                :   ESP-WROOM-32
* Notes                 :   None
*
*******************************************************************************/

/******************************************************************************
* Libraries needed
* *****************************************************************************
* AsyncHTTPRequest_Generic
* AsyncTCP
* ESP_Mail_Client
* ESP32_Mail_Client
* ESPAsyncWebServer
* WifiManager
* Time - Michael Margolis
* TimeAlarms - Michael Margolis
* DS1307RTC - Michael Margolis
* NTPClient - Fabrice Weinberg
* 
*******************************************************************************/

/******************************************************************************
* Funcional description
* 
* 
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include <EEPROM.h>
#include <rom/rtc.h>
#include <driver/adc.h>
#include "soc/rtc_cntl_reg.h"

/******************************************************************************
* Hardware definitions
*******************************************************************************/

#define LED_RED     27 
#define LED_GREEN   13
#define VIN         32
#define ACT         26 


/******************************************************************************
* Typedefs
*******************************************************************************/

/******************************************************************************
* Constants Definitions
*******************************************************************************/
const char*     ssid = "Default SSID";
const char*     passphrase = "Default passord";
//const char* network = "UTORAK_NET";
const char*     network = "WIFI_TEST";

const float     MIN_VOLT = 10.8;    //12V -10%
const int       MILS2SEC = 1000;
const int       INTERVALO_C = 5 * MILS2SEC;     // 5 Segundos
const int       INTERVALO_L = 60 * MILS2SEC;    // 60 segundos

/******************************************************************************
* Variable Definitions
*******************************************************************************/
//int             i = 0;
int             statusCode;
String          content;
String          esid;
String          epass = "";
WebServer       server(80);

int             cycle_state = 0;
int             cycle_loop_c = 0;
int             cycle_loop_l = 0;
unsigned long   tiempo = 0;
float           tension_entrada = 0;


/******************************************************************************
* Functions Declarations
*******************************************************************************/
void wifi_provisioning(void);
void wifi_provisioning_launchWeb(void);
void wifi_provisioning_setupAP(void);
void clear_eeprom(void);
void read_eeprom(void);
void hardware_cfg(void);
void read_adc (void);

/******************************************************************************
* Setup
*******************************************************************************/
void setup()
{
  hardware_cfg();
  Serial.begin(115200); 
  WiFi.disconnect();
  EEPROM.begin(512);
  delay(10);
  wifi_provisioning();

  cycle_state = 0;
}

/******************************************************************************
* Loop
* 
*******************************************************************************/
void loop() 
{
      switch (cycle_state)
      {
        case 0:
              read_adc();
              if (tension_entrada < MIN_VOLT)
              {
                Serial.println("error");
                cycle_state = 6;
              }
              break;

        case 1:
              if(millis() > (tiempo + INTERVALO_C))
              {
                digitalWrite(ACT,HIGH);
                tiempo = millis();
                cycle_state = 2;
                cycle_loop_c++;
                Serial.print(cycle_loop_c);
                Serial.println("-TON");
              }
              break;
              
        case 2:
              if(millis() > (tiempo + INTERVALO_C))
              {
                digitalWrite(ACT,LOW);
                tiempo = millis();
                if (cycle_loop_c < 11)
                {
                  cycle_state = 1;
                  cycle_loop_c++;
                }
                else
                {
                  cycle_state = 3;
                }
                Serial.print(cycle_loop_c);
                Serial.println("-TOFF");
              }
              break;
              
        case 3:
              read_adc();
              if(millis() > (tiempo + INTERVALO_L))
              {
                digitalWrite(ACT,HIGH);
                tiempo = millis();
                cycle_state = 4;
                cycle_loop_l++;
                Serial.print(cycle_loop_l);
                Serial.println("-TON Ciclo Largo");
              }
              break;
              
        case 4:
              if(millis() > (tiempo + INTERVALO_L))
              {
                digitalWrite(ACT,LOW);
                tiempo = millis();
                if (cycle_loop_l < 5)
                {
                  cycle_state = 1;
                  cycle_loop_l++;
                  cycle_loop_c = 0;
                }
                else
                {
                  cycle_state = 5;
                }
                Serial.print(cycle_loop_l);
                Serial.println("-TOFF Ciclo Largo");
              }
              break;
              
        case 5:
               if (tension_entrada < MIN_VOLT)
              {
                cycle_state = 6;
              }
              else
              {
                cycle_state = 7;
              }
              break;
              
        case 6:
              Serial.println("FIN con error");
              digitalWrite(LED_RED,HIGH);
              digitalWrite(LED_GREEN,LOW);
              digitalWrite(ACT,LOW);
              while (1)
              {
              }
              break;
              
        case 7:
              Serial.println("FIN sin error");
              digitalWrite(LED_RED,LOW);
              digitalWrite(LED_GREEN,HIGH);
              digitalWrite(ACT,LOW);
              while (1)
              {
              }
              break;
              
        default:
              break;
      }

}

/******************************************************************************
* Functions Definitions
*******************************************************************************/
void hardware_cfg (void)
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(ACT, OUTPUT);
  pinMode(VIN, INPUT);
  
  digitalWrite(LED_RED,LOW);
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(ACT,LOW);
  
  adc1_config_width(ADC_WIDTH_BIT_11);
  adc1_config_channel_atten(ADC1_CHANNEL_4,ADC_ATTEN_DB_11);
}

void read_adc (void)
{
    float factor = 2048 / 13.2;
    float adc_tension = 0;
    int adc_raw = adc1_get_raw(ADC1_CHANNEL_4);
    adc_tension = (float) adc_raw / factor;  // (2 x 3.7V /4095)
    if (tension_entrada == 0)
    {
      tension_entrada = adc_tension;
    }
    else
    {
      tension_entrada = (tension_entrada + adc_tension) / 2;
    }
}

void clear_eeprom (void)
{
  Serial.println("clearing eeprom");
  for (int i = 0; i < 96; ++i) 
  {
    EEPROM.write(i, 0);
  }
}

void read_eeprom (void)
{
  for (int i = 0; i < 32; ++i)
  {
    esid += char(EEPROM.read(i));
  } 
  for (int i = 32; i < 96; ++i)
  {
    epass += char(EEPROM.read(i));
  }
}
        
void wifi_provisioning (void)
{
  read_eeprom();
  WiFi.begin(esid.c_str(), epass.c_str());
  for (int i = 0; i < 10; ++i)
  {
    delay(1000);
  } 
  
  if ((WiFi.status() == WL_CONNECTED))
  {
      Serial.print("Connected to ");
      Serial.print(esid);
      Serial.println(" Successfully");
      delay(100);
  }
  else
  {
    Serial.println("Turning the HotSpot On");
    wifi_provisioning_launchWeb();
    wifi_provisioning_setupAP();// Setup HotSpot
  }
  while ((WiFi.status() != WL_CONNECTED))
  {
    delay(100);
    server.handleClient();
  }
}

void wifi_provisioning_launchWeb()
{
  wifi_provisioning_createWebServer();
  server.begin();
}

void wifi_provisioning_setupAP(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.softAP(network, "");
  Serial.println("Initializing PIXART_NET WiFi");
  wifi_provisioning_launchWeb();
}

void wifi_provisioning_createWebServer()
{
  {
    server.on("/", []() 
    {
      IPAddress ip = WiFi.softAPIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      content = "<!DOCTYPE HTML>\r\n<html>PIXART Burn-In Test - Configuracion del WiFi";
      content += "<p> Ingrese los datos de su WiFi";
      content += "</p><form method='get' action='setting'><label>SSID: </label><input name='ssid' length=32> <label>Password: </label><input name='pass' length=64><input type='submit'></form>";
      content += "</html>";
      server.send(200, "text/html", content);
    });
    
    server.on("/setting", []() 
    {
      String qsid = server.arg("ssid");
      String qpass = server.arg("pass");
      if (qsid.length() > 0 && qpass.length() > 0) 
      {
        clear_eeprom();
        for (int i = 0; i < qsid.length(); ++i)
        {
          EEPROM.write(i, qsid[i]);
        }
        Serial.println("writing eeprom pass:");
        for (int i = 0; i < qpass.length(); ++i)
        {
          EEPROM.write(32 + i, qpass[i]);
        }
        EEPROM.commit();
        content = "{\"Success\":\"saved to eeprom... reset to boot into new wifi\"}";
        statusCode = 200;
        ESP.restart();
      } 
      else 
      { 
        content = "{\"Error\":\"404 not found\"}";
        statusCode = 404;
        Serial.println("Sending 404");
      }
      server.sendHeader("Access-Control-Allow-Origin", "*");
      server.send(statusCode, "application/json", content);
    });
  }
}






//**** END OF FILE **********************************************************************
