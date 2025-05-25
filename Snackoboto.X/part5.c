#include <xc.h>
#include "BOARD.h"
#include "IO_Ports.h"
#include "AD.h"
#include "LED.h"
#include "Stepper.h"
#include "timers.h"
#include <stdio.h>

// Define constants
#define SWITCH_PIN       PORTY09_BIT  // Direction switch input
#define ALL_LEDS_ON      0x0F         // All LEDs in a bank
#define STEPPER_STEPS    200          // Steps per revolution

// Define drive mode constants - these should match those in stepper_extension.c
#define FULL_STEP_MODE   0
#define HALF_STEP_MODE   1
#define WAVE_DRIVE_MODE  2
#define DRV8811_MODE     3

// Drive Modes

#define FULL_STEP_DRIVE
// #define HALF_STEP_DRIVE
// #define WAVE_DRIVE
// #define DRV8811_DRIVE

// Select which drive mode to use based on your hardware configuration
#ifdef FULL_STEP_DRIVE
#define DRIVE_MODE       FULL_STEP_MODE
#elif defined HALF_STEP_DRIVE
#define DRIVE_MODE       HALF_STEP_MODE
#elif defined WAVE_DRIVE
#define DRIVE_MODE       WAVE_DRIVE_MODE
#elif defined DRV8811_DRIVE
#define DRIVE_MODE       DRV8811_MODE
#else
#define DRIVE_MODE       FULL_STEP_MODE  // Default to full step mode
#endif

#define PART5
#ifdef PART5
int main(void) {
    /* Initialization Section */
    BOARD_Init();
    AD_Init();
    TIMERS_Init();
    Stepper_Init();
    Stepper_SetDriveMode(DRIVE_MODE);
    
    /* Pin Configuration */
    
    // Variables for step timing
    uint16_t stepDelay = 100;  // Initial step delay in milliseconds
    uint16_t stepCounter = 0;
    uint32_t lastStepTime = 0;
    uint16_t maxStepRate = Stepper_GetMaxStepRate();
    
    // Enable the stepper motor
    Stepper_Init();
    
    // Main loop
    while (1) {
        uint8_t switch_state = 1;  // Default to FORWARD
        
        // Map potentiometer value to step delay (faster when pot is high)
        // Minimum delay is 1000/maxStepRate ms, maximum is 100ms
        uint16_t min_delay = 1000 / maxStepRate;
        uint16_t max_delay = 100;
        stepDelay = max_delay - ((pot_value * (max_delay - min_delay)) / 1023);
        if (stepDelay < min_delay) stepDelay = min_delay;
        
        // Check if it's time to take a step
        if (TIMERS_GetTime() - lastStepTime >= stepDelay) {
            lastStepTime = TIMERS_GetTime();
            
            // Take a step in the direction determined by switch
            Stepper_Step(switch_state);
            
            // Increment step counter
            stepCounter++;
            if (stepCounter >= STEPPER_STEPS) {
                stepCounter = 0;
                printf("Completed full revolution\r\n");
            }
        }
    }
    return 0;
}
#endif