/*
 * File:   HallSensor.h
 * Author: Andy Ly
 *
 * Created on February 23rd, 2025, 5:39 PM
 */

#ifndef HALLSENSOR_H
#define	HALLSENSOR_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function HallSensor_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware for Hall Sensor with AD pins */
int HallSensor_Init(void);

/**
 * @Function int HallSensor_GetReadings(void)
 * @param None
 * @return Unsigned Short corresponding to ADC Readings from Hall Sensor */
unsigned int HallSensor_GetReading(void);


#endif	/* HALLSENSOR_H */

