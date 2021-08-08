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
#include "../../pic18f4520/eeprom/eeprom.h"
/*============================================================================*/
static bool currLog = false;
#define PRIMEIRO_LOG    "prim. log"
#define SEGUNDO_LOG     "seg. log"
#define TEM_ENERGIA     "TEM ENERGIA"
char segundo[sizeof(SEGUNDO_LOG)];
static uint8_t count = 0x00;
char vetorTempLocal[4] = {35, 0, 0xf8, 0x43};
char vetorHumLocal[3]  = {90, 5, 0x25};
bool TimeIsElapsed = false;



char vetorTemp [6] = "TEMP: ";
char vetorHum [7] = "HUM : ";
/*============================================================================*/
void main_application( void* args)
{
    static uint8_t voltageStatus = 0x00;
    
    static uint8_t localDHT11Result = 0x00;
    
    static char *localTemp = NULL;
    static char *localHum = NULL;
    
    static char auxTemp[3] = "0.0";
    static char auxHum[3]  = "0.0";
    
    static bool localUserState = false;
    
    static uint8_t localVoltageStatus = 0x00;
    
    static uint8_t addr = 0x00;
    
    char auxText[] = "USER CONECTADO";
    char auxText2[] = "USER DESCONN";
    
    uint8_t aux; 
    
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
                    // Usuário conectado, envia o valor de Temperatura e Humidade
                    Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                    __delay_ms(5);
                    Display_WriteString(auxText, sizeof(auxText), 0);
                    
                    // Existe um Log para enviar para o usuário
                    if(currLog)
                    {
                        Bluetooth_HC_06_WriteString("***ULTIMO LOG***\n", 17);
                        for(addr = 0; addr <= 0x04 /* ADDR_END_MEMORY */; addr++)
                        {
                            aux = addr;
                            aux++;
                            
                            auxTemp[0] = EEPROM_DataRead(addr);
                            auxHum[0] =  EEPROM_DataRead(aux);
                            
                            Bluetooth_HC_06_WriteString(vetorTemp, sizeof(vetorTemp));
                            Bluetooth_HC_06_WriteByte((localTemp[0] / 10) + 0x30);
                            Bluetooth_HC_06_WriteByte((localTemp[0] % 10) + 0x30);
                            Bluetooth_HC_06_WriteString("  ", 2);
                            
                            Bluetooth_HC_06_WriteString(vetorHum, sizeof(vetorHum));
                            // Bluetooth_HC_06_WriteString(vetorHum, 1);
                            Bluetooth_HC_06_WriteByte((localHum[0] / 10) + 0x30);
                            Bluetooth_HC_06_WriteByte((localHum[0] % 10) + 0x30);
                            
                            
                            Bluetooth_HC_06_WriteString("\n", 1);
                        }
                        Bluetooth_HC_06_WriteString("*** FIM LOG ***\n", 16);
                        currLog = false;
                    }
                    else // Não existe log antigo -> Enviar dados atuais
                    {
                        Bluetooth_HC_06_WriteString("*** LEITURA ATUAL ***\n", 22);
                        
                        Bluetooth_HC_06_WriteString(vetorTemp, sizeof (vetorTemp));
                        Bluetooth_HC_06_WriteByte((localTemp[0] / 10) + 0x30);
                        Bluetooth_HC_06_WriteByte((localTemp[0] % 10) + 0x30);
                        Bluetooth_HC_06_WriteString("  ", 2);

                        Bluetooth_HC_06_WriteString(vetorHum, sizeof (vetorHum));
                        // Bluetooth_HC_06_WriteString(vetorHum, 1);
                        Bluetooth_HC_06_WriteByte((localHum[0] / 10));
                        Bluetooth_HC_06_WriteByte((localHum[0] % 10));
                        Bluetooth_HC_06_WriteString("\n", 1);
                        }
                }
                else    // Usuário não conectado, devemos ver a condição da energia
                {
                    // Verifica se existe tensão no pino
                    localVoltageStatus = Voltage_Read();
                    if(localVoltageStatus)
                    {
                        Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                        __delay_ms(5);
                        Display_WriteString(TEM_ENERGIA, sizeof(TEM_ENERGIA), 0);
                    }
                    else // Falha na tensão
                    {
                        auxTemp[0] = *localTemp;
                        auxTemp[2] = *(++localTemp);
                        
                        auxHum[0]  = *localHum;
                        auxHum[2]  = *(++localHum);
                        
                        Display_Update(auxTemp, auxHum);
                        
                        // Novo Log?
                        if(!currLog)
                        {
                            if (EEPROM_DataRead(0) == DEFAULT_MEMORY_DATA) {
                                // Apaga log antigo
                                EEPROM_Erase();
                                // Inicia o novo log
                                EEPROM_DataWrite("A", 0);
                                currLog = true;
                            }
                            Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                            __delay_ms(5);
                            Display_WriteString("SEM LOG", 8, 0);    
                        }
                        else // Log Já iniciado
                        {
                            // Log já iniciado
                            if(address <= 0x04)
                            {
                                // Escreve a temperatura registrada
                                EEPROM_DataWrite(auxTemp[0], address);

                                // Escreve a Humidade registrada
                                EEPROM_DataWrite(auxHum[0], address);   
                                
                                Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                                __delay_ms(5);
                                Display_WriteString("JA LOG", 7, 0);
                                
                            }
                            else 
                            {
                                // LIGA UM ALERTA DE MEMÓRIA CHEIA
                                // OK
                                Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                                __delay_ms(5);
                                Display_WriteString("MEM. FULL", 7, 0);
                            }
                            
                        }
                    }
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
void Display_Update(char* temp, char* hum) {
    Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
    __delay_ms(5);

    Display_WriteString(vetorTemp, sizeof (vetorTemp), 0); // Temp: 

    Display_WriteByte((temp[0] / 10) + 0x30);
    Display_WriteByte((temp[0] % 10) + 0x30); // TEMP: XX

    Display_WriteByte(0xDF); //  TEMP: XX.X°
    Display_WriteByte(0x43); //  TEMP: XX.X°C

    // Escreve segunda linha 1° coluna
    Display_SendByte((DISPLAY_DDRAM_ADD | DISPLAY_DDRAM_ADD_2_1), DISPLAY_COMMAND);
    __delay_us(500);


    Display_WriteString(vetorHum, sizeof (vetorHum), 0); // HUM: 

    Display_WriteByte((hum[0] / 10) + 0x30);
    Display_WriteByte((hum[0] % 10) + 0x30); // HUM: XX
    
    Display_WriteByte(0x25); // HUM: XX.X%
    
}
/*============================================================================*/