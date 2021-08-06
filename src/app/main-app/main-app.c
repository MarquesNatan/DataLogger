/*============================================================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
/*============================================================================*/
#include "../../pic18f4520/timer/timer.h"
#include "../../pic18f4520/gpio/gpio.h"
#include "../../board/pinout/pinout.h"
/*============================================================================*/
#include "../../board/board_definitions/board_definitions.h"
/*============================================================================*/
#include "main-app.h"
#include "../../app/dht11/dht11.h"
#include "../../app/display_lcd/display_lcd.h"
#include "../../app/read_voltage/read_voltage.h"
#include "../../app/bluetooth-hc-06/bluetooth_hc_06.h"
#include "../../board/peripheral-controller/peripheral_controller.h"
/*============================================================================*/
#define FIM_INICIALIZACAO   "END INIT"
uint8_t vetorTempLocal[2] = {35, 0};
uint8_t vetorHumLocal[2]  = {90, 5};
bool TimeIsElapsed = false;
/*============================================================================*/
void main_application( void* args)
{
    static uint8_t voltageStatus = 0x00;
    
    static uint8_t localDHT11Result = 0x00;
    
    static char *localTemp = NULL;
    static char *localHum = NULL;
    
    static bool localUserState = false;
    
    char auxText[] = "USER CONECTADO";
    char auxText2[] = "USER DESCONN";
    
    while(1)
    {

        if(TimeIsElapsed)
        {
            // localDHT11Result = DHT11_ReadData();
            // if(localDHT11Result != DHT11_ERROR_CHECKSUM && localDHT11Result != DHT11_ERROR_TIMEOUT) //  Leitura Bem Sucedida
            if(1) 
            {
                /*
                localTemp = DHT11_GetTemp();
                localHum = DHT11_GetHum();
                */
                
                localTemp = &vetorTempLocal;
                localHum = &vetorHumLocal;
                
                /* Get User Status */
                localUserState = User_GetState();
                if(localUserState)
                {
                    
                    Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                    __delay_ms(5);
                    Display_WriteString(auxText, sizeof(auxText), 0);
                }
                else 
                {
                    Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                    __delay_ms(5);
                    Display_WriteString(auxText2, sizeof(auxText2), 0);
                }
                
                
                
            }else 
            {
                
            }
            
            
            TimeIsElapsed = false;
        }
        else              // Não, ainda não é hora da leitura
        {
            PIN_DIGITAL_WRITE(PIN_HIGH, LED_HEARTBEAT2_PORT, LED_HEARTBEAT2_MASK);
        }
        
    }
    
    
}
/*============================================================================*/
void StartSystem( void* args )
{
    uint8_t dht11_response = 0x00;
    
    // START PERIPHERAL
    Peripheral_Controller(NULL);
    
    
    // START DISPLAY    - TEST DISPLAY
    DisplayLCD_Init();
    
    
    Display_WriteString(START_BLUETOOTH, sizeof(START_BLUETOOTH), 0);
    // START BLUETOOTH  - TEST BLUETOOTH
    Bluetooth_HC_06_Configure();
    __delay_ms(3000);
    
     // Display Clear: 0b00000001 1.52 ms
    Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
   __delay_ms(2); 
    Display_WriteString(FIM_INICIALIZACAO, sizeof(FIM_INICIALIZACAO), 0);
    
    // Testa o módulo dht11, caso não funcione fica travado (aceita comandos)
    if((dht11_response = DHT11_RequestData()) == DHT11_OK)
    {
        Display_WriteString(DHT11_WORKING, sizeof(DHT11_WORKING), 0);
    }else if((dht11_response = DHT11_RequestData()) == DHT11_ERROR_TIMEOUT)
    {
        Display_WriteString(DHT11_TIMEOUT, sizeof(DHT11_TIMEOUT), 0);
        // Não executa mais nada se o dht11 não estiver funcionando
        while(1);
    }
    // Verifica se a memória ram está cheia
    // START RAM        - TEST RAM
}
/*============================================================================*/