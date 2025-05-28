/*
 * File:   TapeSensor.h
 * Author: Andy Ly
 *
 * Created on February 23rd, 2025, 5:13 PM
 */

#ifndef TAPESENSOR_H
#define	TAPESENSOR_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function TapeSensor_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware for Tape Sensor with AD pins */
int TapeSensor_Init(void);

/**
 * @Function int TapeSensor_GetReadings(void)
 * @param None
 * @return Unsigned Short corresponding to ADC Readings from Tape Sensor */
unsigned int TapeSensor_GetReading(void);


#endif	/* TAPESENSOR_H */

