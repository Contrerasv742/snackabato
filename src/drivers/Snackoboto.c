/*
 * File:   Snackoboto.h
 * Author: Andy Ly
 *
 */

#include <IO_Ports.h>
#include <xc.h>
#include <AD.h>
#include <TwoStepper.h>
#include <timers.h>
#include <stdio.h>
#include <pwm.h>
#include <RC_Servo.h>
#include <BOARD.h>
#include "TapeSensor.h"
#include "IR_Sensor.h"
#include "ping.h"
#include "EventChecker.h"

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/


typedef enum {
     RIGHT,
     LEFT,
} Direction;

// Define constants for stepper testing
#define STEPPER_STEPS 200
#define MAX_STEP_RATE_TEST 5000  
#define STEP_RATE_INCREMENT 50
#define STEPPER_STEP_RATE 100
#define STEPPER_RESOLUTION 1.8

#define STEP_INTERVAL 1
#define TIME_INTERVAL 200
#define ANGLE_PER_STEP 1.8
#define MAX_YAW 15

// Defines for the Servo Motors (Part 1)
#define SERVO_PIN RC_PORTV03
#define SERVO_STEP_RATE 600
#define SINGLE_FIRE_DUTY_CYCLE 150
#define SERVO_INIT_DUTY 1000

// Defines for the DC Motors (Part 4)
//#define ENABLE_PIN          RC_PORTY07
#define DC_DIRECTION_PIN1_TRIS   PORTY09_TRIS //RC_PORTV03
#define DC_DIRECTION_PIN2_TRIS   PORTY11_TRIS //RC_PORTW07
#define DC_DIRECTION_PIN1   PORTY09_LAT //RC_PORTV03
#define DC_DIRECTION_PIN2   PORTY11_LAT //RC_PORTW07

#define DC_PWM_MOTOR_PIN    PWM_PORTY10

#define DC_STEP_RATE 100
// Defines for the Stepper Motors (Part 5)
// #define COIL1_PIN1           PORTZ03_LAT
// #define COIL1_PIN2           PORTZ04_LAT
// #define COIL2_PIN1           PORTZ05_LAT
// #define COIL2_PIN2           PORTZ06_LAT

// #define STEPPER_1_ENABLE_PIN_A          RC_PORTZ11
// #define STEPPER_1_ENABLE_PIN_B          RC_PORTZ09

// #define STEPPER_1_PWM_MOTOR_PIN_A   PWM_PORTZ11  // Define missing pin
// #define STEPPER_1_PWM_MOTOR_PIN_B   PWM_PORTZ12

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

static Direction SnackoDirection;
static double YawDisplacement;
static double PitchDisplacement;
static unsigned short int ServoDuty;

 /**
 * @Function Snacko_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware for Snackoboto */
int Snacko_Init(void){
    AD_Init();
    PWM_Init();
    RC_Init();
    TwoStepper_Init();

    //DC Motor
    PWM_SetFrequency(PWM_5KHZ);
    PWM_AddPins(DC_PWM_MOTOR_PIN);  
    DC_DIRECTION_PIN1_TRIS = 0;
    DC_DIRECTION_PIN2_TRIS = 0;
    DC_DIRECTION_PIN1 = 0;
    DC_DIRECTION_PIN2 = 0;
    /*
    IO_PortsSetPortOutputs(PORTY, ENABLE_PIN);
    IO_PortsWritePort(PORTY, ENABLE_PIN);
    IO_PortsSetPortOutputs(PORTV, DC_DIRECTION_PIN1);
    IO_PortsSetPortOutputs(PORTW, DC_DIRECTION_PIN2);
     * */
    
    //RC Servo
    RC_AddPins(SERVO_PIN);
    //Stepper
    Stepper_SetRate(STEPPER_STEP_RATE, STEPPER_1);
    //Reset Static Variables
    SnackoDirection = RIGHT;
    YawDisplacement = 0;
    PitchDisplacement = 0;
    ServoDuty = SERVO_INIT_DUTY;
    RC_SetPulseTime(SERVO_PIN, SERVO_INIT_DUTY);
    ServoDuty = SERVO_INIT_DUTY;
//    Stepper_InitSteps(FORWARD, 1, STEPPER_2);
//    Stepper_InitSteps(FORWARD, 1, STEPPER_1);
    return SUCCESS;
}

