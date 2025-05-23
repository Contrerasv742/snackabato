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

// Defines for the Stepper Driver
#define ENABLE_PIN      PORTZ09_LAT
#define DIRECTION_PIN   PORTZ05_LAT
#define STEP_PIN        PORTZ07_LAT

#define ENABLE_TRIS     PORTZ09_TRIS
#define DIRECTION_TRIS  PORTZ05_TRIS
#define STEP_TRIS       PORTZ07_TRIS

#define PART6
#ifdef PART6
// Part 6 - Stepper Motor Control using DRV8811 Driver
int main(void) {
    /* Initialization Section */
    BOARD_Init();
    AD_Init();
    TIMERS_Init();  // Initialize the timers module
    
    /* Pin Configuration */
    AD_AddPins(AD_PORTV5);
    
    static uint32_t stepCounter = 0;
    static uint32_t lastStepTime = 0;
    static uint8_t switch_state = FORWARD;
    static uint32_t currentStepRate = 100;
    
    // Start at a low rate
    Stepper_Init();
    Stepper_SetSteps(switch_state, currentStepRate);
    
    while (1) {
        // Read potentiometer for speed control
        uint32_t pot_value = AD_ReadADPin(AD_PORTV5);
        
        // Use potentiometer to control step rate (50-1000 steps/sec)
        // uint32_t manual_rate = 50 + ((pot_value * 950) / 1023);  
        uint32_t manual_rate = 700;
        Stepper_SetRate(manual_rate);
        Stepper_SetSteps(FORWARD, manual_rate);
        
        // Check if it's time to take a step (using non-blocking delay)
        if (TIMERS_GetTime() - lastStepTime >= (1000 / manual_rate)) {
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
