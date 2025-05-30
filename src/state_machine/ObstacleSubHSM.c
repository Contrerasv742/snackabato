/*
 * File: ObstacleSubHSM.c
 * Author: Andy Ly
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "SnackobotoHSM.h"
#include "ObstacleSubHSM.h"
#include "Snackoboto.h"
#include "ES_Timers.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    Obstacle_Aim,
    Obstacle_Fire,
} ObstacleSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "Obstacle_Aim",
    "Obstacle_Fire",
};

#define FLYWHEEL_SPEED 300
#define FIRE_DELAY 1000
#define STEP_INTERVAL 1
#define TIME_INTERVAL 200
#define ANGLE_PER_STEP 1
#define CENTERING_STEPS 5
#define OBSTACLE_PITCH 0


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

static ObstacleSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static uint8_t StepCount;
static int fired;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitObstacleSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitObstacleSubHSM(void)
{
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunObstacleSubHSM(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunObstacleSubHSM(ES_Event ThisEvent)
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
ES_Event RunObstacleSubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    ObstacleSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
    case InitPSubState: // If current state is initial Psedudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state

            // now put the machine into the actual initial state
            nextState = Obstacle_Aim;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

    case Obstacle_Aim: // in the first state, replace this with correct names
        //ThisEvent = RunObstacleAimSubHSM(ThisEvent);
        if (ThisEvent.EventType == ES_ENTRY){
            StepCount = 0;
            printf("Aiming at Obstacle (%f)\r\n", OBSTACLE_PITCH);
            Snacko_SetPitch(OBSTACLE_PITCH);
            ES_Timer_Init();
            ES_Timer_InitTimer(5, TIME_INTERVAL);
        }
        if (ThisEvent.EventType == ES_TIMEOUT && ThisEvent.EventParam == 5){
            StepCount++;
            if (Snacko_GetDirection() == RIGHT){
                Snacko_RotateLeft(STEP_INTERVAL);
                Snacko_SetYawDisplacement(Snacko_GetYawDisplacement() - ANGLE_PER_STEP * STEP_INTERVAL);
            }
            else{
                Snacko_RotateRight(STEP_INTERVAL);
                Snacko_SetYawDisplacement(Snacko_GetYawDisplacement() + ANGLE_PER_STEP * STEP_INTERVAL);
            }
            if (StepCount >= 5){
            nextState = Obstacle_Fire;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            }
            else{
                ES_Timer_Init();
                ES_Timer_InitTimer(5, TIME_INTERVAL);
            }
        }
        break;

    case Obstacle_Fire:
        if (ThisEvent.EventType == ES_ENTRY){
            fired = FALSE;
            Snacko_SetFlywheelSpeed(FLYWHEEL_SPEED);
            ES_Timer_Init();
            ES_Timer_InitTimer(5, FIRE_DELAY);
        }
        if (ThisEvent.EventType == ES_TIMEOUT && ThisEvent.EventParam == 5){
            if (fired == FALSE){
                Snacko_FireCandy();
                fired = TRUE;
                ES_Timer_InitTimer(5, FIRE_DELAY);
            }
            else if (fired == TRUE){
                Snacko_SetFlywheelSpeed(0);
                fired = FALSE;
                ThisEvent.EventType = CANDY_FIRED;
            }
        }
        break;
        
    default: // all unhandled states fall into here
        break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunObstacleSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunObstacleSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

