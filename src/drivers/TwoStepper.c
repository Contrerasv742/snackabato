#include <TwoStepper.h>
#include <stdio.h>
#include <xc.h>
#include <sys/attribs.h>
//#include <peripheral/timer.h>

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//#define STEPPER_TEST

/* Note that you need to set the prescalar and peripheral clock appropriate to
 * the processor board that you are using. In order to calculate the minimal
 * prescalar: Prescalar = (2000*F_PB/(1000000*0xFFFF))+1, round down */
#ifndef F_CPU
#define F_CPU       80000000L
#define F_PB        (F_CPU/2)
#define F_PB_DIV8   (F_PB/8)
#define F_PB_DIV64  (F_PB/64)
#define ONE_KHZ_RATE  (F_PB_DIV8-1)/1000
#endif

#define MED_HZ_RATE 77
#define LOW_HZ_RATE 10
#define LOW_REP_NUM 64

#define ONE_HUNDRED_HZ 100
#define TWENTY_KILOHERTZ 20000

#define DEFAULT_STEP_RATE ONE_HUNDRED_HZ

#define LED_BANK1_3 LATDbits.LATD6
#define LED_BANK1_2 LATDbits.LATD11
#define LED_BANK1_1 LATDbits.LATD3
#define LED_BANK1_0 LATDbits.LATD5

#define ShutDownDrive() (COIL_A_ENABLE = 0, COIL_B_ENABLE = 0)
#define TurnOnDrive() (COIL_A_ENABLE = 1, COIL_B_ENABLE = 1)

#define ShutDownDrive_2() (COIL_A_ENABLE_2 = 0, COIL_B_ENABLE_2 = 0)
#define TurnOnDrive_2() (COIL_A_ENABLE_2 = 1, COIL_B_ENABLE_2 = 1)

/*******************************************************************************
 * PRIVATE STRUCTS and TYPEDEFS                                                *
 ******************************************************************************/
//integer round: (x - 1)/y + 1
/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

static int32_t stepCount = 0;
static uint32_t overflowReps = 0;
static uint8_t stepDir = FORWARD;
static uint16_t stepsPerSecondRate = DEFAULT_STEP_RATE;

static enum {
    off, inited, stepping, halted,
} stepperState, stepperState_2;

static enum {
    step_one, step_two, step_three, step_four,
} coilState, coilState_2;

static int32_t stepCount_2 = 0;
static uint32_t overflowReps_2 = 0;
static uint8_t stepDir_2 = FORWARD;
static uint16_t stepsPerSecondRate_2 = DEFAULT_STEP_RATE;


/*******************************************************************************
 * PRIVATE FUNCTIONS PROTOTYPES                                                *
 ******************************************************************************/
/**
 * @Function: CalculateOverflowPeriod(uint16_t rate);
 * @param pulse rate is steps per second (0 = 0.5Hz, special case)
 * @return period overflow for timer to match step rate
 * @remark Calculates the overflow period and sets the module variable
 *         overflowReps to match for the right step rate.
 *         Note: rate 0 is a special case corresponding to 0.5Hz
 * @author Gabriel Hugh Elkaim
 * @date 2012.01.28 23:21 */
uint32_t CalculateOverflowPeriod(uint16_t rate);

/**
 * @Function: FullStepDrive(void)
 * @param none
 * @return none
 * @remark Implements the full step drive state machine in terms of switching
 *         the coils in the right sequence.
 * @author Gabriel Hugh Elkaim
 * @date 2016.10.16 15:42 */
static void FullStepDrive(void);

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/* Stepper_Init(void) initializes the stepper module to step at 100Hz and makes
 * sure that all module level variables are initialized correctly. 
 */
