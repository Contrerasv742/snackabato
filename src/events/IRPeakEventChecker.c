/*
 * File:   TemplateEventChecker.c
 * Author: Gabriel Hugh Elkaim
 *
 * Template file to set up typical EventCheckers for the  Events and Services
 * Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the
 * names will have to be changed to match your code.
 *
 * This EventCheckers file will work with both FSM's and HSM's.
 *
 * Remember that EventCheckers should only return TRUE when an event has occured,
 * and that the event is a TRANSITION between two detectable differences. They
 * should also be atomic and run as fast as possible for good results.
 *
 * This file includes a test harness that will run the event detectors listed in the
 * ES_Configure file in the project, and will conditionally compile main if the macro
 * EVENTCHECKER_TEST is defined (either in the project or in the file). This will allow
 * you to check you event detectors in their own project, and then leave them untouched
 * for your project unless you need to alter their post functions.
 *
 * Created on September 27, 2013, 8:37 AM
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

 #include <ES_Configure.h>
 #include <EventChecker.h>
 #include <ES_Events.h>
 #include <serial.h>
 #include <IR_Sensor.h>
 #include <AD.h>
#include <IO_Ports.h>
#include <SnackobotoHSM.h>
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define IR_THRESHOLD 30
#define DEBOUNCE_THRESHOLD 4

/*******************************************************************************
 * EVENTCHECKER_TEST SPECIFIC CODE                                                             *
 ******************************************************************************/

//#define EVENTCHECKER_TEST
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
#define SaveEvent(x) do {eventName=__func__; storedEvent=x;} while (0)

static const char *eventName;
static ES_Event storedEvent;
#endif

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this EventChecker. They should be functions
   relevant to the behavior of this particular event checker */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

