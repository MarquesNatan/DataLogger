/*============================================================================*/
#include <xc.h>
#include <stdio.h>
#include <stdbool.h>
/*============================================================================*/
#include "pic18f4520/fuse/fuse.h"
/*============================================================================*/
#include "pic18f4520/gpio/gpio.h"
#include "board/pinout/pinout.h"
/*============================================================================*/
#include "pic18f4520/timer/timer.h"
#include "pic18f4520/interrupt/interrupt.h"
#include "pic18f4520/serial/serial.h"
/*============================================================================*/
#include "board/board_definitions/board_definitions.h"
/*============================================================================*/
#include "app/main-app/main-app.h"
#include "app/bluetooth-hc-06/bluetooth_hc_06.h"
#include "app/display_lcd/display_lcd.h"
#include "app/dht11/dht11.h"
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
/*============================================================================*/
uint8_t count = 0x00;
volatile uint8_t vector[3] = {0, 0, 0};
static uint8_t i = 0x00;

/*============================================================================*/
static global_timer_t t = 0;
extern bool TimeIsElapsed;
/*============================================================================*/
void tickHook_func(global_timer_t *timer_value) {
    (*timer_value)++;
    if((*timer_value - t) >= TIME_TO_SEND_MS)
    {
        DIGITAL_PIN_TOGGLE(LED_HEARTBEAT1_PORT, LED_HEARTBEAT1_MASK);
        t = (*timer_value);
        TimeIsElapsed = true;
    }
}
/*============================================================================*/
void __interrupt() TC0INT(void) {
    
    // Interrupção Timer 0
    if (INTCONbits.TMR0IF == 0x01) {
        
        tickHook_Execute(&global_timer_value);
        
        TMR0 = 0xFB1E; // TMR0 = 0x9E58; 
        INTCONbits.T0IF = 0x00; // Clean Timer Flag 
    }

    // Interrupção recepção serial
    if (PIR1bits.RCIF) {
        count = RCREG;
        vector[i] = count;
        
        if(count != 0x3E)
        {
            vector[i] = count;
            i++;
        }else 
        {
            vector[i] = count;
            Display_SendByte(DISPLAY_CLEAR, DISPLAY_COMMAND);
            __delay_ms(5);
            Display_WriteString(vector, sizeof(vector) + 1, 0);
            
            if(vector[1] == 0x43)
            {
                User_SetState(true);
            }else if(vector[1] == 0x44)
            {
                User_SetState(false);
            }
            
            i = 0;
        }
        PIR1bits.RCIF = 0x00;
    }
}

/*============================================================================*/
void main(void) {
    
    
    Interrupt_GlobalEnable();
    Timer0_Config(&timerConfig);
    Timer0_SetTickHook(tickHook_func);
    
    Serial_1_Config(&serialConfig);
    
    // StartSystem(NULL);
    __delay_ms(300);
    DisplayLCD_Init();
    
    PIN_CONFIGURE_DIGITAL(PIN_OUTPUT, LED_HEARTBEAT1_PORT, LED_HEARTBEAT1_MASK);
    PIN_CONFIGURE_DIGITAL(PIN_OUTPUT, LED_HEARTBEAT2_PORT, LED_HEARTBEAT2_MASK);
    
    
    while (1) 
    {
        main_application(NULL);
    }
    return;
}
/*============================================================================*/