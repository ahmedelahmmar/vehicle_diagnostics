/*
 * PB.h
 *
 *  Created on: Dec 5, 2024
 *      Author: yusuf
 */
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

#define PB_LEFT_MOTOR_OPEN_PIN              4
#define PB_LEFT_MOTOR_CLOSE_PIN             5
#define PB_RIGHT_MOTOR_OPEN_PIN             6
#define PB_RIGHT_MOTOR_CLOSE_PIN            7


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
