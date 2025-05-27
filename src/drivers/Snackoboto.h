/*
 * File:   Snackoboto.h
 * Author: Andy Ly
 *
 */

 #ifndef SNACKOBOTO_H
 #define SNACKOBOTO_H

/*******************************************************************************
 * PUBLIC #DEFINES                                                            *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

 /**
 * @Function Snacko_Init(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief initializes hardware for Snackoboto */
int Snacko_Init(void);

/**
 * @Function Snacko_RotateLeft(unsigned int speed)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Rotates Snackoboto Left*/
int Snacko_RotateLeft(unsigned int speed);

/**
 * @Function Snacko_RotateRight(unsigned int speed)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Rotates Snackoboto Right*/
int Snacko_RotateRight(unsigned int speed);

/**
 * @Function Snacko_PitchUp(unsigned int angle)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Pithces Snackoboto Up*/
int Snacko_PitchUp(unsigned int angle);

/**
 * @Function Snacko_PitchUp(unsigned int angle)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Pithces Snackoboto Up*/
int Snacko_PitchDown(unsigned int angle);
 #endif /* SNACKOBOTO_H */