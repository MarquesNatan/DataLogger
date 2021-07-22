/*============================================================================*/
#include "display_lcd.h"
/*============================================================================*/
void displayLcd_CMD(uint8_t cmd)
{
    uint8_t auxCmd; 
    auxCmd = cmd >> 4;
}
/*============================================================================*/
void DisplayLCD_Init( void )
{
    
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