/*
 * PB.h
 *
 *  Created on: Dec 5, 2024
 *      Author: yusuf
 */
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

// Gpio Port D

#define PB_LEFT_MOTOR_OPEN_PIN              0
#define PB_LEFT_MOTOR_CLOSE_PIN             1
#define PB_RIGHT_MOTOR_OPEN_PIN             2
#define PB_RIGHT_MOTOR_CLOSE_PIN            3


extern volatile struct
{
    unsigned char openLeftMotor       : 1;
    unsigned char closeLeftMotor      : 1;
    unsigned char stopLeftMotor       : 1;
    unsigned char openRightMotor      : 1;
    unsigned char closeRightMotor     : 1;
    unsigned char stopRightMotor      : 1;
    unsigned char isThereAnOpenRequest  : 1;
    unsigned char isThereACloseRequest  : 1;

} sFlags;


void pb_init(void);
