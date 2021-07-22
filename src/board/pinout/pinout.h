/*============================================================================*/
#ifndef PINOUT_H
#define PINOUT_H
/*==============================================================================
 *                                  LED 
 ===============================================================================
 */
#define LED_HEARTBEAT1_PORT             B 
#define LED_HEARTBEAT1_BIT              0
#define LED_HEARTBEAT1_MASK             (1 << LED_HEARTBEAT1_BIT)

#define LED_HEARTBEAT2_PORT             B 
#define LED_HEARTBEAT2_BIT              1
#define LED_HEARTBEAT2_MASK             (1 << LED_HEARTBEAT2_BIT)
/*==============================================================================
 *                              DISPLAY LCD
 ===============================================================================
 */
#define DISPLAY_LCD_D0_PORT             B
#define DISPLAY_LCD_D0_BIT              0
#define DISPLAY_LCD_D0_MASK             (1 << DISPLAY_LCD_D0_BIT)

#define DISPLAY_LCD_D1_PORT             B
#define DISPLAY_LCD_D1_BIT              1
#define DISPLAY_LCD_D1_MASK             (1 << DISPLAY_LCD_D1_BIT)

#define DISPLAY_LCD_D2_PORT             B
#define DISPLAY_LCD_D2_BIT              2
#define DISPLAY_LCD_D2_MASK             (1 << DISPLAY_LCD_D2_BIT)

#define DISPLAY_LCD_D3_PORT             B
#define DISPLAY_LCD_D3_BIT              3
#define DISPLAY_LCD_D3_MASK             (1 << DISPLAY_LCD_D3_BIT)

#define DISPLAY_LCD_D4_PORT             B
#define DISPLAY_LCD_D4_BIT              0
#define DISPLAY_LCD_D4_MASK             (1 << DISPLAY_LCD_D4_BIT)

#define DISPLAY_LCD_D5_PORT             B
#define DISPLAY_LCD_D5_BIT              1
#define DISPLAY_LCD_D5_MASK             (1 << DISPLAY_LCD_D5_BIT)

#define DISPLAY_LCD_D6_PORT             B
#define DISPLAY_LCD_D6_BIT              2
#define DISPLAY_LCD_D6_MASK             (1 << DISPLAY_LCD_D6_BIT)

#define DISPLAY_LCD_D7_PORT             B
#define DISPLAY_LCD_D7_BIT              3
#define DISPLAY_LCD_D7_MASK             (1 << DISPLAY_LCD_D7_BIT)

#define DISPLAY_LCD_RS_PORT             D
#define DISPLAY_LCD_RS_BIT              1
#define DISPLAY_LCD_RS_MASK             (1 << DISPLAY_LCD_RS_BIT)


#define DISPLAY_LCD_EN_PORT             D
#define DISPLAY_LCD_EN_BIT              0
#define DISPLAY_LCD_EN_MASK             (1 << DISPLAY_LCD_EN_BIT)
/*==============================================================================
 *                                  UART
 ===============================================================================
 */
#endif /* PINOUT_H */
/*============================================================================*/