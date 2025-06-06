/*
 * File:   IR_Sensor.h
 * Author: Andy Ly
 * Date: 4 June 2025
 */

#include <xc.h>
#include <BOARD.h>
#include <stdio.h>
#include <AD.h>
#include <IR_Sensor.h>

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/
#define LEFT_IR_PIN AD_PORTV7
#define RIGHT_IR_PIN AD_PORTV8

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
    return SUCCESS;
}

/**
 * @Function int IR_GetReadingR(void)
 * @param None
 * @return Unsigned Short corresponding to ADC Readings from Right IR Sensor */
unsigned int IR_GetReadingR(void){
    int timeout = 10000;
    
    while((!AD_IsNewDataReady()) && 
          (timeout-- > 0)){
        ;
    }
    
    // Error: Timeout
    if (timeout < 0) {
        return 0xFFFF;
    }
    
    return AD_ReadADPin(RIGHT_IR_PIN);
}

/**
 * @Function int IR_GetReadingL(void)
 * @param None
 * @return Unsigned Short corresponding to ADC Readings from Left IR Sensor */
unsigned int IR_GetReadingL(void){
    int timeout = 10000;
    
    while((!AD_IsNewDataReady()) && 
          (timeout-- > 0)){
        ;
    }
    
    // Error: Timeout
    if (timeout < 0) {
        return 0xFFFF;
    }
    
    return AD_ReadADPin(LEFT_IR_PIN);
}
