/*
 * File: TargetLAimSubHSM.c
 * Author: Andy Ly
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"
#include "BOARD.h"
#include "SnackobotoHSM.h"
#include "TargetLSubHSM.h"
#include "TargetLAimSubHSM.h"
#include "Snackoboto.h"
#include "ping.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    NextPeak,
    Centering,
    Angle,
} TargetLAimSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "NextPeak",
    "Centering",
    "Angle",
};

#define STEP_INTERVAL 4
#define TIME_INTERVAL 1000
#define ANGLE_PER_STEP 1
#define AVERAGE_CONST 5
#define PITCH_CONST 0.05



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static TargetLAimSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static int StepCount;
static unsigned short total;
static uint8_t count;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTargetLAimSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTargetLAimSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunTargetLAimSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunTargetLAimSubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the heirarchical state
 *        machine, as this is called any time a new event is passed to the event
 *        queue. This function will be called recursively to implement the correct
 *        order for a state transition to be: exit current state -> enter next state
 *        using the ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @author Gabriel H Elkaim, 2011.10.23 19:25 */
ES_Event RunTargetLAimSubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    TargetLAimSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
    case InitPSubState: // If current state is initial Psedudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state

            // now put the machine into the actual initial state
            nextState = NextPeak;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

    case NextPeak:
        if (ThisEvent.EventType == ES_ENTRY){
            StepCount = 0;
            //ES_Timer_Init();
            ES_Timer_InitTimer(4, TIME_INTERVAL);
            ThisEvent.EventType = ES_NO_EVENT;
        }
        if (ThisEvent.EventType == ES_TIMEOUT && ThisEvent.EventParam == 4){
            StepCount++;
            Snacko_RotateLeft(STEP_INTERVAL);
            //ES_Timer_Init();
            ES_Timer_InitTimer(4, TIME_INTERVAL);
            ThisEvent.EventType = ES_NO_EVENT;
            if (StepCount > 4){
                ThisEvent.EventType = TARGET_LOST;
            }
        }
        if (ThisEvent.EventType == PEAK_R_DETECTED){
            printf("Second Peak Detected at %f\r\n", Snacko_GetYawDisplacement());
            nextState = Centering;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;
    
    case Centering:
        if (ThisEvent.EventType == ES_ENTRY){
            StepCount = StepCount / 2;
            //ES_Timer_Init();
            ES_Timer_InitTimer(4, TIME_INTERVAL);
            ThisEvent.EventType = ES_NO_EVENT;
        }
        if (ThisEvent.EventType == ES_TIMEOUT && ThisEvent.EventParam == 4){
            StepCount--;
            Snacko_RotateRight(STEP_INTERVAL);
            if (StepCount <= 0){
                printf("Centered at %f\r\n", Snacko_GetYawDisplacement());
                nextState = Angle;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else{
                //ES_Timer_Init();
                ES_Timer_InitTimer(4, TIME_INTERVAL);
            }
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

    case Angle:
        if (ThisEvent.EventType == ES_ENTRY){
            //total = 0;
            count = 0;
            //ES_Timer_Init();
            ES_Timer_InitTimer(4, 500);
            ThisEvent.EventType = ES_NO_EVENT;
        }
        if (ThisEvent.EventType == ES_TIMEOUT && ThisEvent.EventParam == 4){
            //printf("angling\r\n");
            count++;
            if (count < 4){
                Snacko_PitchUp(4);
                ES_Timer_InitTimer(2, 250);
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else {
                count = 0;
                ThisEvent.EventType = AIMED;
                //printf("aimed\r\n");
            }
            /*
            Snacko_PitchUp(5);
            //printf("pitch\r\n");
            ES_Timer_InitTimer(4, 250);
            ThisEvent.EventType = ES_NO_EVENT;
            /*
            count++;
            //total += Ping_GetDistance();
            if (count >= AVERAGE_CONST){
                //unsigned short averageDist = total / count;
                //printf("Aiming at %f\r\n", averageDist * PITCH_CONST);
                Snacko_SetPitch(8);
                total = 0;
                count = 0;
                ThisEvent.EventType = AIMED;
            }
            else{
                //ES_Timer_Init();
                ES_Timer_InitTimer(4, TIME_INTERVAL);
                ThisEvent.EventType = ES_NO_EVENT;
            }
            */
        }
        /*
        if (ThisEvent.EventType == TAPE_LOST){
            ThisEvent.EventType = AIMED;
        }
         * */
        break;
        
    default: // all unhandled states fall into here
        break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunTargetLAimSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunTargetLAimSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

