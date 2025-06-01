/*
 * File: SnackobotoHSM.c
 * Author: Andy Ly
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

 #include "ES_Configure.h"
 #include "ES_Framework.h"
 #include "BOARD.h"
 #include "SnackobotoHSM.h"
 //#include "CalibrationSubHSM.h"
 #include "SearchingSubHSM.h"
 #include "TargetRSubHSM.h"
 #include "TargetLSubHSM.h"
 #include "ObstacleSubHSM.h"
 #include "EventChecker.h"
 #include "ES_Timers.h"
 #include "Snackoboto.h"
 #include <stdio.h>
 /*******************************************************************************
  * PRIVATE #DEFINES                                                            *
  ******************************************************************************/
 //Include any defines you need to do
 
 /*******************************************************************************
  * MODULE #DEFINES                                                             *
  ******************************************************************************/
#define DELAY(x)    for (unsigned int wait = 0; wait <= x; wait++) {asm("nop");}
#define A_BIT       18300
#define A_BIT_MORE  36600
#define YET_A_BIT_LONGER (A_BIT_MORE<<2)
#define A_LOT       183000
#define NUM_TIMES_REPEAT_LED 5
#define MOTOR_TIME (A_LOT<<2)
 
 typedef enum {
     InitPState,
     Calibration,
     Searching,
     TargetR,
     TargetL,
     Obstacle,
 } SnackoHSMState_t; // <- For Tattletale, keep the "State_t" on the end of the enum type name.
 
 static const char *StateNames[] = {
     "InitPState",
     "Calibration",
     "Searching",
     "TargetR",
     "TargetL",
     "Obstacle",
 };

 #define STEP_INTERVAL 4
 #define TIME_INTERVAL 1000
 #define STARTING_PITCH 0
 
 
 /*******************************************************************************
  * PRIVATE FUNCTION PROTOTYPES                                                 *
  ******************************************************************************/
 /* Prototypes for private functions for this machine. They should be functions
    relevant to the behavior of this state machine
    Example: char RunAway(uint_8 seconds);*/
 /*******************************************************************************
  * PRIVATE MODULE VARIABLES                                                            *
  ******************************************************************************/
 /* You will need MyPriority and the state variable; you may need others as well.
  * The type of state variable should match that of enum in header file. */
 
 static SnackoHSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
 static uint8_t MyPriority;
 
 
 /*******************************************************************************
  * PUBLIC FUNCTIONS                                                            *
  ******************************************************************************/
 
 /**
  * @Function InitSnackoHSM(uint8_t Priority)
  * @param Priority - internal variable to track which event queue to use
  * @return TRUE or FALSE
  * @brief This will get called by the framework at the beginning of the code
  *        execution. It will post an ES_INIT event to the appropriate event
  *        queue, which will be handled inside RunTemplateFSM function. Remember
  *        to rename this to something appropriate.
  *        Returns TRUE if successful, FALSE otherwise
  * @author J. Edward Carryer, 2011.10.23 19:25 */
 uint8_t InitSnackoHSM(uint8_t Priority)
 {
     MyPriority = Priority;
     // put us into the Initial PseudoState
     CurrentState = InitPState;
     // post the initial transition event
     if (ES_PostToService(MyPriority, INIT_EVENT) == TRUE) {
         return TRUE;
     } else {
         return FALSE;
     }
 }
 
 /**
  * @Function PostSnackoHSM(ES_Event ThisEvent)
  * @param ThisEvent - the event (type and param) to be posted to queue
  * @return TRUE or FALSE
  * @brief This function is a wrapper to the queue posting function, and its name
  *        will be used inside ES_Configure to point to which queue events should
  *        be posted to. Remember to rename to something appropriate.
  *        Returns TRUE if successful, FALSE otherwise
  * @author J. Edward Carryer, 2011.10.23 19:25 */
 uint8_t PostSnackoHSM(ES_Event ThisEvent)
 {
     return ES_PostToService(MyPriority, ThisEvent);
 }
 
 /**
  * @Function RunSnackoHSM(ES_Event ThisEvent)
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
 ES_Event RunSnackoHSM(ES_Event ThisEvent)
 {
     uint8_t makeTransition = FALSE; // use to flag transition
     SnackoHSMState_t nextState; // <- need to change enum type here
     
     ES_Tattle(); // trace call stack
 
     switch (CurrentState) {
     case InitPState: // If current state is initial Pseudo State
         if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
         {
             // this is where you would put any actions associated with the
             // transition from the initial pseudo-state into the actual
             // initial state
 
             // now put the machine into the actual initial state
             nextState = Calibration;
             makeTransition = TRUE;
             ThisEvent.EventType = ES_NO_EVENT;
             DELAY(MOTOR_TIME);
         }
         break;
     
     case Calibration:
         //ThisEvent = RunCalibrationSubHSM(ThisEvent);
         if (ThisEvent.EventType == ES_ENTRY){
             ES_Timer_Init();
             ES_Timer_InitTimer(6, TIME_INTERVAL);
             ThisEvent.EventType = ES_NO_EVENT;
         }
         if (ThisEvent.EventType == ES_TIMEOUT && ThisEvent.EventParam == 6){
            Snacko_PitchDown(STEP_INTERVAL);
            DELAY(MOTOR_TIME);
            //printf("New Pitch: %f\r\n",Snacko_GetPitchDisplacement());
            ES_Timer_Init();
            ES_Timer_InitTimer(6, TIME_INTERVAL);
            ThisEvent.EventType = ES_NO_EVENT;
         }
         if (ThisEvent.EventType == TAPE_DETECTED){
             //Pitch Up + Reset Pitch?
             Snacko_SetPitchDisplacement(STARTING_PITCH);
             InitSearchingSubHSM();
             nextState = Searching;
             makeTransition = TRUE;
             ThisEvent.EventType = ES_NO_EVENT;
         }
         /*
         if (ThisEvent.EventType == CALIBRATED)
         {
             nextState = Searching;
             makeTransition = TRUE;
             ThisEvent.EventType = ES_NO_EVENT;
         }
         */
         break;
 
     case Searching:
         ThisEvent = RunSearchingSubHSM(ThisEvent);
         if (ThisEvent.EventType == ES_ENTRY){
             //printf("Searching\r\n");
             ThisEvent.EventType = ES_NO_EVENT;
         }
         if (ThisEvent.EventType == PEAK_R_DETECTED){
             //printf("R Peak Detected at %f\r\n", Snacko_GetYawDisplacement());
             InitTargetRSubHSM();
             nextState = TargetR;
             makeTransition = TRUE;
             ThisEvent.EventType = ES_NO_EVENT;
         }
         if (ThisEvent.EventType == PEAK_L_DETECTED){
             //printf("L Peak Detected at %f\r\n", Snacko_GetYawDisplacement());
             InitTargetLSubHSM();
             nextState = TargetL;
             makeTransition = TRUE;
             ThisEvent.EventType = ES_NO_EVENT;
         }
         if (ThisEvent.EventType == OBSTACLE_DETECTED){
             InitObstacleSubHSM();
             nextState = Obstacle;
             makeTransition = TRUE;
             ThisEvent.EventType = ES_NO_EVENT;
         }
         break;
     
     case TargetR:
         ThisEvent = RunTargetRSubHSM(ThisEvent);
         if (ThisEvent.EventType == ES_ENTRY){

             ThisEvent.EventType = ES_NO_EVENT;
         }
         if (ThisEvent.EventType == CANDY_FIRED){
             //InitSearchingSubHSM();
             nextState = Searching;
             makeTransition = TRUE;
             ThisEvent.EventType = ES_NO_EVENT;
         }
         break;

     case TargetL:
         ThisEvent = RunTargetLSubHSM(ThisEvent);
         if (ThisEvent.EventType == ES_ENTRY){

             ThisEvent.EventType = ES_NO_EVENT;
         }
         if (ThisEvent.EventType == CANDY_FIRED){
             //InitSearchingSubHSM();
             nextState = Searching;
             makeTransition = TRUE;
             ThisEvent.EventType = ES_NO_EVENT;
         }
         break;
     
     case Obstacle:
         ThisEvent = RunObstacleSubHSM(ThisEvent);
         if (ThisEvent.EventType == ES_ENTRY){

             ThisEvent.EventType = ES_NO_EVENT;
         }
         if (ThisEvent.EventType == CANDY_FIRED){
             //InitSearchingSubHSM();
             nextState = Searching;
             makeTransition = TRUE;
             ThisEvent.EventType = ES_NO_EVENT;
         }
         break;
     default: // all unhandled states fall into here
         break;
     } // end switch on Current State
     if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
         // recursively call the current state with an exit event
         RunSnackoHSM(EXIT_EVENT);
         CurrentState = nextState;
         RunSnackoHSM(ENTRY_EVENT);
     }
     ES_Tail(); // trace call stack end
     return ThisEvent;
     
 }
 
 
 /*******************************************************************************
  * PRIVATE FUNCTIONS                                                           *
  ******************************************************************************/
 
 