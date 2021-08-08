/*=============================================================================
 *      Sensor DHT 11 https://img.filipeflop.com/files/download/Datasheet_DHT11.pdf
 *       _______    _______           _______         _______    
 *      |       |          |         |       |       |       |       
 *      | DHT11 |          |_________|       |_______|       |___ . . . 
 *      |       |          |<-  A  ->|<- B ->|<- C ->|<- D ->|
 *      |_______|           
 *       | | | |      Legend: Initialization
 *    Vcc DT NC GND       A : request data (uc sends)  Duration : 18      ms
 *                        B : delay dht11  (dht sends) Duration:  20 ~ 40 us
 *                        C : dht response signal      Duration:  80      us
 *                        D : dht response signal      Duration:  80      us
 *                                  _______         _________
 *                         |       |       |       |         |
 *                         |_______|       |_______|         |
 *                         |<- E ->|<- D ->|<- F ->|<-  G  ->|
 *                   Legend: Response (byte)
 *                        E: Signal for next bit        Duration: 50      us
 *                        D: Signal of 0                Duration: 26 ~ 28 us
 *                        F: Signal for next bit        Duration: 50      us
 *                        G: Signal of 1                Duration: 70      us
 * 
 * Data presentation: 
 *  TEMP:   XX.X -> temp[2] = {XX, X}
 *  HUM:    YY.Y
 * 1° step: 
 *      vetAux[3] -> strcat(vetAux, temp)
 =============================================================================*/
#include "dht11.h"
#include "../../board/board_definitions/board_definitions.h"
#include "../../pic18f4520/gpio/gpio.h"
#include "../../board/pinout/pinout.h"
#include "../../pic18f4520/timer/timer.h"
#include "../../pic18f4520/serial/serial.h"




#include "../display_lcd/display_lcd.h"
#include "../../pic18f4520/serial/serial.h"
/*============================================================================*/
static  uint8_t temperature [2]; // [TEMP HIGH BYTE][TEMP LOW BYTE]
static uint8_t humidity [2]; // [HUM HIGH BYTE][HUM LOW BYTE]



void DHT11_Start( void )
{
    PIN_CONFIGURE_DIGITAL(PIN_OUTPUT, DHT11_DATA_PORT, DHT11_DATA_MASK);
    PIN_DIGITAL_WRITE(PIN_LOW, DHT11_DATA_PORT, DHT11_DATA_MASK);
    
    __delay_ms(20);
    PIN_CONFIGURE_DIGITAL(PIN_INPUT, DHT11_DATA_PORT, DHT11_DATA_MASK);
}

void DHT11_Check_Response (void)  
{
	while (DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT));
    while (!DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT));
	while (DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT));
}

uint8_t read_data (void)
{
	uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT) == 0);
		__delay_us (40);
		if (DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT) == 0)
		{
			i&= ~(1<<(7-j));
		}
		else i|= (1<<(7-j));
		while (DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT));
	}
	return i;
}






























































/*============================================================================*/
uint8_t DHT11_RequestData(void) {
    uint16_t timeOut = 0xFFFF;

    PIN_CONFIGURE_DIGITAL(PIN_OUTPUT, DHT11_DATA_PORT, DHT11_DATA_MASK);
    PIN_DIGITAL_WRITE(PIN_LOW, DHT11_DATA_PORT, DHT11_DATA_MASK);

    __delay_ms(18);

    PIN_DIGITAL_WRITE(PIN_HIGH, DHT11_DATA_PORT, DHT11_DATA_MASK);
    PIN_CONFIGURE_DIGITAL(PIN_INPUT, DHT11_DATA_PORT, DHT11_DATA_MASK);
    __delay_us(30);
    
    while( !DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT))
    {
        if(!--timeOut )
        {   
            return DHT11_ERROR_TIMEOUT;
        }
        
    }
    
    timeOut = 0xFFFF;
    
    while(DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT))
    {
        if(!--timeOut)
        {   
            return DHT11_ERROR_TIMEOUT;
        }        
    }
    

    return DHT11_OK;
}

/*============================================================================*/
uint8_t DHT11_ReadData(void) {
    uint8_t resquestResult = 0x00;
    uint8_t checkSum = 0x00;


    resquestResult = DHT11_RequestData();


    if (!resquestResult) {
        humidity[0] = DHT11_ReadByte();
        humidity[1] = DHT11_ReadByte();
        
        temperature[0] = DHT11_ReadByte();
        temperature[1] = DHT11_ReadByte();
        
        Display_WriteByte(humidity[0]);
        Display_WriteByte(temperature[0]);
        
        
    } else {
        return resquestResult;
    }
    
    return 0;
}

/*============================================================================*/
uint8_t DHT11_ReadByte(void) {
    uint16_t timeout = 0xFFFF;
    uint8_t i;
    uint8_t byte;

    for (i = 0b10000000; i; i = (i >> 1)) {
        timeout = 0xFFFF;
        while (!DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT)) {
            if (!--timeout) {
                return DHT11_ERROR_TIMEOUT;
            }
        }

        __delay_us(40);

        if (DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT)) {
            byte = byte | i;
            timeout = 0xFFFF;
            while (!DIGITAL_PIN_READ(DHT11_DATA_PORT, DHT11_DATA_BIT)) {
                if (!--timeout)
                    return DHT11_ERROR_TIMEOUT;
            }

        }
    }

    return byte;
}
/*============================================================================*/
uint8_t* DHT11_GetTemp( void )
{
    return temperature;
}
/*============================================================================*/
uint8_t* DHT11_GetHum( void )
{
    return humidity;
}
/*============================================================================*/