/**
 * @Function Snacko_RotateLeft(unsigned int steps)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Rotates Snackoboto Left*/
int Snacko_RotateLeft(unsigned int steps){
    if (!Stepper_IsStepping(STEPPER_2)){
        Stepper_InitSteps(FORWARD, steps, STEPPER_2);
    }
    YawDisplacement = YawDisplacement - (ANGLE_PER_STEP * steps);
    return SUCCESS;
}

/**
 * @Function Snacko_RotateRight(unsigned int steps)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Rotates Snackoboto Right*/
int Snacko_RotateRight(unsigned int steps){
    if (!Stepper_IsStepping(STEPPER_2)){
        Stepper_InitSteps(REVERSE, steps, STEPPER_2);
    }
    //printf("%f adding %f\r\n", YawDisplacement, YawDisplacement + (ANGLE_PER_STEP * steps));
    YawDisplacement = YawDisplacement + (ANGLE_PER_STEP * steps);
    return SUCCESS;
}

/**
 * @Function Snacko_PitchDown(unsigned in steps)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Pithces Snackoboto Down*/
int Snacko_PitchDown(unsigned int steps){
    if (!Stepper_IsStepping(STEPPER_1)){
        Stepper_InitSteps(FORWARD, steps, STEPPER_1);
    }
    return SUCCESS;
}

/**
 * @Function Snacko_PitchDown(unsigned in steps)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Pithces Snackoboto Down*/
int Snacko_PitchUp(int32_t steps){
    if (!Stepper_IsStepping(STEPPER_1)){
        Stepper_InitSteps(REVERSE, steps, STEPPER_1);
    }
    return SUCCESS;
}

/**
 * @Function Snacko_SetPitch(int angle)
 * APPROXIMATE_ANGLE = ANGLE - (ANGLE % RESOLUTION)
 * STEPS = APPROXIMATE_ANGLE / 1.8 deg
 * @param None
 * @return SUCCESS or ERROR
 * @brief Pithces Snackoboto to Specified Angle*/
int Snacko_SetPitch(int angle){
    double roundAngle = angle - ( ((angle*10) % (int)(STEPPER_RESOLUTION*10)) / 10.0);
    double angleNeeded = PitchDisplacement - roundAngle;
    int steps = angleNeeded / STEPPER_RESOLUTION;
    PitchDisplacement += angleNeeded;
    //printf("Snacko Setting Pitch : %f deg, %d steps\r\n", roundAngle, steps);
    if (steps > 0){
        if (!Stepper_IsStepping(STEPPER_1)){
            Stepper_InitSteps(REVERSE, steps, STEPPER_1);
        }
    }
    else if (steps < 0){
        if (!Stepper_IsStepping(STEPPER_1)){
            Stepper_InitSteps(FORWARD, steps, STEPPER_1);
        }
    }
    else {
        printf("SetPitch ERROR: Already at %d\r\n", angle);
    }
    return SUCCESS;
}

/**
 * @Function Snacko_SetFlywheelSpeed(unsigned int speed)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Sets Flywheel Speed of Snackoboto (0 - 1000)*/
int Snacko_SetFlywheelSpeed(unsigned int DutyCycle){
    if (DutyCycle == 0){
        PWM_SetDutyCycle(DC_PWM_MOTOR_PIN, DutyCycle);
        DC_DIRECTION_PIN1 = 0;
        DC_DIRECTION_PIN2 = 0;
    }
    else{
        PWM_SetDutyCycle(DC_PWM_MOTOR_PIN, DutyCycle);
        DC_DIRECTION_PIN1 = 1;
        DC_DIRECTION_PIN2 = 0;
    }
    /*
    IO_PortsWritePort(PORTV, DC_DIRECTION_PIN1);
    IO_PortsClearPortBits(PORTW, DC_DIRECTION_PIN2);
     * */
    return SUCCESS;
}