/* Any private module level variable that you might need for keeping track of
   events would be placed here. Private variables should be STATIC so that they
   are limited in scope to this module. */

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function TemplateCheckBattery(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is a prototype event checker that checks the battery voltage
 *        against a fixed threshold (#defined in the .c file). Note that you need to
 *        keep track of previous history, and that the actual battery voltage is checked
 *        only once at the beginning of the function. The function will post an event
 *        of either BATTERY_CONNECTED or BATTERY_DISCONNECTED if the power switch is turned
 *        on or off with the USB cord plugged into the Uno32. Returns TRUE if there was an 
 *        event, FALSE otherwise.
 * @note Use this code as a template for your other event checkers, and modify as necessary.
 * @author Gabriel H Elkaim, 2013.09.27 09:18
 * @modified Gabriel H Elkaim/Max Dunne, 2016.09.12 20:08 */
uint8_t CheckIRPeak(void) {
#define IR_DETECTORS
#ifdef IR_DETECTORS
    //static unsigned int previousReadingR = 0;       // debounced state
    //static unsigned int previousReadingL = 0;
    static uint8_t debounceCounterR = 0;   // debounce counters per bumper
    static uint8_t debounceCounterL = 0;
    static uint8_t peakedR = FALSE;
    static uint8_t peakedL = FALSE;
    unsigned int rawReadingR = IR_GetReadingR();
    unsigned int rawReadingL = IR_GetReadingL();
    uint8_t returnVal = FALSE;
    //printf("IR_READING_R: %d, IR_READING_L: %d\r\n", rawReadingR, rawReadingL);
    
    if (rawReadingR < IR_THRESHOLD){
        debounceCounterR++;
        if (debounceCounterR > DEBOUNCE_THRESHOLD && !peakedR){
            //printf("Peak R Detected\r\n");
            peakedR = TRUE;
            debounceCounterR = 0;
            ES_Event thisEvent;
            thisEvent.EventType = PEAK_R_DETECTED;
            #ifdef EVENTCHECKER_TEST           // keep this as is for test harness
                SaveEvent(thisEvent);
            #else
                PostSnackoHSM(thisEvent); // Change it to your target service's post function
            #endif  
            returnVal = TRUE;
        }
    }
    else{
        peakedR = FALSE;
        debounceCounterR = 0;
    }
    if (rawReadingL < IR_THRESHOLD){
        debounceCounterL++;
        if (debounceCounterL > DEBOUNCE_THRESHOLD && !peakedL){
            //printf("Peak L Detected\r\n");
            peakedL = TRUE;
            debounceCounterL = 0;
            ES_Event thisEvent;
            thisEvent.EventType = PEAK_L_DETECTED;
            #ifdef EVENTCHECKER_TEST           // keep this as is for test harness
                SaveEvent(thisEvent);
            #else
                PostSnackoHSM(thisEvent); // Change it to your target service's post function
            #endif  
            returnVal = TRUE;
        }
    }
    else{
        peakedL = FALSE;
        debounceCounterL = 0;
    }
    return (returnVal);
#endif
    
//#define SWITCH_DETECTORS
#ifdef SWITCH_DETECTORS
#define SWITCH_R_TRIS PORTY07_TRIS
#define SWITCH_L_TRIS PORTY05_TRIS
#define SWITCH_R_BIT PORTY07_BIT
#define SWITCH_L_BIT PORTY05_BIT
#define UP 1
#define DOWN 0
    static uint8_t prevR = UP;
    static uint8_t prevL = UP;
    static uint8_t countR = 0;
    static uint8_t countL = 0;
    SWITCH_R_TRIS = 1;
    SWITCH_L_TRIS = 1;
    uint8_t switchR = SWITCH_R_BIT;
    uint8_t switchL = SWITCH_L_BIT;
    uint8_t returnVal = FALSE;

    if (switchR == prevR) {
        countR = 0;  // no change, reset count
    } else {
        countR++;
        if (countR >= DEBOUNCE_THRESHOLD) {
            countR = 0;
            prevR ^= 1;  // flip the stable bit

            ES_Event thisEvent;
            if (switchR == DOWN) {
                thisEvent.EventType = PEAK_R_DETECTED;
            #ifdef EVENTCHECKER_TEST           // keep this as is for test harness
                SaveEvent(thisEvent);
            #else
                PostSnackoHSM(thisEvent); // Change it to your target service's post function
            #endif  
            returnVal = TRUE;
            }
        }
    }

    if (switchL == prevL) {
        countL = 0;  // no change, reset count
    } else {
        countL++;
        if (countL >= DEBOUNCE_THRESHOLD) {
            countL = 0;
            prevL ^= 1;  // flip the stable bit

            ES_Event thisEvent;
            if (switchL == DOWN) {
                thisEvent.EventType = PEAK_L_DETECTED;
            #ifdef EVENTCHECKER_TEST           // keep this as is for test harness
                SaveEvent(thisEvent);
            #else
                PostSnackoHSM(thisEvent); // Change it to your target service's post function
            #endif  
            returnVal = TRUE;
            }
        }
    }
#endif
}

/* 
 * The Test Harness for the event checkers is conditionally compiled using
 * the EVENTCHECKER_TEST macro (defined either in the file or at the project level).
 * No other main() can exist within the project.
 * 
 * It requires a valid ES_Configure.h file in the project with the correct events in 
 * the enum, and the correct list of event checkers in the EVENT_CHECK_LIST.
 * 
 * The test harness will run each of your event detectors identically to the way the
 * ES_Framework will call them, and if an event is detected it will print out the function
 * name, event, and event parameter. Use this to test your event checking code and
 * ensure that it is fully functional.
 * 
 * If you are locking up the output, most likely you are generating too many events.
 * Remember that events are detectable changes, not a state in itself.
 * 
 * Once you have fully tested your event checking code, you can leave it in its own
 * project and point to it from your other projects. If the EVENTCHECKER_TEST marco is
 * defined in the project, no changes are necessary for your event checkers to work
 * with your other projects.
 */
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
static uint8_t(*EventList[])(void) = {EVENT_CHECK_LIST};

void PrintEvent(void);

void main(void) {
    BOARD_Init();
    /* user initialization code goes here */
    IR_Init();
    // Do not alter anything below this line
    int i;

    printf("\r\nEvent checking test harness for %s", __FILE__);

    while (1) {
        CheckIRPeak();
    }
}

void PrintEvent(void) {
    printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
            EventNames[storedEvent.EventType], storedEvent.EventParam);
}
#endif
