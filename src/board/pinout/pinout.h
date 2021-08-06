/*============================================================================*/
#ifndef PINOUT_H
#define PINOUT_H
/*==============================================================================
 *                                  LED 
 ===============================================================================
 */
#define LED_HEARTBEAT1_PORT             D
#define LED_HEARTBEAT1_BIT              0
#define LED_HEARTBEAT1_MASK             (1 << LED_HEARTBEAT1_BIT)

#define LED_HEARTBEAT2_PORT             D 
#define LED_HEARTBEAT2_BIT              1
#define LED_HEARTBEAT2_MASK             (1 << LED_HEARTBEAT2_BIT)
/*==============================================================================
 *                              SENSOR DHT11
 ===============================================================================
 */
#define DHT11_DATA_PORT                 D
#define DHT11_DATA_BIT                  0
#define DHT11_DATA_MASK                 (1 << DHT11_DATA_BIT)

/*==============================================================================
 *                              DISPLAY LCD
 ===============================================================================
 */
#define DISPLAY_LCD_D4_PORT             B
#define DISPLAY_LCD_D4_BIT              4
#define DISPLAY_LCD_D4_MASK             (1 << DISPLAY_LCD_D4_BIT)

#define DISPLAY_LCD_D5_PORT             B
#define DISPLAY_LCD_D5_BIT              5
#define DISPLAY_LCD_D5_MASK             (1 << DISPLAY_LCD_D5_BIT)

#define DISPLAY_LCD_D6_PORT             B
#define DISPLAY_LCD_D6_BIT              6
#define DISPLAY_LCD_D6_MASK             (1 << DISPLAY_LCD_D6_BIT)

#define DISPLAY_LCD_D7_PORT             B
#define DISPLAY_LCD_D7_BIT              7
#define DISPLAY_LCD_D7_MASK             (1 << DISPLAY_LCD_D7_BIT)

#define DISPLAY_LCD_RS_PORT             B
#define DISPLAY_LCD_RS_BIT              3
#define DISPLAY_LCD_RS_MASK             (1 << DISPLAY_LCD_RS_BIT)

#define DISPLAY_LCD_EN_PORT             B
#define DISPLAY_LCD_EN_BIT              2
#define DISPLAY_LCD_EN_MASK             (1 << DISPLAY_LCD_EN_BIT)
/*==============================================================================
 *                          MODULE BLUETOOTH
 ===============================================================================
 */
#define BLUETOOTH_TX_PORT               C
#define BLUETOOTH_TX_BIT                6
#define BLUETOOTH_TX_MASK               ( 1 << BLUETOOTH_TX_BIT)

#define BLUETOOTH_RX_PORT               C
#define BLUETOOTH_RX_BIT                7
#define BLUETOOTH_RX_MASK               ( 1 << BLUETOOTH_RX_BIT ) 

/*==============================================================================
 *                      DISPLAY LCD INTERFACE (74HC595)
 ===============================================================================
 */
#define VOLTAGE_INPUT_PORT              B
#define VOLTAGE_INPUT_BIT               0
#define VOLTAGE_INPUT_MASK              (1 << VOLTAGE_INPUT_BIT)

/*==============================================================================
 *                      DISPLAY LCD INTERFACE (74HC595)
 ===============================================================================
 */
#define DISPLAY_DS_INTERFACE_PORT       D 
#define DISPLAY_DS_INTERFACE_BIT        1
#define DISPLAY_DS_INTERFACE_MASK       ( 1 << DISPLAY_DS_INTERFACE_BIT)

#define DISPLAY_OE_INTERFACE_PORT       D
#define DISPLAY_OE_INTERFACE_BIT        2
#define DISPLAY_OE_INTERFACE_MASK       (1 << DISPLAY_OE_INTERFACE_BIT)

#define DISPLAY_CLK_INTERFACE_PORT      D
#define DISPLAY_CLK_INTERFACE_BIT       3
#define DISPLAY_CLK_INTERFACE_MASK      (1 << DISPLAY_CLK_INTERFACE_BIT)

#define DISPLAY_LATCH_INTERFACE_PORT    D
#define DISPLAY_LATCH_INTERFACE_BIT     4
#define DISPLAY_LATCH_INTERFACE_MASK    (1 << DISPLAY_LATCH_INTERFACE_BIT)

#endif /* PINOUT_H */
/*============================================================================*/