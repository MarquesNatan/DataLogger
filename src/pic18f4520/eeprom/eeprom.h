/*============================================================================*/
#ifndef EEPROM_H
#define	EEPROM_H
/*============================================================================*/
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
/*============================================================================*/
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*============================================================================*/
    void EEPROM_DataWrite(unsigned char data, unsigned char addr);
    unsigned char  EEPROM_DataRead( uint8_t addr );
/*============================================================================*/
#ifdef	__cplusplus
}
#endif /* __cplusplus */
#endif	/* EEPROM_H */
/*============================================================================*/
