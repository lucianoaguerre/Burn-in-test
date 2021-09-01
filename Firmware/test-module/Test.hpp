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
                test_state = 2;
              }
              else
              {
                Serial.print("Tension ok comienza el ciclo");
                cycle_state = 1;
                test_state = 1;
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
              test_state = 2;
              cycle_state = 8;
              break;
              
        case 7:
              Serial.println("FIN sin error");
              digitalWrite(LED_RED,LOW);
              digitalWrite(LED_GREEN,HIGH);
              digitalWrite(ACT,LOW);
              test_state = 3;
              cycle_state = 8;
              break;
        case 8:
              {
                      
              }
        default:
              break;
      }

}

//**** END OF FILE **********************************************************************
