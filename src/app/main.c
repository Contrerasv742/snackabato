#include <IO_Ports.h>
#include <AD.h>
#include <Stepper.h>
#include <timers.h>
#include <stdio.h>
#include <pwm.h>
#include <RC_Servo.h>
#include <BOARD.h>
#include "Snackoboto.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "IR_Sensor.h"
#include "HallSensor.h"
#include "ping.h"
#include "TapeSensor.h"

// Define constants for stepper testing
#define STEPPER_STEPS 200
#define MAX_STEP_RATE_TEST 5000  
#define STEP_RATE_INCREMENT 50

// Defines for the Servo Motors (Part 1)
#define SERVO_PIN RC_PORTV04

// Defines for the DC Motors (Part 4)
#define ENABLE_PIN          RC_PORTY07
#define DC_DIRECTION_PIN1   RC_PORTV03
#define DC_DIRECTION_PIN2   RC_PORTW07

#define DC_PWM_MOTOR_PIN    PWM_PORTZ06

// Defines for the Stepper Motors (Part 5)
// #define COIL1_PIN1           PORTZ03_LAT
// #define COIL1_PIN2           PORTZ04_LAT
// #define COIL2_PIN1           PORTZ05_LAT
// #define COIL2_PIN2           PORTZ06_LAT

// #define STEPPER_1_ENABLE_PIN_A          RC_PORTZ11
// #define STEPPER_1_ENABLE_PIN_B          RC_PORTZ09

// #define STEPPER_1_PWM_MOTOR_PIN_A   PWM_PORTZ11  // Define missing pin
// #define STEPPER_1_PWM_MOTOR_PIN_B   PWM_PORTZ12

//#define STEPPER_TEST
//#define DC_MOTOR_TEST
//#define RC_SERVO_TEST
//#define MAIN

#ifdef MAIN
void main(void)
{
    ES_Return_t ErrorType;

    BOARD_Init();

    printf("Starting ES Framework Template\r\n");
    printf("using the 2nd Generation Events & Services Framework\r\n");


    // Your hardware initialization function calls go here
    Snacko_Init();
    IR_Init();
    HallSensor_Init();
    Ping_Init();
    TapeSensor_Init();

    // now initialize the Events and Services Framework and start it running
    ErrorType = ES_Initialize();
    if (ErrorType == Success) {
        ErrorType = ES_Run();

    }
    //if we got to here, there was an error
    switch (ErrorType) {
    case FailedPointer:
        printf("Failed on NULL pointer");
        break;
    case FailedInit:
        printf("Failed Initialization");
        break;
    default:
        printf("Other Failure: %d", ErrorType);
        break;
    }
    for (;;)
        ;

};
#endif

#ifdef STEPPER_TEST
int main(void) {
    BOARD_Init();
    AD_Init();
    TIMERS_Init();
    RC_Init();
    Stepper_Init();
    PWM_Init();

    static uint32_t stepCounter = 0;
    static uint8_t switch_state = FORWARD;
    static uint32_t currentStepRate = 100;
    static uint32_t numSteps = 100;

    // Enable coil driver outputs

    PWM_SetFrequency(PWM_1KHZ);
    // IO_PortsSetPortOutputs(PORTZ, STEPPER_1_ENABLE_PIN_A | STEPPER_1_ENABLE_PIN_B);
    // IO_PortsSetPortOutputs(PORTZ, COIL1_PIN1 | COIL1_PIN2 | COIL2_PIN1 | COIL2_PIN2);

    Stepper_SetRate(currentStepRate);
    Stepper_InitSteps(switch_state, numSteps);  // Start first 100 steps
    
    while (1) {

        if (!Stepper_IsStepping()) {
            if (Stepper_GetDirection() == FORWARD) {
                Stepper_InitSteps(REVERSE, numSteps);
                printf("\r\nStepping Backwards");
            } else {
                Stepper_InitSteps(FORWARD, numSteps);
                printf("\r\nStepping Forwards");
            }
        }
    }
    return 0;
}
#endif

#ifdef DC_MOTOR_TEST
int main(void) {
    /* Initialization Section */
    BOARD_Init();
    AD_Init();
    TIMERS_Init();
    RC_Init();
    Stepper_Init();
    PWM_Init();
                  
    // PWM(square wave) output for DC motor
    PWM_AddPins(DC_PWM_MOTOR_PIN);   
    IO_PortsSetPortOutputs(PORTY, ENABLE_PIN);
    IO_WritePort(PORTY, ENABLE_PIN);
    
    // Configure direction control pins for the H-bridge
    IO_PortsSetPortOutputs(PORTV, DC_DIRECTION_PIN1);
    IO_PortsSetPortOutputs(PORTW, DC_DIRECTION_PIN2);
    
    // Set PWM frequency to 1KHz (default)
    PWM_SetFrequency(PWM_1KHZ);
    
    while (1) {
        uint32_t DC_Step_Rate = 100;
        
        unsigned int duty_cycle = (DC_Step_Rate * 1000) / 1023;
        PWM_SetDutyCycle(PWM_MOTOR_PIN, duty_cycle);
        
        // Set direction
        IO_PortsWritePort(PORTV, DC_DIRECTION_PIN1);
        IO_PortsClearPortBits(PORTW, DC_DIRECTION_PIN2);
        
    }
    return 0;
}
#endif

#ifdef RC_SERVO_TEST
int main(void) {
    /* Initialization Section */
    BOARD_Init();
    AD_Init();
    RC_Init();
    
    RC_AddPins(RC_PORTV04);
    
    while (1) {
        
        // Manually control step rate (X =steps/sec)
        uint32_t Servo_Step_Rate = 600;
        
        // Servo Motor Configuration
        unsigned int Servo_Duty_Cycle = 1000 + (Servo_Step_Rate * 1000) / 1023;
        RC_SetPulseTime(RC_PORTV04, Servo_Duty_Cycle);
        RC_GetPulseTime(RC_PORTV04);
    }
    return 0;
}
#endif
