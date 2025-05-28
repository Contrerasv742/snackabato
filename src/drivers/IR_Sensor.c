/*
 * File:   IR_Sensor.h
 * Author: Andy Ly
 *
 */

#include <xc.h>
#include <BOARD.h>
#include <stdio.h>
#include <AD.h>
#include "IR_Sensor.h"

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/
#define LEFT_IR_PIN AD_PORTV_5
#define RIGHT_IR_PIN AD_PORTV_5

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function IR_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware for  with AD pins */
int IR_Init(void){
    AD_Init();
    AD_AddPins(LEFT_IR_PIN);
    AD_AddPins(RIGHT_IR_PIN);
}

/**
 * @Function int IR_GetReadingR(void)
 * @param None
 * @return Unsigned Short corresponding to ADC Readings from Right IR Sensor */
unsigned int IR_GetReadingR(void){
    while(!AD_IsNewDataReady()){
        ;
    }
    return AD_ReadADPin(RIGHT_IR_PIN);
}

/**
 * @Function int IR_GetReadingL(void)
 * @param None
 * @return Unsigned Short corresponding to ADC Readings from Left IR Sensor */
unsigned int IR_GetReadingL(void){
    while(!AD_IsNewDataReady()){
        ;
    }
    return AD_ReadADPin(LEFT_IR_PIN);
}