int8_t TwoStepper_Init(void) {
    //Stepper 1
    uint16_t overflowPeriod;
    if (stepperState != off) {
        return ERROR;
    }
    stepCount = 0;
    overflowReps = 0;
    stepsPerSecondRate = DEFAULT_STEP_RATE;
    // Initialize hardware (no current flow)
    COIL_A_DIRECTION = 1;
    COIL_A_DIRECTION_INV = ~COIL_A_DIRECTION;
    COIL_B_DIRECTION = 1;
    COIL_B_DIRECTION_INV = ~COIL_B_DIRECTION;
    
    TRIS_COIL_A_DIRECTION = 0;
    TRIS_COIL_A_DIRECTION_INV = 0;
    TRIS_COIL_A_ENABLE = 0;
    TRIS_COIL_B_DIRECTION = 0;
    TRIS_COIL_B_DIRECTION_INV = 0;
    TRIS_COIL_B_ENABLE = 0;
    // Calculate overflow time and prescalar
    overflowPeriod = CalculateOverflowPeriod(stepsPerSecondRate);

    //    mT3IntEnable(1);
    stepperState = inited;

    //Stepper 2
    uint16_t overflowPeriod_2;
    if (stepperState_2 != off) {
        return ERROR;
    }
    stepCount_2 = 0;
    overflowReps_2 = 0;
    stepsPerSecondRate_2 = DEFAULT_STEP_RATE;
    // Initialize hardware (no current flow)
    COIL_A_DIRECTION_2 = 1;
    COIL_A_DIRECTION_INV_2 = ~COIL_A_DIRECTION;
    COIL_B_DIRECTION_2 = 1;
    COIL_B_DIRECTION_INV_2 = ~COIL_B_DIRECTION;
    
    TRIS_COIL_A_DIRECTION_2 = 0;
    TRIS_COIL_A_DIRECTION_INV_2 = 0;
    TRIS_COIL_A_ENABLE_2 = 0;
    TRIS_COIL_B_DIRECTION_2 = 0;
    TRIS_COIL_B_DIRECTION_INV_2 = 0;
    TRIS_COIL_B_ENABLE_2 = 0;
    // Calculate overflow time and prescalar
    overflowPeriod_2 = CalculateOverflowPeriod(stepsPerSecondRate);

    // Setup timer and interrupt
    T3CON = 0; // reset everything
    T3CONbits.TCKPS = 0b011;    // set prescaler 8:1
    TMR3 = 0; // start timer at 0
    PR3 = overflowPeriod;

    IFS0bits.T3IF = 0; // clear remnant flag
    IPC3bits.T3IP = 3; // set interrupt priority
    IEC0bits.T3IE = 1; // start interrupts for timer
    T3CONbits.ON = 1;
    //    mT3IntEnable(1);
    stepperState_2 = inited;
    return SUCCESS;
}

/* Sets the module variable with rate, and changes the overflow period
 * of the TIMER3 to generate the correct interrupt and repetition number
 * to match the number of steps per second.
 */
int8_t Stepper_SetRate(uint16_t rate, uint8_t stepper) {
    uint16_t overflowPeriod;
    stepsPerSecondRate = rate;
    if ((rate > TWENTY_KILOHERTZ)) {
        return ERROR;
    }
    T3CONbits.ON = 0; // halt timer3
    overflowPeriod = CalculateOverflowPeriod(rate);
    PR3 = overflowPeriod;
    if (stepperState != halted) {
        T3CONbits.ON = 1; // restart timer3
    }
    return SUCCESS;
}

// Wrapper function for the module variable that tracks rate
uint16_t Stepper_GetRate(uint8_t stepper) { return stepsPerSecondRate; }

// Sets the module level variable of direction and number of steps
int8_t Stepper_SetSteps(uint8_t direction, int32_t steps, uint8_t stepper) {
    if (stepper == STEPPER_1){
        if (stepperState == off) return ERROR;
        if ((direction == FORWARD) || (direction == REVERSE)) {
            stepDir = direction;
            stepCount = steps;
            return SUCCESS;
        }
    }
    else if (stepper == STEPPER_2){
        if (stepperState_2 == off) return ERROR;
        if ((direction == FORWARD) || (direction == REVERSE)) {
            stepDir_2 = direction;
            stepCount_2 = steps;
            return SUCCESS;
        }
    }
    return ERROR;
}

// Sets the steps and directions, and starts the stepper going
int8_t Stepper_InitSteps(uint8_t direction, int32_t steps, uint8_t stepper) {
    int8_t result = ERROR;
    if (stepper == STEPPER_1){
        if ((stepperState == off) || (steps == 0)) { 
            return ERROR;
        }
        result = Stepper_SetSteps(direction, steps, stepper);
        if (result == ERROR) {
            return result;
        }
        result = Stepper_StartSteps(stepper);
    }
    if (stepper == STEPPER_2){
        if ((stepperState_2 == off) || (steps == 0)) { 
            return ERROR;
        }
        result = Stepper_SetSteps(direction, steps, stepper);
        if (result == ERROR) {
            return result;
        }
        result = Stepper_StartSteps(stepper);
    }
    return result;
}

