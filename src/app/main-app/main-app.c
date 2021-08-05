/*============================================================================*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "main-app.h"
#include "../../board/board_definitions/board_definitions.h"
#include "../../pic18f4520/timer/timer.h"
/*============================================================================*/
#include "../../board/peripheral-controller/peripheral_controller.h"
#include "../../app/display_lcd/display_lcd.h"
#include "../../app/bluetooth-hc-06/bluetooth_hc_06.h"
#include "../../app/dht11/dht11.h"
#include "../../app/read_voltage/read_voltage.h"
/*============================================================================*/
#define FIM_INICIALIZACAO   "ACABOU ESSA POHA"
bool TimeIsElapsed = false;
/*============================================================================*/
void main_application( void* args)
{
    uint8_t voltageStatus = 0x00;
    uint8_t localDHT11Result = 0x00;
    uint8_t *localTemp = NULL;
    uint8_t *localHum = NULL;
    
    while(1)
    {
        // Hora da leitura?
        if(TimeIsElapsed) // Sim, já é hora da leitura
        {
            // Faz a leitura de temperatura e umidade
            localDHT11Result = DHT11_ReadData();
            if(localDHT11Result != DHT11_ERROR_CHECKSUM && localDHT11Result != DHT11_ERROR_TIMEOUT) //  Leitura Bem Sucedida
            {
                localTemp = DHT11_GetTemp();
                localHum = DHT11_GetHum();
                
                // Usuário conectado, verifica se tem usuário conectado
                
                
            }else                   // Erro de Leitura
            {
                
            }
            
            
        }
        else              // Não, ainda não é hora da leitura
        {
            
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