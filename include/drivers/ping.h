#ifndef PINGSENSOR_H
#define	PINGSENSOR_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/



/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function PingSensor_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware for PingSensor with the needed interrupts */
int Ping_Init(void);

/**
 * @Function int PingSensor_GetDistance(void)
 * @param None
 * @return Unsigned Short corresponding to distance in millimeters */
unsigned short Ping_GetDistance(void);


#endif	/* ROTARYENCODER_H */

