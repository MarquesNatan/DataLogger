/*============================================================================*/
#include "eeprom.h"
#include "../../board/board_definitions/board_definitions.h"
/*============================================================================*/
void EEPROM_DataWrite(unsigned char data, unsigned char addr)
{
    
    uint8_t STATUS_INTCON = INTCONbits.GIE;
    while( EECON1bits.WR);
    
    EEADR  = addr;
    EEDATA = data;
    
    EECON1bits.EEPGD = 0x00;
    EECON1bits.CFGS  = 0x00;
    EECON1bits.WREN  = 1;
    
    INTCONbits.GIE   = 0;
    
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR    = 1;
    
    INTCONbits.GIE = STATUS_INTCON;
}
/*============================================================================*/
unsigned char EEPROM_DataRead( uint8_t addr )
{
    while(EECON1bits.WR);
    
    EEADR = addr;
    EECON1bits.EEPGD = 0x00;
    EECON1bits.CFGS = 0x00;
    
    EECON1bits.RD = 0x01;
    
    return (EEDATA);
}
/*============================================================================*/