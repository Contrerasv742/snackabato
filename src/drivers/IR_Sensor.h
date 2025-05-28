/*
 * File:   IR_Sensor.h
 * Author: Andy Ly
 *
 */

#ifndef IR_SENSOR_H
#define	IR_SENSOR_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function IR_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware for Hall Sensor with AD pins */
int IR_Init(void);

/**
 * @Function int IR_GetReadingR(void)
 * @param None
 * @return Unsigned Short corresponding to ADC Readings from Hall Sensor */
unsigned int IR_GetReadingR(void);

/**
 * @Function int IR_GetReadingL(void)
 * @param None
 * @return Unsigned Short corresponding to ADC Readings from Hall Sensor */
unsigned int IR_GetReadingL(void);

#endif	/* IR_SENSOR_H */