/**
 * @Function Snacko_FireCandy(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Rotates Servo to Fire a Single Candy*/
int Snacko_FireCandy(void){
    RC_SetPulseTime(SERVO_PIN, ServoDuty + SINGLE_FIRE_DUTY_CYCLE);
    ServoDuty += SINGLE_FIRE_DUTY_CYCLE;
    printf("Servo: %d\r\n", ServoDuty);
    return SUCCESS;
}

/**
 * @Function Snacko_ResetServi(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Rotates Servo to Initial Position*/
int Snacko_ResetServo(void){
    
    RC_SetPulseTime(SERVO_PIN, SERVO_INIT_DUTY);
    ServoDuty = SERVO_INIT_DUTY;
    /*
    RC_SetPulseTime(SERVO_PIN, ServoDuty - SINGLE_FIRE_DUTY_CYCLE);
    ServoDuty -= SINGLE_FIRE_DUTY_CYCLE;*/
    //printf("Servo: %d\r\n", ServoDuty);
    return SUCCESS;
}

/**
 * @Function Snacko_SetDirection(Direction d)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Sets Status Variable of Sweep Direction*/
void Snacko_SetDirection(Direction d){
    SnackoDirection = d;
}

/**
 * @Function Snacko_GetDirection(void)
 * @param None
 * @return Direction
 * @brief Gets Status Variable of Sweep Direction*/
Direction Snacko_GetDirection(void){
    return SnackoDirection;
}

/**
 * @Function Snacko_SetYawDispalcement(int angle)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Sets Status Variable of Yaw Dispalcement*/
void Snacko_SetYawDisplacement(double angle){
    YawDisplacement = angle;
}

/**
 * @Function Snacko_GetYawDisplacement(void)
 * @param None
 * @return Direction
 * @brief Gets Status Variable of Yaw Displacement*/
double Snacko_GetYawDisplacement(void){
    //printf("Returning %f\r\n", YawDisplacement);
    return YawDisplacement;
}

/**
 * @Function Snacko_SetPitchDispalcement(int angle)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Sets Status Variable of Pitch Dispalcement*/
void Snacko_SetPitchDisplacement(double angle){
    PitchDisplacement = angle;
}

/**
 * @Function Snacko_GetPitchDisplacement(void)
 * @param None
 * @return Direction
 * @brief Gets Status Variable of Pitch Displacement*/
double Snacko_GetPitchDisplacement(void){
    return PitchDisplacement;
}

