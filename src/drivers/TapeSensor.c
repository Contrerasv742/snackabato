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
#include "TapeSensor.h"

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/
#define TAPE_SENSOR_PIN AD_PORTV3

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function TapeSensor_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware for Tape Sensor with AD pins */
int TapeSensor_Init(void){
    AD_Init();
    AD_AddPins(TAPE_SENSOR_PIN);
}

/**
 * @Function int TapeSensor_GetReadings(void)
 * @param None
 * @return Unsigned Short corresponding to ADC Readings from Tape Sensor */
unsigned int TapeSensor_GetReading(void){
    while(!AD_IsNewDataReady()){
        ;
    }
    return AD_ReadADPin(TAPE_SENSOR_PIN);
}

