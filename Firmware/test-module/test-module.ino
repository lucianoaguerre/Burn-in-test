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
* Funcional description
* El circuito realiza un ciclado para el burn- test de fuentes de alimentacion
* luego hace un advertizing de los resultados del ensayo a travez de BLE 
* 
*******************************************************************************/

/******************************************************************************
* Includes
*******************************************************************************/
//#include <EEPROM.h>
//#include <rom/rtc.h>
#include <driver/adc.h>
//#include "soc/rtc_cntl_reg.h"

#include "Hardware_Def.h"
#include "Memory.h"
#include "ADC_Utils.hpp"
#include "Test.hpp"
#include "BLE_Functions.hpp"

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

  BLE_setup();
}

/******************************************************************************
* Loop
* 
*******************************************************************************/
void loop() 
{
     test_procedure();
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


//**** END OF FILE **********************************************************************