//#define SNACKO_TEST
#ifdef SNACKO_TEST
#define DELAY(x)    for (wait = 0; wait <= x; wait++) {asm("nop");}
#define A_BIT       18300
#define A_BIT_MORE  36600
#define YET_A_BIT_LONGER (A_BIT_MORE<<2)
#define A_LOT       183000
#define NUM_TIMES_REPEAT_LED 5
#define MOTOR_TIME (A_LOT<<2)

 #include <stdio.h>
 
 void main(void) {
     unsigned int wait;
     BOARD_Init();
     /* user initialization code goes here */
     Snacko_Init();
     IR_Init();
     Ping_Init();
     TapeSensor_Init();
     /*
     //FLYWHEEL TEST
     Snacko_SetFlywheelSpeed(500);
     printf("Flywheel On\r\n");
     DELAY(MOTOR_TIME);
     Snacko_SetFlywheelSpeed(0);
     printf("Flywheel Off\r\n");
     DELAY(MOTOR_TIME);
     //ROTATE TEST
     Snacko_RotateLeft(8);
     printf("Yaw Displacement: %d\r\n", Snacko_GetYawDisplacement());
     DELAY(MOTOR_TIME);
     Snacko_RotateRight(8);
     printf("Yaw Displacement: %d\r\n", Snacko_GetYawDisplacement());
     DELAY(MOTOR_TIME);
     //PITCH TEST
     Snacko_PitchDown(8);
     printf("Pitch Displacement: %d\r\n", Snacko_GetPitchDisplacement());
     DELAY(MOTOR_TIME);
     Snacko_SetPitch(14.4);
     printf("Pitch Displacement: %d\r\n", Snacko_GetPitchDisplacement());
     DELAY(MOTOR_TIME);
     //SERVO TEST
     for (int i = 0; i < 4; i++){
         printf("Single Candy Fired\r\n");
         Snacko_FireCandy();
         DELAY(MOTOR_TIME);
     }
                   
     printf("done\r\n");
      * */
     //while(1);
     printf("Starting Snackoboto Test (Keyboard Input)\r\n");
     printf("*************************KEYBOARD INPUTS*************************\r\n"
             "w: Flywheel On\t\ts: Flywheel Off\t\ta: Rotate Left\r\n"
                            "d: Rotate Right\t\tq: Pitch Up\t\te: Pitch Down\r\n"
                            "f: Fire Candy\t\tr: Reset Servo\t\tp: Ping Reading\r\n"
                            "i: Left IR\t\to: Right IR\t\tt: Tape Sensor\r\n"
                            "m: Keyboard Input Menu\r\n"
             "*******************************************************************\r\n");
     unsigned int ping;
     while (1) {
         CheckObstacle();
         CheckIRPeak();
         CheckTapeReading();
        int reading;
        if (!IsReceiveEmpty()) {
            char input = GetChar();
            switch (input) {
                case 'w':
                    Snacko_SetFlywheelSpeed(1000);
                    printf("Flywheel On\r\n");
                    //DELAY(MOTOR_TIME);
                    break;
                case 's':
                    Snacko_SetFlywheelSpeed(0);
                    printf("Flywheel Off\r\n");
                    //DELAY(MOTOR_TIME);
                    break;
                case 'a':
                    Snacko_RotateLeft(8);
                    printf("Rotating Left\r\n");
                    //DELAY(MOTOR_TIME);
                    break;
                case 'd':
                    Snacko_RotateRight(8);
                    printf("Rotating Right\r\n");
                    //DELAY(MOTOR_TIME);
                    break;
                case 'q':
                    Snacko_PitchDown(5);
                    printf("Pitching Down\r\n");
                    break;
                case 'e':
                    Snacko_PitchUp(5);
                    printf("Pitching Up\r\n");
                    break;
                case 'f':
                    Snacko_FireCandy();
                    printf("Firing Candy\r\n");
                    break;
                case 'r':
                    Snacko_ResetServo();
                    printf("Resetting Servo\r\n");
                    break;
                case 'p':
                    ping = Ping_GetDistance();
                    printf("Ping Reading: %d\r\n", ping);
                    break;
                case 'i':
                    reading = IR_GetReadingL();
                    printf("Left IR Reading: %d\r\n", reading);
                    break;
                case 'o':
                    reading = IR_GetReadingR();
                    printf("Right IR Reading: %d\r\n", reading);
                    break;
                case 't':
                    reading = TapeSensor_GetReading();
                    printf("Tape Sensor Reading: %d\r\n", reading);
                    break;
                case 'm':
                    printf("*************************KEYBOARD INPUTS*************************\r\n"
                            "w: Flywheel On\t\ts: Flywheel Off\t\ta: Rotate Left\r\n"
                            "d: Rotate Right\t\tq: Pitch Up\t\te: Pitch Down\r\n"
                            "f: Fire Candy\t\tr: Reset Servo\t\tp: Ping Reading\r\n"
                            "i: Left IR\t\to: Right IR\t\tt: Tape Sensor\r\n"
                            "m: Keyboard Input Menu\r\n"
                            "*****************************************************************\r\n");
                    break;
            }
        }
    }

 }
#endif