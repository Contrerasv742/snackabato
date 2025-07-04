/*
 * File: SearchingSubHSM.c
 * Author: Andy Ly
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "SnackobotoHSM.h"
#include "SearchingSubHSM.h"
#include "Snackoboto.h"
#include "ES_Timers.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    Sweep_Right,
    Sweep_Left,
} SearchingSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "Sweep_Right",
    "Sweep_Left",
};

#define STEP_INTERVAL 12
#define TIME_INTERVAL 150
#define ANGLE_PER_STEP 1.8
#define MAX_YAW 60


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

static SearchingSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static uint8_t YawDisplacement;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitSearchingSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitSearchingSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunSearchingSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunSearchingSubHSM(ES_Event ThisEvent)
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
ES_Event RunSearchingSubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    SearchingSubHSMState_t nextState; // <- change type to correct enum
    
    ES_Tattle(); // trace call stack

    switch (CurrentState) {
    case InitPSubState: // If current state is initial Psedudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state

            // now put the machine into the actual initial state
            nextState = Sweep_Right;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

    case Sweep_Right: // in the first state, replace this with correct names
        //printf("Sweeping Right\r\n");
        if (ThisEvent.EventType == ES_ENTRY){
            //printf("SWEEP_RIGHT_ENTRY\r\n");
            Snacko_SetDirection(RIGHT);
            //ES_Timer_Init();
            ES_Timer_InitTimer(0, TIME_INTERVAL);
            ThisEvent.EventType = ES_NO_EVENT;
        }
        else if (ThisEvent.EventType == ES_TIMEOUT && ThisEvent.EventParam == 0){
            //double yawDisplace = Snacko_GetYawDisplacement();
            //printf("Rotating Right, Currently at %f\r\n", yawDisplace);
            Snacko_RotateRight(STEP_INTERVAL);
            if (Snacko_GetYawDisplacement() >= MAX_YAW){
                //printf("%f is greater than 1.8\r\n", yawDisplace);
                nextState = Sweep_Left;
                makeTransition = TRUE;
            }
            else{
                //ES_Timer_Init();
                ES_Timer_InitTimer(0, TIME_INTERVAL);
            }
            ThisEvent.EventType = ES_NO_EVENT;
        } 
        break;

    case Sweep_Left:
        if (ThisEvent.EventType == ES_ENTRY){
            Snacko_SetDirection(LEFT);
            //ES_Timer_Init();
            ES_Timer_InitTimer(0, TIME_INTERVAL);
            ThisEvent.EventType = ES_NO_EVENT;
        }
        if (ThisEvent.EventType == ES_TIMEOUT && ThisEvent.EventParam == 0){
            //printf("Rotating Left, Currently at %f\r\n", Snacko_GetYawDisplacement());
            Snacko_RotateLeft(STEP_INTERVAL);
            if (Snacko_GetYawDisplacement() <= -MAX_YAW){
                nextState = Sweep_Right;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else{
                //ES_Timer_Init();
                ES_Timer_InitTimer(0, TIME_INTERVAL);
                ThisEvent.EventType = ES_NO_EVENT;
            }
        }
        break;
        
    default: // all unhandled states fall into here
        break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunSearchingSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunSearchingSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

