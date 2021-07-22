/*============================================================================*/
#ifndef DISPLAY_LCD_H
#define	DISPLAY_LCD_H
/*============================================================================*/
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>
/*============================================================================*/
#define DISPLAY_PORT                B
// Funções para concatenação  de comandos PORT e TRIS
#define DISPLAY_PASTE2B(a, b)       a##b

#define DISPLAY_LCD_TRIS(a)         DISPLAY_PASTE2B(TRIS, a)        
#define DISPLAY_LCD_PORT(a)         DISPLAY_PASTE2B(PORT, a)
/*============================================================================*/
#define DISPLAY_CLR                     0b00000001
#define DISPLAY_HOME                0b00000010
/*============================================================================*/
// --- DISPLAY ENTRY SET MODE ---
#define DISPLAY_ENTRY_SET_MODE          0b00000100 
 
// Cursor Direction
#define DISPLAY_CURSOR_INCREMENT        0b00000010
#define DISPLAY_CURSOR_DECREMENT        0b00000000

// Display shift
#define DISPLAY_EN_SHIFT                0b00000001
#define DISPLAY_NO_SHIFT                0b00000000
/*============================================================================*/
// ---- DISPLAY ON OFF CONTROL ---- 
#define DISPLAY_ON_CONTROL              0b00001000

// Display ON/OFF
#define DISPLAY_ON                      0b00000100
#define DISPLAY_OFF                     0b00000000

// Cursor ON OFF
#define DISPLAY_CURSOR_ON               0b00000010
#define DISPLAY_CURSOR_OFF              0b00000000

// Blink Cursor
#define DISPLAY_CURSOR_BLK_ON           0b00000001
#define DISPLAY_CURSOR_BLK_OFF          0b00000000
/*============================================================================*/
// --- CURSOR DISPLAY SHIFT ---
#define CURSOR_DISPLAY_SHIFT            0b00010000

// possible configurations
#define CURSOR_LEFT_AC_DECR             0b00000000
#define CURSOR_RIGHT_AC_INCR            0b00000100

#define DISPLAY_SHIFT_LEFT              0b00001000
#define DISPLAY_SHIFT_RIGHT             0b00001100
/*============================================================================*/
#define DISPLAY_FUNCTION_SET            0b00100000

// Display data length
#define DISPLAY_BUS_8_BITS              0b00010000
#define DISPLAY_BUS_4_BITS              0b00000000

// Display lines
#define DISPLAY_2_ROW                    0b00001000
#define DISPLAY_1_ROW                    0b00000000

// Tamanho do fonte
#define DISPLAY_FONT_5x11               0b00000100
#define DISPLAY_FONT_5x8                0b00000000
/*============================================================================*/
#define SET_CGRAM_ADDRESS        0b01000000
#define SET_DRAM_ADDRESS         0b10000000

#define END_INICIAL_LINHA_1      0x00
#define END_INICIAL_LINHA_2      0x40
/*============================================================================*/
#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
/*============================================================================*/
    void DisplayLCD_Init( void );
/*============================================================================*/
#ifdef	__cplusplus
}
#endif /* __cplusplus */
#endif	/* DISPLAY_LCD_H */
/*============================================================================*/
