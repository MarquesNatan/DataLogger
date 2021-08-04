/*============================================================================*/
#include <xc.h>
#include <stdio.h>
#include "pic18f4520/fuse/fuse.h"
/*============================================================================*/
#include "pic18f4520/timer/timer.h"
#include "pic18f4520/interrupt/interrupt.h"
#include "app/display_lcd/display_lcd.h"
/*============================================================================*/
#include "pic18f4520/serial/serial.h"
#include "app/dht11/dht11.h"
/*============================================================================*/
#include "pic18f4520/gpio/gpio.h"
#include "board/pinout/pinout.h"
/*============================================================================*/
#include "app/bluetooth-hc-06/bluetooth_hc_06.h"
#include "app/main-app/main-app.h"
/*============================================================================*/
timer_config_t timerConfig = {
    .timer_length = TIMER_LENGTH_16,
    .timer_clk_src = TIMER_CLKO_SRC,
    .timer_transition = TIMER_TRANSITION_LOW_HIGH,
    .timer_prescaler_assign = TIMER_PRESCALER_IS_ASSIGNED,
    .timer_prescaler_value = TIMER_PRESCALER_2
};
/*============================================================================*/
serial_config_t serialConfig = {
    .serial_sync_com = SERIAL_ASSYNC_MODE,
    .serial_data_length = SERIAL_DATA_LENGTH_8,
    .serial_op_mode = SERIAL_MASTER_MODE,
    .serial_desired_baud = SPEED_SERIAL
};
/*============================================================================*/
extern global_timer_t global_timer_value;
extern uint8_t temperature[2];
extern uint8_t humidity[2];
uint8_t count = 0x00;

#define BLUETOOTH_SERIAL    "AT\r"
/*============================================================================*/
void tickHook_func(global_timer_t *timer_value) {
    (*timer_value)++;
}
/*============================================================================*/
void __interrupt() TC0INT(void) {
    if (INTCONbits.TMR0IF == 0x01) {
        tickHook_Execute(&global_timer_value);
        TMR0 = 0xFB1E; // TMR0 = 0x9E58; 
        INTCONbits.T0IF = 0x00; // Clean Timer Flag 
    }

    if (PIR1bits.RCIF) {
        count = RCREG;
        Serial_Transmit(count);

        PIR1bits.RCIF = 0x00;   
    }
}

/*============================================================================*/
void main(void) {
    
  //   Interrupt_GlobalEnable();
    // Timer0_Config(&timerConfig);
    // Timer0_SetTickHook(tickHook_func);
    Serial_1_Config(&serialConfig);
    
    StartSystem(NULL);
    
    int i = 0;
    while (1) 
    {
        Serial_TransmitBuffer(BLUETOOTH_SERIAL, sizeof(BLUETOOTH_SERIAL));
        
        __delay_ms(1000);
        __delay_ms(1000);
    }
    return;
}
/*============================================================================*/