// Sets the enum for the stepper state to stepping
int8_t Stepper_StartSteps(uint8_t stepper) {
    if (stepper == STEPPER_1){
        if ((stepCount == 0) || (stepperState == stepping)) {
            return ERROR;
        }
        stepperState = stepping;
        TurnOnDrive();
    }
    if (stepper == STEPPER_2){
        if ((stepCount_2 == 0) || (stepperState_2 == stepping)) {
            return ERROR;
        }
        stepperState_2 = stepping;
        TurnOnDrive_2();
    }
    return SUCCESS;
}

// Sets the enum for the stepper state to halted
int8_t Stepper_StopsSteps(uint8_t stepper) {
    if (stepper == STEPPER_1){
        if ((stepperState == off) || (stepperState == halted)) {
            return ERROR;
        }
        stepperState = halted;
    }
    else if (stepper == STEPPER_2){
        if ((stepperState_2 == off) || (stepperState_2 == halted)) {
            return ERROR;
        }
        stepperState_2 = halted;
    }
    return SUCCESS;
}

// Wrapper to return the step count
int32_t Stepper_GetRemainingSteps(uint8_t stepper) { return stepCount; }

// Wrapper to return the direction
int8_t Stepper_GetDirection(uint8_t stepper) { return stepDir; }

// Wrapper function to check state
int8_t Stepper_IsStepping(uint8_t stepper) {
    if (stepper == STEPPER_1){
        return (stepperState == stepping); 
    } 
    if (stepper == STEPPER_2){
        return (stepperState_2 == stepping);
    }
    return ERROR;
}

