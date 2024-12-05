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

extern volatile unsigned char openLeftMotor;       
extern volatile unsigned char closeLeftMotor;    
extern volatile unsigned char stopLeftMotor;
extern volatile unsigned char openRightMotor;      
extern volatile unsigned char closeRightMotor;     
extern volatile unsigned char stopRightMotor;      
extern volatile unsigned char isThereAnOpenRequest;
extern volatile unsigned char isThereACloseRequest;  


void pb_init(void);
