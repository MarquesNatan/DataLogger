/*============================================================================*/
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
/*============================================================================*/
// Oscillator Freq
#define _XTAL_FREQ          10000000UL

// Peripheral Definitions
#define SERIAL_INTERFACE    UART
#define UART_BAUD           9600


// Board Definitions
#define BOARD_NAME          "DATA LOGGER v0.01"
#define BOARD_PIN           "1234"


#define START_BLUETOOTH     "START_BLUETOOTH"


// DHT11 STRINGS
#define DHT11_WORKING       "DHT11 OK"
#define DHT11_TIMEOUT       "DHT11 TIMEOUT"


// Data logger Commands
#define DATA_LOGGER_SEND_BACKUP     "<SBK>"
#define DATA_LOGGER_DELETE_BACKUP   "<DBK>"

/*============================================================================*/
#endif	/* BOARD_DEFINITIONS_H */
/*============================================================================*/
