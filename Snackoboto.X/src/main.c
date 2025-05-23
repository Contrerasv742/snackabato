#include "IO_Ports.h"
#include "AD.h"
#include "Stepper.h"
#include "timers.h"
#include <stdio.h>

// Define DRV8811_DRIVE to use that drive mode in the Stepper module
#define DRV8811_DRIVE


// Define constants for stepper testing
#define STEPPER_STEPS 200
#define MAX_STEP_RATE_TEST 5000  
#define STEP_RATE_INCREMENT 50

// Defines for the Servo Motors
#define SERVO_PIN RC_PORTV04

// Defines for the DC Motors
#define ENABLE_PIN          RC_PORTY07
#define DC_DIRECTION_PIN1   PIN8
#define DC_DIRECTION_PIN2   PIN9
#define DC_PWM_MOTOR_PIN    PWM_PORTZ06

// Defines for the Stepper Motors
#define STEPPER_1_ENABLE_PIN      PORTZ03_LAT
#define STEPPER_1_DIRECTION_PIN   PORTZ04_LAT
#define STEPPER_1_STEP_PIN        PORTZ05_LAT
#define STEPPER_1_PWM_MOTOR_PIN   PWM_PORTZ10

#define STEPPER_2_ENABLE_PIN     PORTZ06_LAT
#define STEPPER_2_DIRECTION_PIN  PORTZ07_LAT
#define STEPPER_2_STEP_PIN       PORTZ08_LAT
#define STEPPER_2_PWM_MOTOR_PIN   PWM_PORTZ12

#define MAIN
#ifdef MAIN
int main(void) {
    /* Initialization Section */
    BOARD_Init();
    AD_Init();
    TIMERS_Init();
    
    /* Pin Configuration */
    AD_AddPins(AD_PORTV5);
    
    static uint32_t stepCounter = 0;
    static uint32_t lastStepTime = 0;
    static uint8_t switch_state = FORWARD;
    static uint32_t currentStepRate = 100;
    
    // Set the stepper start at a low rate
    Stepper_Init();
    Stepper_SetSteps(switch_state, currentStepRate);

    // DC Motor -- Configure direction control pins for the H-bridge
    IO_PortsSetPortOutputs(PORTZ, DC_DIRECTION_PIN1);
    IO_PortsSetPortOutputs(PORTZ, DC_DIRECTION_PIN2);
    
    // Set PWM frequency to 1KHz (default)
    PWM_SetFrequency(PWM_1KHZ);
    
    while (1) {
        // Read potentiometer for speed control
        uint32_t pot_value = AD_ReadADPin(AD_PORTV5);
        
        // Manually control step rate (X steps/sec)
        uint32_t Stepper_Step_Rate  = 600;
        uint32_t DC_Step_Rate       = 600;
        uint32_t Servo_Step_Rate    = 600;

        // Stepper Motor Configuration
        Stepper_SetRate(Stepper_Step_Rate);
        Stepper_SetSteps(FORWARD, Stepper_Step_Rate);

        // DC Motor Configuration
        unsigned int DC_Duty_Cycle = (pot_value * 1000) / 1023;
        printf("DC Motor duty cycle = %d%%\r\n", DC_Duty_Cycle/10);
        PWM_SetDutyCycle(PWM_MOTOR_PIN, DC_Duty_Cycle);
        
        // Servo Motor Configuration
        unsigned int Servo_Duty_Cycle = 1000 + (Servo_Step_Rate * 1000) / 1023;
        RC_SetPulseTime(RC_PORTV04, pulse_time);
        
        // Check if it's time to take a step 
        if (TIMERS_GetTime() - lastStepTime >= (1000 / Stepper_Step_Rate)) {
            lastStepTime = TIMERS_GetTime();
            
            Stepper_SetSteps(switch_state, currentStepRate);
            Stepper_StartSteps();
            
            // Toggle direction every 100 steps
            (stepCounter)++;
            if (stepCounter >= 100) {
                stepCounter = 0;
                printf("Direction changed to: %s\r\n", switch_state ? "FORWARD" : "REVERSE");
            }
        }
    }
    return 0;
}

#endif
