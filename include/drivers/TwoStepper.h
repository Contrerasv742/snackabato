/*
 * File:   TwoStepper.h
 * Author: 
 */

#ifndef TWO_STEPPER_H
#define TWO_STEPPER_H

#include <BOARD.h>

/*******************************************************************************
 * STEPPER MODE #DEFINES                                                       *
 ******************************************************************************/

#define FULL_STEP_DRIVE
//#define HALF_STEP_DRIVE
//#define WAVE_DRIVE
//#define DRV8811_DRIVE

#if defined FULL_STEP_DRIVE && ( defined HALF_STEP_DRIVE || defined WAVE_DRIVE || defined DRV8811_DRIVE )
#error "Define only one stepper drive mode at a time"
#endif

#if defined HALF_STEP_DRIVE && ( defined FULL_STEP_DRIVE || defined WAVE_DRIVE || defined DRV8811_DRIVE )
#error "Define only one stepper drive mode at a time"
#endif

#if defined WAVE_DRIVE && ( defined HALF_STEP_DRIVE || defined FULL_STEP_DRIVE || defined DRV8811_DRIVE )
#error "Define only one stepper drive mode at a time"
#endif

#if defined DRV8811_DRIVE && ( defined HALF_STEP_DRIVE || defined FULL_STEP_DRIVE || defined WAVE_DRIVE )
#error "Define only one stepper drive mode at a time"
#endif

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/

#define FORWARD 1
#define REVERSE 0

#define TRIS_COIL_A_ENABLE TRISFbits.TRISF1     	//PORTZ_04
#define TRIS_COIL_A_DIRECTION TRISEbits.TRISE4  	//PORTZ_03
#define TRIS_COIL_A_DIRECTION_INV TRISEbits.TRISE3	//PORTZ_05
#define TRIS_COIL_B_ENABLE TRISDbits.TRISD8     	//PORTZ_08
#define TRIS_COIL_B_DIRECTION TRISEbits.TRISE2  	//PORTZ_07
#define TRIS_COIL_B_DIRECTION_INV TRISEbits.TRISE1  //PORTZ_09

#define COIL_A_ENABLE LATFbits.LATF1
#define COIL_A_DIRECTION LATEbits.LATE4
#define COIL_A_DIRECTION_INV LATEbits.LATE3
#define COIL_B_ENABLE LATDbits.LATD8
#define COIL_B_DIRECTION LATEbits.LATE2
#define COIL_B_DIRECTION_INV LATEbits.LATE1

#define TRIS_COIL_A_ENABLE_2 TRISBbits.TRISB0     	//PORTX_04
#define TRIS_COIL_A_DIRECTION_2 TRISFbits.TRISF5  	//PORTX_03
#define TRIS_COIL_A_DIRECTION_INV_2 TRISGbits.TRISG6	//PORTX_05
#define TRIS_COIL_B_ENABLE_2 TRISFbits.TRISF6     	//PORTX_08
#define TRIS_COIL_B_DIRECTION_2 TRISDbits.TRISD7  	//PORTX_10
#define TRIS_COIL_B_DIRECTION_INV_2 TRISDbits.TRISD4  //PORTX_11

#define COIL_A_ENABLE_2 LATBbits.LATB0
#define COIL_A_DIRECTION_2 LATFbits.LATF5
#define COIL_A_DIRECTION_INV_2 LATGbits.LATG6
#define COIL_B_ENABLE_2 LATFbits.LATF6
#define COIL_B_DIRECTION_2 LATDbits.LATD7
#define COIL_B_DIRECTION_INV_2 LATDbits.LATD4

#define STEPPER_1 0
#define STEPPER_2 1

/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

/**
 * @Function: Stepper_Init(void);
 * @param none
 * @return SUCCESS or ERROR
 * @brief Initializes the Stepper Module, sets up the stepper on PORTZ
 * @note Defaults to a stepping rate of MED_HZ_RATE
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t TwoStepper_Init(void);

/**
 * @Function Stepper_SetRate(unsigned short int rate);
 * @param rate, steps per second, 0 is a special case of 0.5Hz
 * @return SUCCESS or ERROR
 * @brief Sets the stepping rate in steps per second
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_SetRate(uint16_t rate, uint8_t stepper);

/**
 * @Function Stepper_GetRate(void);
 * @param none
 * @return rate in steps per second
 * @brief Gets the stepping rate in steps per second
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
uint16_t Stepper_GetRate(uint8_t stepper);

/**
 * @Function: Stepper_SetSteps(char direction, unsigned int steps);
 * @param direction - stepper direction (FORWARD or REVERSE)
 * @param steps - number of steps to take
 * @return SUCCESS or ERROR
 * @brief Sets the number of steps and direction for the stepper drive. Wipes
 *        out any previous values, does NOT start stepping. If the stepper is
 *        already stepping, then the stepper will continue stepping.
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_SetSteps(uint8_t direction, int32_t steps, uint8_t stepper);

/**
 * @Function: Stepper_InitSteps(char direction, unsigned int steps);
 * @param direction - stepper direction (FORWARD or REVERSE)
 * @param steps - number of steps to take
 * @return SUCCESS or ERROR
 * @brief Sets the number of steps and direction for the stepper drive. Wipes
 *        out any previous stepper command and starts stepping.
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_InitSteps(uint8_t direction, int32_t steps, uint8_t stepper);

/**
 * @Function: Stepper_StartSteps(void);
 * @param none
 * @return SUCCESS or ERROR
 * @brief Starts the stepper motor stepping
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_StartSteps(uint8_t stepper);

/**
 * @Function: Stepper_StopSteps(void);
 * @param none
 * @return SUCCESS or ERROR
 * @brief Stops the stepper motor stepping
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_StopsSteps(uint8_t stepper);

/**
 * @Function: Stepper_GetRemainingSteps(void);
 * @return number of remaining steps
 * @brief Returns the number of remaining steps
 * @author Gabriel Hugh Elkaim, 2012.01.28 23:21 */
int32_t Stepper_GetRemainingSteps(uint8_t stepper);

/**
 * @Function: Stepper_GetDirection(void);
 * @return FORWARD or REVERSE
 * @brief Returns the current direction (or previous if stopped)
 * @author Gabriel Hugh Elkaim, 2012.01.28 23:21 */
int8_t Stepper_GetDirection(uint8_t stepper);

/**
 * @Function: Stepper_IsStepping(void);
 * @return TRUE or FALSE
 * @brief Returns TRUE if the stepper is currently stepping, FALSE otherwise
 * @author Gabriel Hugh Elkaim, 2016.10.13 15:37 */
int8_t Stepper_IsStepping(uint8_t stepper);

/**
 * @Function: Stepper_End(void);
 * @return SUCCESS or ERROR
 * @brief Shuts down the stepper driver software module. Module can be re-enabled
 *        using a stepper init.
 * @author Gabriel Hugh Elkaim, 2012.01.28 23:21 */
int8_t Stepper_End(void);



#endif //TWO_STEPPER_H
