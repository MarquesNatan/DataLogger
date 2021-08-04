/*============================================================================*/
#include <string.h>
/*============================================================================*/
#include "bluetooth_hc_06.h"
#include "../../pic18f4520/serial/serial.h"

/*============================================================================*/
void Bluetooth_HC_06_Configure(void) {
    uint16_t timeOut = 0xFFFF;
    uint8_t response_bluetooth[10];
    
    // Set Bluetooth baud rate
    if (BLUETOOTH_BAUD != BLUETOOTH_DEFAULT_BAUD) {
        switch (BLUETOOTH_DEFAULT_BAUD)
        {
            case 1200:
                strcat(BLUETOOTH_BAUD_COMM, "1");
                break;
            case 2400:
                strcat(BLUETOOTH_BAUD_COMM, "2");
                break;
            case 4800:
                strcat(BLUETOOTH_BAUD_COMM, "3");
                break;
            case 9600:
                strcat(BLUETOOTH_BAUD_COMM, "4");
                break;
            case 19200:
                strcat(BLUETOOTH_BAUD_COMM, "5");
                break;
            case 38400:
                strcat(BLUETOOTH_BAUD_COMM, "6");
                break;
            case 57600:
                strcat(BLUETOOTH_BAUD_COMM, "7");
                break;
            case 115200:
                strcat(BLUETOOTH_BAUD_COMM, "8");
                break;
            default:
                strcat(BLUETOOTH_BAUD_COMM, "4");
                break;
        }
        Serial_TransmitBuffer(BLUETOOTH_BAUD_COMM, sizeof (BLUETOOTH_BAUD_COMM));   
    }
    
    // Configure Module name: default: HC06
}

/*============================================================================*/