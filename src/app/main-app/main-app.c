/*============================================================================*/
#include <stdio.h>
#include "main-app.h"
/*============================================================================*/
#include "../../board/peripheral-controller/peripheral_controller.h"

/*============================================================================*/
void main_application( void* args)
{
    
    
}
/*============================================================================*/
void StartSystem( void* args )
{
    
    // START PERIPHERAL
    Peripheral_Controller(NULL);
    
    
    // START DISPLAY    - TEST DISPLAY
    // START DHT11      - TEST DHT11
    // START RAM        - TEST RAM
    // START BLUETOOTH  - TEST BLUETOOTH
}
/*============================================================================*/