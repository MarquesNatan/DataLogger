/*============================================================================*/
#include <stdio.h>
#include "main-app.h"
#include "../../board/board_definitions/board_definitions.h"
/*============================================================================*/
#include "../../board/peripheral-controller/peripheral_controller.h"
#include "../../app/display_lcd/display_lcd.h"
#include "../../app/dht11/dht11.h"
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
    
    
    // START DHT11      - TEST DHT11
    // START RAM        - TEST RAM
}
/*============================================================================*/