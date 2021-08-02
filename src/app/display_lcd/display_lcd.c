/*============================================================================*/
#include "display_lcd.h"
#include "../../board/board_definitions/board_definitions.h"
#include "../../pic18f4520/gpio/gpio.h"
#include "../../board/pinout/pinout.h"
#include <stdint.h>

#define STRING_TEST         "TESTE ABC"
/*============================================================================*/
void DisplayLCD_Init( void )
{
    __delay_ms(500);
    PORT_DIGITAL_CONFIGURE(DISPLAY_LCD_D4_PORT, 0x00);
    
    // Function: Function Set ( send 2, 2 and 3 to display)
    sendNibble(0x20);
    sendNibble(0x20);
    sendNibble(0x30);
    
    // Functios: Entry Set Mode 
    // RS   RW  D7  D6  D5  D4  D3  D2  D1  D0      0b00000110
    // 0    0   0   0   0   0   0   1   I/D S       -> I/D = 1 Increment / 0 = Decrement
    //                                              -> S = 1 Display Shift / 0 Display don't shift
    
    Display_SendByte((DISPLAY_ENTRY_SET_MODE | DISPLAY_INCREMENT | DISPLAY_SHIFT_DIS), DISPLAY_COMMAND);
    
    // Functios: Display On Off Control 
    // RS   RW  D7  D6  D5  D4  D3  D2  D1  D0      0b00000110
    // 0    0   0   0   0   0   1   D   C   S       D -> Display On Off (0 off)
    //                                              C -> Cursor ON OFF (1 ON)
    //                                              S -> Cursor Blink
    
    Display_SendByte((DISPLAY_ON_OFF | DISPLAY_ON | DISPLAY_CURSOR_ON | DISPLAY_CURSOR_BLK_EN ), DISPLAY_COMMAND);
    
    Display_SendByte(0b00000001, DISPLAY_COMMAND);
    
   __delay_ms(2);
   
   Display_WriteString(STRING_TEST, sizeof(STRING_TEST));
    
}
/*============================================================================*/
void sendNibble(uint8_t nibble)
{
    uint8_t auxNibble = 0x00;
    
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_RS_PORT, DISPLAY_LCD_RS_MASK);
    
    DIGITAL_PORT_WRITE(DISPLAY_LCD_D4_PORT, ((DIGITAL_PORT_READ(DISPLAY_LCD_D4_PORT) & 0x0F) | nibble));
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    
    __delay_ms(1);
}
/*============================================================================*/
void Display_SendByte(uint8_t byte, uint8_t comm)
{
    uint8_t auxByte = 0x00;
    
    PIN_DIGITAL_WRITE(comm, DISPLAY_LCD_RS_PORT, DISPLAY_LCD_RS_MASK);
    
    auxByte = (byte & 0xF0);
    
    DIGITAL_PORT_WRITE(DISPLAY_LCD_D4_PORT, ((DIGITAL_PORT_READ(DISPLAY_LCD_D4_PORT) & 0x0F) | auxByte));
    
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    
    auxByte = (byte << 0x04);
    
    DIGITAL_PORT_WRITE(DISPLAY_LCD_D4_PORT, auxByte);
    
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    
    __delay_ms(1);
}
/*============================================================================*/
void Display_WriteByte(uint8_t byte)
{
    uint8_t auxByte = 0x00;
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_RS_PORT, DISPLAY_LCD_RS_MASK);
    
    auxByte = (byte & 0xF0);
    DIGITAL_PORT_WRITE(DISPLAY_LCD_D4_PORT, ((DIGITAL_PORT_READ(DISPLAY_LCD_D4_PORT) & 0x0F) | auxByte));
    
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
   
    
    auxByte = (byte << 0x04);
    DIGITAL_PORT_WRITE(DISPLAY_LCD_D4_PORT, ((DIGITAL_PORT_READ(DISPLAY_LCD_D4_PORT) & 0x0F) | auxByte));
    
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_LOW, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    
    __delay_ms(2);
}
/*============================================================================*/
void Display_WriteString(char* string, uint8_t length)
{
    uint8_t auxLength = 0x00; 
    for(auxLength = 0; auxLength < length - 1; auxLength++)
    {
        Display_WriteByte((uint8_t)string[auxLength]);
    }
}
/*============================================================================*/