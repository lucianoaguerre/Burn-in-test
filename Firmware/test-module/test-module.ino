/*******************************************************************************
* Title                 :   Module for Burn in Test   
* Filename              :   test-module.ino
* Author                :   Luciano Aguerre
* Origin Date           :   19/05/2021
* Version               :   0.1.0
* Compiler              :   Arduino 1.8.13
* Target                :   ESP-WROOM-32
* Notes                 :   None
*******************************************************************************/


/******************************************************************************
* Libraries needed
* *****************************************************************************
* 
*******************************************************************************/

/******************************************************************************
* Funcional description
* El circuito realiza un ciclado para el burn- test de fuentes de alimentacion
* luego hace un advertizing de los resultados del ensayo a travez de BLE 
* 
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
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

const float     MIN_VOLT = 10.8;    //12V -10%
const int       MILS2SEC = 1000;
const int       INTERVALO_C = 5 * MILS2SEC;     // 5 Segundos
const int       INTERVALO_L = 60 * MILS2SEC;    // 60 segundos

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define         SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define         CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
const char*     DEVICE_NAME = "PIXART-BIT-0001";

/******************************************************************************
* Variable Definitions
*******************************************************************************/
int             statusCode;
String          content;

int             cycle_state = 0;
int             cycle_loop_c = 0;
int             cycle_loop_l = 0;
unsigned long   tiempo = 0;
float           tension_entrada = 0;

byte            val = 0;
BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
/******************************************************************************
* Functions Declarations
*******************************************************************************/
void hardware_cfg(void);
void read_adc (void);

/******************************************************************************
* Setup
*******************************************************************************/
void setup()
{
  hardware_cfg();
  BLE_cfg();
  Serial.begin(115200); 

  cycle_state = 0;
  Serial.println("Setup terminado");
  
  Serial.println("Secuencia de inicio");
  digitalWrite(LED_RED, HIGH);
  delay(300);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  delay(300);
  digitalWrite(LED_GREEN, LOW);
 
}

/******************************************************************************
* Loop
* 
*******************************************************************************/
void loop() 
{
     //test_procedure();
     BLE_send_data();
     delay(2000);
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
    float factor = 105.315;     // (2^11 bits) / {(33k/5k6) * 3.3v }
    float adc_tension = 0;
    int adc_raw = adc1_get_raw(ADC1_CHANNEL_4);
    adc_tension = (float) adc_raw / factor;  
    if (tension_entrada == 0)
    {
      tension_entrada = adc_tension;
    }
    else
    {
      tension_entrada = (tension_entrada + adc_tension) / 2;
    }
}

void BLE_cfg (void)
{
  BLEDevice::init(DEVICE_NAME);
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("data");
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT,ESP_PWR_LVL_P9);   
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9);      
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN, ESP_PWR_LVL_P9);      
  
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void BLE_send_data (void)
{
  pAdvertising->stop();
  String _val = String(val++);
  BLEAdvertisementData data;
  data.setFlags(0x6);
  data.setManufacturerData(_val.c_str());
  pAdvertising->setAdvertisementData(data);
  pAdvertising->start();
}

void test_procedure (void)
{
  switch (cycle_state)
      {
        case 0:
              read_adc();
              Serial.print(tension_entrada);
              if (tension_entrada < MIN_VOLT)
              {
                Serial.println("error");
                cycle_state = 6;
              }
              else
              {
                Serial.print("Tension ok comienza el ciclo");
                cycle_state = 1;
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
//**** END OF FILE **********************************************************************
