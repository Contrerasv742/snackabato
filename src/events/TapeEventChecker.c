/*
 * File:   TapeEventChecker.c
 * Author: Andy Ly
 *
 */

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

 #include "ES_Configure.h"
 #include "EventChecker.h"
 #include "ES_Events.h"
 #include "Serial.h"
 #include "TapeSensor.h"
 #include "AD.h"
#include "SnackobotoHSM.h"
#include <stdio.h>
 
 /*******************************************************************************
  * MODULE #DEFINES                                                             *
  ******************************************************************************/
 #define HIGH_THRESHOLD 900
 #define LOW_THRESHOLD 700
 
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
 uint8_t CheckTapeReading(void) {
     static ES_EventTyp_t lastEvent = ES_NO_EVENT;
     ES_EventTyp_t curEvent;
     ES_Event thisEvent;
     uint8_t returnVal = FALSE;
     thisEvent.EventType = ES_NO_EVENT;
     unsigned int sensorReading = TapeSensor_GetReading();
     //printf("%d\r\n", sensorReading);
     //thisEvent.EventParam = sensorReading;
     if (sensorReading > HIGH_THRESHOLD) {
         curEvent = TAPE_DETECTED;
     } 
     else if (sensorReading < LOW_THRESHOLD){
         curEvent = TAPE_LOST;
     }
     else{
         return FALSE;
     }
     if (curEvent != lastEvent) { // check for change from last time
         if (curEvent == TAPE_DETECTED){
             printf("Tape Detected Event\r\n");
         }
         else if (curEvent == TAPE_LOST){
             printf("Tape Lost Event\r\n");
         }
         thisEvent.EventType = curEvent;
         returnVal = TRUE;
         lastEvent = curEvent; // update history
         //printf("Here\r\n");
        #ifndef EVENTCHECKER_TEST           // keep this as is for test harness
                PostSnackoHSM(thisEvent); // Change it to your target service's post function
        #else
                SaveEvent(thisEvent);
        #endif   
     }
     return (returnVal);
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
     TapeSensor_Init();
     // Do not alter anything below this line
     int i;
 
     printf("\r\nEvent checking test harness for %s", __FILE__);
     while(1){
         CheckTapeReading();
     }
     /*
     while (1) {
         if (IsTransmitEmpty()) {
             for (i = 0; i< sizeof (EventList) >> 2; i++) {
                 if (EventList[i]() == TRUE) {
                     PrintEvent();
                     break;
                 }
 
             }
         }
     }
      * */
 }
 
 void PrintEvent(void) {
     //printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
             //EventNames[storedEvent.EventType], storedEvent.EventParam);
 }
 #endif
 