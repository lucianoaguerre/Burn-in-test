/******************************************************************************
* Constants Definitions
*******************************************************************************/

const float     MIN_VOLT = 10.8;    //tension minima de falla (12V -10%)
const uint16_t  MILS2SEC = 1000;
const uint16_t  INTERVALO_C = 5 * MILS2SEC;     // 5 Segundos
const uint16_t  INTERVALO_L = 60 * MILS2SEC;    // 60 segundos


/******************************************************************************
* Variable Definitions
*******************************************************************************/
uint16_t        cycle_state = 0;   
uint16_t        cycle_loop_c = 0;  // tiempo de ciclo corto
uint16_t        cycle_loop_l = 0;  // tiempo de ciclo largo
unsigned long   tiempo = 0;        // se usa para contar mseg
float           tension_entrada = 0; //aca se guarda el valor en V de la fuente
uint8_t         test_state = 0;   // Este valor es el que se pasa al BLE.
