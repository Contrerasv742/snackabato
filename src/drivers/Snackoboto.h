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
typedef enum {
     RIGHT,
     LEFT,
} Direction;

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
 * @Function Snacko_RotateLeft(unsigned int steps)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Rotates Snackoboto Left*/
int Snacko_RotateLeft(unsigned int steps);

/**
 * @Function Snacko_RotateRight(unsigned int steps)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Rotates Snackoboto Right*/
int Snacko_RotateRight(unsigned int steps);

/**
 * @Function Snacko_PitchDown(unsigned in steps)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Pithces Snackoboto */
int Snacko_PitchDown(unsigned int steps);

/**
 * @Function Snacko_SetPitch(int angle)
 * APPROXIMATE_ANGLE = ANGLE - (ANGLE % RESOLUTION)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Pithces Snackoboto */
int Snacko_SetPitch(int angle);

/**
 * @Function Snacko_SetFlywheelSpeed(unsigned int speed)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Sets Flywheel Speed of Snackoboto*/
int Snacko_SetFlywheelSpeed(unsigned int speed);

/**
 * @Function Snacko_FireCandy(void)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Rotates Servo to Fire a Single Candy*/
int Snacko_FireCandy(void);

/**
 * @Function Snacko_SetDirection(Direction d)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Sets Status Variable of Sweep Direction*/
void Snacko_SetDirection(Direction d);

/**
 * @Function Snacko_GetDirection(void)
 * @param None
 * @return Direction
 * @brief Gets Status Variable of Sweep Direction*/
Direction Snacko_GetDirection(void);

/**
 * @Function Snacko_SetYawDispalcement(int angle)
 * @param None
 * @return SUCCESS or ERROR
 * @brief Sets Status Variable of Yaw Dispalcement*/
void Snacko_SetYawDisplacement(int angle);

/**
 * @Function Snacko_GetYawDisplacement(void)
 * @param None
 * @return Direction
 * @brief Gets Status Variable of Yaw Displacement*/
int Snacko_GetYawDisplacement(void);

 #endif /* SNACKOBOTO_H */