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
#include "HallSensor.h"

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/
#define HALL_SENSOR_PIN AD_PORTV4

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

