/*============================================================================*/
#include <stdio.h>
#include "main-app.h"
#include "../../board/board_definitions/board_definitions.h"
#include "../../pic18f4520/timer/timer.h"
/*============================================================================*/
#include "../../board/peripheral-controller/peripheral_controller.h"
#include "../../app/display_lcd/display_lcd.h"
#include "../../app/bluetooth-hc-06/bluetooth_hc_06.h"
#include "../../app/dht11/dht11.h"
/*============================================================================*/
#define FIM_INICIALIZACAO   "ACABOU ESSA POHA"
/*============================================================================*/
void main_application( void* args)
{
    
    while(1)
    {
        // Funções ciclicas
    }
    
    
}
/*============================================================================*/
void StartSystem( void* args )
{
    
    // START PERIPHERAL
    Peripheral_Controller(NULL);
    
    
    // START DISPLAY    - TEST DISPLAY
    DisplayLCD_Init();
    
    
    Display_WriteString(START_BLUETOOTH, sizeof(START_BLUETOOTH), 0);
    // START BLUETOOTH  - TEST BLUETOOTH
    Bluetooth_HC_06_Configure();
    Timer0_WaitMS(3000);
    Display_WriteString(FIM_INICIALIZACAO, sizeof(FIM_INICIALIZACAO), 0);
    // START DHT11      - TEST DHT11
    // START RAM        - TEST RAM
}
/*============================================================================*/