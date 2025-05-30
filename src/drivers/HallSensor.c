/*
 * File:   TapeSensor.c
 * Author: Andy Ly
 *
 * Created on February 23rd, 2025, 5:20 PM
 */

#include <xc.h>
#include <BOARD.h>
#include <stdio.h>
#include <AD.h>
#include <ES_Timers.h>
#include <HallSensor.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/
#define HALL_SENSOR_PIN AD_PORTV5
#define HALL_THRESHOLD 111

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function TapeSensor_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware for Tape Sensor with AD pins */
int HallSensor_Init(void){
    AD_Init();
    AD_AddPins(HALL_SENSOR_PIN);
}

/**
 * @Function int TapeSensor_GetReadings(void)
 * @param None
 * @return Unsigned Short corresponding to ADC Readings from Tape Sensor */
unsigned int HallSensor_GetReading(void){
    while(!AD_IsNewDataReady()){
        ;
    }
    return AD_ReadADPin(HALL_SENSOR_PIN);
}

/**
 * @Function int HallSensor_GetRPM(void)
 * @param None
 * @return Unsigned int corresponding to Calculated RPM of wheel */
unsigned int HallSensor_GetRPM(void){
    static unsigned int RPM;
    static int prevDetect = FALSE;
    static uint32_t previousTime;
    uint32_t currentTime = ES_Timer_GetTime();
    unsigned int hallReading = HallSensor_GetReading();
    if (hallReading <= HALL_THRESHOLD && prevDetect == FALSE){
        RPM = (60000) / (currentTime - previousTime);
        previousTime = currentTime;
        prevDetect = TRUE;
    }
    else if (hallReading > HALL_THRESHOLD && prevDetect == TRUE){
        prevDetect = FALSE;
    }
    return RPM;
}

