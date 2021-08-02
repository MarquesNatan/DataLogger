/*============================================================================*/
#ifndef DISPLAY_LCD_H
#define	DISPLAY_LCD_H
/*============================================================================*/
#include <xc.h> 
#include <stdint.h>
/*============================================================================*/
#define DISPLAY_COMMAND             0
#define DISPLAY_WRITE               1   
/*============================================================================*/
#define DISPLAY_ENTRY_SET_MODE      0b00000100
                
#define DISPLAY_INCREMENT           0b00000010
#define DISPLAY_DECREMENT           0b00000000

#define DISPLAY_SHIFT_EN            0b00000001
#define DISPLAY_SHIFT_DIS           0b00000000
/*============================================================================*/
#define DISPLAY_ON_OFF              0b00001000

#define DISPLAY_ON                  0b00000100
#define DISPLAY_OFF                 0b00000000

#define DISPLAY_CURSOR_ON           0b00000010
#define DISPLAY_CURSOR_OFF          0b00000000

#define DISPLAY_CURSOR_BLK_EN       0b00000001
#define DISPLAY_CURSOR_BLK_DIS      0b00000000
/*============================================================================*/
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*============================================================================*/
    void DisplayLCD_Init( void );
    void Display_SendByte(uint8_t byte, uint8_t comm);
    void Display_WriteByte(uint8_t byte);
    void Display_WriteString(char* string, uint8_t length);
    void sendNibble(uint8_t nibble);
/*============================================================================*/
#ifdef	__cplusplus
}
#endif /* __cplusplus */
#endif	/* DISPLAY_LCD_H */
/*============================================================================*/
