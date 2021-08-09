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
static bool log = false;
#define PRIMEIRO_LOG    "prim. log"
#define SEGUNDO_LOG     "seg. log"
#define TEM_ENERGIA     "TEM ENERGIA"
char segundo[sizeof (SEGUNDO_LOG)];
static uint8_t count = 0x00;
char vetorTempLocal[4] = {35, 0, 0xf8, 0x43};
char vetorHumLocal[3] = {90, 5, 0x25};
bool TimeIsElapsed = false;

uint8_t i = 0x00;


char vetorTemp [6] = "TEMP: ";
char vetorHum [7] = "HUM : ";

/*============================================================================*/
void main_application(void* args) {
    static uint8_t voltageStatus = 0x00;

    static uint8_t localDHT11Result = 0x00;

    static char *localTemp = NULL;
    static char *localHum = NULL;

    static char auxTemp[3] = "0.0";
    static char auxHum[3] = "0.0";

    static bool localUserState = false;

    static uint8_t localVoltageStatus = 0x00;

    static uint8_t addr = 0x00;
    uint8_t aux = 0x00;
    uint8_t aux2 = 0x00;
    uint8_t aux3 = 0x00;
    char auxText[] = "USER CONECTADO";
    char auxText2[] = "USER DESCONN";
    
    


    while (1) {

        // Funcionando 
        if (TimeIsElapsed)
        {   
            // localDHT11Result = DHT11_ReadData();
            // if(localDHT11Result != DHT11_ERROR_CHECKSUM && localDHT11Result != DHT11_ERROR_TIMEOUT) //  Leitura Bem Sucedida
            if (1)
            {
                localTemp = &vetorTempLocal;
                localHum = &vetorHumLocal;

                /* Get User Status */
                localUserState = User_GetState();

                if (localUserState) {
                    
                    Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                    __delay_ms(3);
                    Display_WriteString("Conectado", 10, 0);
                    __delay_ms(1000);
                    
                    // Existe um Log para enviar para o usuário
                    if (log)
                    {
                        Bluetooth_HC_06_WriteString("\n***ULTIMO LOG***\n", 18);
                        
                        /*
                        Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                        __delay_ms(3);
                        Display_WriteString("Existe Log", 11, 0);
                        __delay_ms(1000);
                        */
                        
                        for(aux2 = 0x00; aux2 <= 0x08; aux2 += 2)
                        {
                            aux = EEPROM_DataRead(aux2);
                            if(aux != 0xFF)
                            {
                                
                                Bluetooth_HC_06_WriteString("\nAddress: ", 9);
                                Bluetooth_HC_06_WriteByte(0x31);
                                Bluetooth_HC_06_WriteString("\nValor Lido: ", 12);
                                Bluetooth_HC_06_WriteByte(aux);
                            }
                        }
                        
                        log = false;
                        address = ADDR_BASE;
                    }
                    else // Não existe log antigo -> Enviar dados atuais
                    {
                        Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                        __delay_ms(3);
                        Display_WriteString("Nao tem Log", 12, 0);
                        __delay_ms(1000);
                        
                        
                        Bluetooth_HC_06_WriteString("\n***ENVIA LOG ATUAL: ***\n", 25);
                    }
                    
                }
                else // Usuário não conectado, devemos ver a condição da energia
                {
                    Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                    __delay_ms(3);
                    Display_WriteString("Desconectado", 13, 0);
                    __delay_ms(1000);
                    
                    // Verifica o estado do pino de energia
                    localVoltageStatus = Voltage_Read();
                    
                    if(localVoltageStatus)
                    {
                        Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                        __delay_ms(5);
                        Display_WriteString("Tem energia", 12, 0);
                        __delay_ms(500);
                    }
                    else 
                    {
                        Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                        __delay_ms(5);
                        Display_WriteString("Nao tem energia", 16, 0);
                        __delay_ms(500);
                        
                        if(address <= 0x08)
                        {
                            // Escreve a temperatura registrada
                            EEPROM_DataWrite(/*vetorTempLocal[0]*/ (0x41 + i), address);
                            
                            // Escreve a Humidade registrada
                            //EEPROM_DataWrite(/*vetorHumLocal[0]*/"B" , address);
                            
                            aux = EEPROM_DataRead(address);
                            
                            Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                            __delay_ms(5);
                            Display_WriteString("EEPROM:", 8, 0);
                            
                            Display_WriteByte(0x20);
                            Display_WriteByte(aux);
                            
                            Display_WriteByte(0x20);
                            Display_WriteByte(address + 48);
                            __delay_ms(500);
                            
                            address++;
                            i++;
                        }
                        else 
                        {
                            Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                            __delay_ms(5);
                            Display_WriteString("FULL MEM.", 10, 0);
                            __delay_ms(350);
                        }
                        
                        log = true;
                    }
                }
            }
            else // erro no sensor
            {
                 Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
                 __delay_ms(3);
                 Display_WriteString("Erro Sensor", 12, 0);
                 __delay_ms(2000);
            }
            
            TimeIsElapsed = false;
        }
        else // Não, ainda não é hora da leitura
        {
            Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
            __delay_ms(5);
            Display_WriteString("Nao e Hora", 11, 0);
            
            __delay_ms(2000);
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