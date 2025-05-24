#include "BOARD.h"
#include "RC_Servo.h"
#include "IO_Ports.h"
#include "AD.h"
#include "LED.h"
#include "pwm.h"
#include <stdio.h>
//#include "ES_Configure.h"
//#include "ES_Framework.h"

// Define for all LEDs in a bank
#define ALL_LEDS_ON      0x0F  

// Define pins for L298 H-Bridge control
#define PWM_MOTOR_PIN   PWM_PORTZ06
#define ENABLE_PIN      RC_PORTY07
#define DIRECTION_PIN1  0x0100 
#define DIRECTION_PIN2  0x0200 

#define PART4
#ifdef PART4
int main(void) {
//    ES_Return_t ErrorType;
    
    /* Initialization Section */
    BOARD_Init();
    AD_Init();
    LED_Init();
    PWM_Init();  
    
    /* Pin Configuration */
    // 1) UNO Pot Input
    AD_AddPins(AD_PORTV5);                  
    // 2) PWM (square wave) output for DC motor
    PWM_AddPins(PWM_MOTOR_PIN);               
    // 3) Pins for the LEDs
    LED_AddBanks(LED_BANK1|LED_BANK2|LED_BANK3);
    
    // Configure direction control pins for the H-bridge
    IO_PortsSetPortOutputs(PORTZ, DIRECTION_PIN1);
    IO_PortsSetPortOutputs(PORTZ, DIRECTION_PIN2);
    
    // Set PWM frequency to 1KHz (default)
    PWM_SetFrequency(PWM_1KHZ);
    
    while (1) {
        // Read potentiometer and switch
        unsigned int pot_value = AD_ReadADPin(AD_PORTV5);
        unsigned int switch_state = 1;
        
        // Map potentiometer value to PWM duty cycle (0-1000)
        unsigned int duty_cycle = (pot_value * 1000) / 1023;
        printf("DC Motor duty cycle = %d%%\r\n", duty_cycle/10);
        PWM_SetDutyCycle(PWM_MOTOR_PIN, duty_cycle);
        
        // Set direction based on switch state
        IO_PortsWritePort(PORTZ, DIRECTION_PIN1);
        IO_PortsClearPortBits(PORTZ, DIRECTION_PIN2);
        
    }
    return 0;
}
#endif 
