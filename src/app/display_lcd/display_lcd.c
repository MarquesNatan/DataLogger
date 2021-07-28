/*============================================================================*/
#include "display_lcd.h"
#include "../../board/pinout/pinout.h"
#include "../../pic18f4520/gpio/gpio.h"
/*============================================================================*/
#define _XTAL_FREQ      10000000
/*============================================================================*/
void displayLcd_CMD(uint8_t cmd)
{
    uint8_t auxCmd; 
    auxCmd = (cmd >> 4);
    PORTB = auxCmd;
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_RS_PORT, DISPLAY_LCD_RS_MASK);
    
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    
    auxCmd = (cmd & 0x0F);
    PORTB = auxCmd;
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_RS_PORT, DISPLAY_LCD_RS_MASK);
    
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
}
/*============================================================================*/
void displayLCD_Nibble(uint8_t nibble)
{
    PORTB = nibble;
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_RS_PORT, DISPLAY_LCD_RS_MASK);
    
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
}
/*============================================================================*/
void DisplayLCD_Init( void )
{
    TRISB = 0x00;
    TRISD = 0x00;
    PORTB = 0x00;
    PORTD = 0x00;
    __delay_ms(40);
   
    
    
    displayLCD_Nibble(0x02);
    __delay_ms(1);
    displayLCD_Nibble(0x02);
    __delay_ms(1);
    displayLCD_Nibble(0x02);
    __delay_ms(1);
    displayLCD_Nibble(0x00);
    __delay_ms(1);
    displayLCD_Nibble(0x0E);
    __delay_ms(1);
    
    PORTB = 0x04;
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_RS_PORT, DISPLAY_LCD_RS_MASK);
    
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    
    PORTB = 0x08;
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_RS_PORT, DISPLAY_LCD_RS_MASK);
    
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    __delay_us(100);
    PIN_DIGITAL_WRITE(PIN_HIGH, DISPLAY_LCD_EN_PORT, DISPLAY_LCD_EN_MASK);
    
    
    
}
/*==============================================================================
 * 
 *                  Wait 15 ms
 *                      |
 *              |---------------|
 *              |    00 0010    |   Function set (interface 4 bits long)
 *              |---------------|
 *                      |
 *                  Wait 4.1 ms
 *                      |
 *              |---------------|
 *              |    00 0010    |   Function set (interface 4 bits long))
 *              |---------------|
 *                      |
 *                  Wait 100 us
 *                      |
 *              |---------------|
 *              |    00 0010    |   Function set (interface 4 bits long))
 *              |---------------|
 *                      |
 *              |---------------|
 *              |    00 0010    |   Function set (interface 4 bits long))
 *              |---------------|
 *              |    00 0010    |   Function set (interface 4 bits long)
 *              |    00 NF**    |   N -> Number lines, F -> Set Fonts
 *              |---------------|
 *              |    00 0000    |   Display ON OFF Control
 *              |    00 1DCB    |   D - ON/OFF C - CURSOR ON/OFF B - BLINK CURSOR
 *              |---------------|                      
 *              |    00 0000    |   Display Clear
 *              |    00 0001    |   
 *              |---------------|                      
 *              |    00 0000    |   ENTRY SET MODE
 *              |    00 01 ID S |   I/D -> Increment/Decrement
 *              |---------------|   S - > Shift Display
 *                      | 
 *              Initialization ends
 * 
 * ============================================================================*/