int8_t Stepper_End(void)
{
    if (stepperState == off || stepperState_2 == off) {
        return ERROR;
    }
    T3CONbits.ON = 0; // halt timer3
    stepperState = off;
    ShutDownDrive();
    // turn hardware pins back to inputs
    TRIS_COIL_A_DIRECTION = 1;
    TRIS_COIL_A_DIRECTION_INV = 1;
    TRIS_COIL_A_ENABLE = 1;
    TRIS_COIL_B_DIRECTION = 1;
    TRIS_COIL_B_DIRECTION_INV = 1;
    TRIS_COIL_B_ENABLE = 1;
    // reset module variables
    stepCount = 0;
    overflowReps = 0;
    coilState = step_one;
    stepsPerSecondRate = DEFAULT_STEP_RATE;
    //Stepper 2
    stepperState_2 = off;
    ShutDownDrive_2();
    // turn hardware pins back to inputs
    TRIS_COIL_A_DIRECTION_2 = 1;
    TRIS_COIL_A_DIRECTION_INV_2 = 1;
    TRIS_COIL_A_ENABLE_2 = 1;
    TRIS_COIL_B_DIRECTION_2 = 1;
    TRIS_COIL_B_DIRECTION_INV_2 = 1;
    TRIS_COIL_B_ENABLE_2 = 1;
    // reset module variables
    stepCount_2 = 0;
    overflowReps_2 = 0;
    coilState_2 = step_one;
    stepsPerSecondRate_2 = DEFAULT_STEP_RATE;
    // turn off timer and interrupt
    T3CONbits.ON = 0; // shut down timer 3
    IEC0bits.T3IE = 0; // shut down interrupt
    return SUCCESS;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

/* There are three possibilities for the step rate calculation that keep the
   step rate error to under 0.2% of the desired value, from within 0.5 to 2KHz:
   from 78 to 20Khz, Prescale is 1:8, Rollover = (F_PB/8-1)/PPS
   from 10 to 77Hz, Prescale is 1:64, Rollover = (F_PB/64-1)/PPS
   from 0.5 to 10Hz, Set rollover for a constant 1Khz, and increment to reach
   the desired time, Prescale is 1:8, Rollover = (F_PB/8-1)/1000 and the number
   of times to repeat is (1000-1)/PPS + 1                                     */
uint32_t CalculateOverflowPeriod(uint16_t rate)
{
    if (rate == 0) {
        overflowReps = 2000;
        return (ONE_KHZ_RATE);
    }
    if (rate > MED_HZ_RATE) {
        overflowReps = 0;
        return ((F_PB_DIV8 - 1) / rate);
    }
    if (rate > LOW_HZ_RATE) {
       overflowReps = (1000 - 1) / rate;
        return ONE_KHZ_RATE;
    }
    // rate is less than 10Hz, switch to counted 1KHz pulses
    overflowReps = (1000 - 1) / rate + 1;
    return ONE_KHZ_RATE;
}

void FullStepDrive(void)
{
    switch (coilState) {
    case step_one:
        // coil drive both forward
        COIL_A_DIRECTION = 1;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 1;
        COIL_B_DIRECTION_INV = 0;
        if (stepDir == FORWARD) {
            coilState = step_two;
        } else {
            coilState = step_four;
        }
        break;

    case step_two:
        // coil drive A forward, B reverse
        COIL_A_DIRECTION = 1;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 1;
        if (stepDir == FORWARD) {
            coilState = step_three;
        } else {
            coilState = step_one;
        }
        break;

    case step_three:
        // coil drive both reverse
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 1;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 1;
        if (stepDir == FORWARD) {
            coilState = step_four;
        } else {
            coilState = step_two;
        }
        break;

    case step_four:
        // coil drive A reverse, B forward
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 1;
        COIL_B_DIRECTION = 1;
        COIL_B_DIRECTION_INV = 0;
        if (stepDir == FORWARD) {
            coilState = step_one;
        } else {
            coilState = step_three;
        }
        break;
    }
}

void FullStepDrive_2(void)
{
    switch (coilState_2) {
    case step_one:
        // coil drive both forward
        COIL_A_DIRECTION_2 = 1;
        COIL_A_DIRECTION_INV_2 = 0;
        COIL_B_DIRECTION_2 = 1;
        COIL_B_DIRECTION_INV_2 = 0;
        if (stepDir_2 == FORWARD) {
            coilState_2 = step_two;
        } else {
            coilState_2 = step_four;
        }
        break;

    case step_two:
        // coil drive A forward, B reverse
        COIL_A_DIRECTION_2 = 1;
        COIL_A_DIRECTION_INV_2 = 0;
        COIL_B_DIRECTION_2 = 0;
        COIL_B_DIRECTION_INV_2 = 1;
        if (stepDir_2 == FORWARD) {
            coilState_2 = step_three;
        } else {
            coilState_2 = step_one;
        }
        break;

    case step_three:
        // coil drive both reverse
        COIL_A_DIRECTION_2 = 0;
        COIL_A_DIRECTION_INV_2 = 1;
        COIL_B_DIRECTION_2 = 0;
        COIL_B_DIRECTION_INV_2 = 1;
        if (stepDir_2 == FORWARD) {
            coilState_2 = step_four;
        } else {
            coilState_2 = step_two;
        }
        break;

    case step_four:
        // coil drive A reverse, B forward
        COIL_A_DIRECTION_2 = 0;
        COIL_A_DIRECTION_INV_2 = 1;
        COIL_B_DIRECTION_2 = 1;
        COIL_B_DIRECTION_INV_2 = 0;
        if (stepDir_2 == FORWARD) {
            coilState_2 = step_one;
        } else {
            coilState_2 = step_three;
        }
        break;
    }
}

void WaveDrive(void)
{
    switch (coilState) {
    case step_one:
        // Only coil A forward
        COIL_A_DIRECTION = 1;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 0;
        if (stepDir == FORWARD) {
            coilState = step_two;
        } else {
            coilState = step_four;
        }
        break;

    case step_two:
        // Only coil B forward
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 1;
        COIL_B_DIRECTION_INV = 0;
        if (stepDir == FORWARD) {
            coilState = step_three;
        } else {
            coilState = step_one;
        }
        break;

    case step_three:
        // Only coil A reverse
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 1;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 0;
        if (stepDir == FORWARD) {
            coilState = step_four;
        } else {
            coilState = step_two;
        }
        break;

    case step_four:
        // Only coil B reverse
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 1;
        if (stepDir == FORWARD) {
            coilState = step_one;
        } else {
            coilState = step_three;
        }
        break;
    }
}

void HalfStepDrive(void) {
    static enum {
        half_step_one, half_step_two, half_step_three, half_step_four,
        half_step_five, half_step_six, half_step_seven, half_step_eight
    } halfStepState = half_step_one;
    
    switch (halfStepState) {
    case half_step_one:
        // Only coil A forward
        COIL_A_DIRECTION = 1;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 0;
        if (stepDir == FORWARD) {
            halfStepState = half_step_two;
        } else {
            halfStepState = half_step_eight;
        }
        break;

    case half_step_two:
        // Coil A forward, coil B forward
        COIL_A_DIRECTION = 1;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 1;
        COIL_B_DIRECTION_INV = 0;
        if (stepDir == FORWARD) {
            halfStepState = half_step_three;
        } else {
            halfStepState = half_step_one;
        }
        break;

    case half_step_three:
        // Only coil B forward
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 1;
        COIL_B_DIRECTION_INV = 0;
        if (stepDir == FORWARD) {
            halfStepState = half_step_four;
        } else {
            halfStepState = half_step_two;
        }
        break;

    case half_step_four:
        // Coil A reverse, coil B forward
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 1;
        COIL_B_DIRECTION = 1;
        COIL_B_DIRECTION_INV = 0;
        if (stepDir == FORWARD) {
            halfStepState = half_step_five;
        } else {
            halfStepState = half_step_three;
        }
        break;

    case half_step_five:
        // Only coil A reverse
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 1;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 0;
        if (stepDir == FORWARD) {
            halfStepState = half_step_six;
        } else {
            halfStepState = half_step_four;
        }
        break;

    case half_step_six:
        // Coil A reverse, coil B reverse
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 1;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 1;
        if (stepDir == FORWARD) {
            halfStepState = half_step_seven;
        } else {
            halfStepState = half_step_five;
        }
        break;

    case half_step_seven:
        // Only coil B reverse
        COIL_A_DIRECTION = 0;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 1;
        if (stepDir == FORWARD) {
            halfStepState = half_step_eight;
        } else {
            halfStepState = half_step_six;
        }
        break;

    case half_step_eight:
        // Coil A forward, coil B reverse
        COIL_A_DIRECTION = 1;
        COIL_A_DIRECTION_INV = 0;
        COIL_B_DIRECTION = 0;
        COIL_B_DIRECTION_INV = 1;
        if (stepDir == FORWARD) {
            halfStepState = half_step_one;
        } else {
            halfStepState = half_step_seven;
        }
        break;
    }
}

// Function to implement DRV8811 driver control (STEP/DIR interface)
void DRV8811Drive(void) {
    // Set direction pin based on stepDir
    if (stepDir == FORWARD) {
        COIL_A_DIRECTION = 1;      // Use as DIR pin
    } else {
        COIL_A_DIRECTION = 0;
    }
    
    // Generate step pulse (active high)
    COIL_B_DIRECTION = 1;          // Use as STEP pin
    
    // Short delay for pulse width (typically a few microseconds)
    int i;
    for (i = 0; i < 50; i++) {
        // Busy wait for pulse duration
        __asm("nop");
    }
    
    // Complete the step pulse
    COIL_B_DIRECTION = 0;

    for (i = 0; i < 5; i++) {
        __asm("nop");
    }
}

void __ISR(_TIMER_3_VECTOR) Timer3IntHandler(void) {
    static uint16_t timerLoopCount = 0;
    
    timerLoopCount++;
    if (timerLoopCount > overflowReps) {
        timerLoopCount = 0;
        // execute Stepper Drive state machine here
        //Stepper 1
        switch (stepperState) {
        case off: // should not get here
            T3CONbits.ON = 0; // halt timer3
            ShutDownDrive();
            IEC0bits.T3IE = 0;
            break;

        case inited:
        case halted:
            if (stepCount < 0) {
                stepCount = 0;
            }
            break;

        case stepping:
            if (--stepCount <= 0) {
                stepperState = halted;
            }
            TurnOnDrive();
            FullStepDrive();
            break;
        }

        //Stepper 2
        switch (stepperState_2) {
        case off: // should not get here
            T3CONbits.ON = 0; // halt timer3
            ShutDownDrive_2();
            IEC0bits.T3IE = 0;
            break;

        case inited:
        case halted:
            if (stepCount_2 < 0) {
                stepCount_2 = 0;
            }
            break;

        case stepping:
            if (--stepCount_2 <= 0) {
                stepperState_2 = halted;
            }
            TurnOnDrive_2();
            FullStepDrive_2();
            break;
        }
    }


    IFS0bits.T3IF = 0;  // clear interrupt flag
}

/*******************************************************************************
 * TEST HARNESS                                                                *
 ******************************************************************************/
#ifdef STEPPER_TEST

#include <stdio.h>

#define NOPCOUNT 150000
#define DELAY() for(i=0; i< NOPCOUNT; i++) __asm("nop")

void main(void)
{
    BOARD_Init();

    uint8_t errors = 0;
    uint16_t myRate = 0;
    uint16_t setRate = 1337;
    int32_t i, numSteps = 50, numSteps2 = 800;
    int8_t result;

    printf("\n\rStepper Module Test Harness\n\r");
    stepperState = inited;
    result = Stepper_Init();
    if (result == SUCCESS) {
        errors++;
    }
    stepperState = off;
    result = Stepper_Init();
    if (result != SUCCESS) {
        errors++;
    }
    if (errors) {
        printf("\n\rStepper_Init() function failed");
        while (1) {
            ;
        }
    } else {
        printf("\n\rStepper_Init() function passed");
    }

    myRate = Stepper_GetRate();
    if (myRate != DEFAULT_STEP_RATE) {
        errors++;
    }
    result = Stepper_SetRate(setRate);
    if (result != SUCCESS) {
        errors++;
    }
    myRate = Stepper_GetRate();
    if (myRate != setRate) {
        errors++;
    }
    if (errors) {
        printf("\r\nStepper_GetRate() or Stepper_SetRate() function failed");
        while (1) {
            ;
        }
    } else {
        printf("\r\nStepper_GetRate() and Stepper_SetRate() function passed");
    }

    stepperState = inited;
    result = Stepper_SetSteps(REVERSE, numSteps);
    if (result != SUCCESS) {
        errors++;
    }
    if (stepDir != REVERSE) {
        errors++;
    }
    if (stepCount != numSteps) {
        errors++;
    }
    if (stepperState != inited) {
        errors++;
    }
    if (errors) {
        printf("\r\nStepper_SetSteps() function failed");
        while (1) {
            ;
        }
    } else {
        printf("\r\nStepper_SetSteps() function passed");
    }

    result = Stepper_InitSteps(FORWARD, numSteps2);
    if (result != SUCCESS) {
        errors++;
    }
    if (stepDir != FORWARD) {
        errors++;
    }
    if (stepCount != numSteps2) {
        errors++;
    }
    if (stepperState != stepping) {
        errors++;
    }
    if (errors) {
        printf("\r\nStepper_InitSteps() function failed");
        while (1) {
            ;
        }
    } else {
        printf("\r\nStepper_InitSteps() function passed");
    }

    i = Stepper_GetRemainingSteps();
    if (i != numSteps2) {
        errors++;
    }
    if (errors) {
        printf("\r\nStepper_GetRemainingSteps() function failed");
        while (1) {
            ;
        }
    } else {
        printf("\r\nStepper_GetRemainingSteps() function passed");
    }

    result = Stepper_IsStepping();
    if (result != TRUE) {
        errors++;
    }
    if (errors) {
        printf("\r\nStepper_IsStepping() function failed");
        while (1) {
            ;
        }
    } else {
        printf("\r\nStepper_IsStepping() function passed");
    }

    result = Stepper_GetDirection();
    if (result != FORWARD) {
        errors++;
    }
    if (errors) {
        printf("\r\nStepper_GetDirection() function failed");
        while (1) {
            ;
        }
    } else {
        printf("\r\nStepper_GetDirection() function passed");
    }


    result = Stepper_StopsSteps();
    if (result != SUCCESS) {
        errors++;
    }
    if (stepperState != halted) {
        errors++;
    }
    if (errors) {
        printf("\r\nStepper_StopSteps() function failed");
        while (1) {
            ;
        }
    } else {
        printf("\r\nStepper_StopSteps() function passed");
    }


    stepperState = off;
    result = Stepper_End();
    if (result == SUCCESS) {
        errors++;
    }
    stepperState = inited;
    result = Stepper_End();
    if (result != SUCCESS) {
        errors++;
    }
    if (errors) {
        printf("\n\rStepper_End() function failed");
        while (1) {
            ;
        }
    } else {
        printf("\n\rStepper_End() function passed");
    }

    printf("\n\rTerminating test harness");
    

    Stepper_Init();
    Stepper_SetRate(setRate);
    printf("\n\r\n\rNow setting stepper to turn forwards and backwards %d steps at %d Hz", numSteps, Stepper_GetRate());
    Stepper_InitSteps(FORWARD, numSteps);
    printf("\r\nStepping Forwards");
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
}
#endif
