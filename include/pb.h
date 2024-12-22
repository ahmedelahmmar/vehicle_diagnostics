/*
 * PB.h
 *
 *  Created on: Dec 5, 2024
 *      Author: yusuf
 */
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
#include "gpio.h"

// Gpio Port D

#define PB_LEFT_MOTOR_OPEN_PIN              GPIO_PIN_0
#define PB_LEFT_MOTOR_OPEN_PORT             GPIOD

#define PB_LEFT_MOTOR_CLOSE_PIN             GPIO_PIN_1
#define PB_LEFT_MOTOR_CLOSE_PORT            GPIOD

#define PB_RIGHT_MOTOR_OPEN_PIN             GPIO_PIN_2
#define PB_RIGHT_MOTOR_OPEN_PORT            GPIOD

#define PB_RIGHT_MOTOR_CLOSE_PIN            GPIO_PIN_3
#define PB_RIGHT_MOTOR_CLOSE_PORT           GPIOD

#define PB_FAN_INPUT_PIN                    GPIO_PIN_7
#define PB_FAN_INPUT_PORT                   GPIOB

#define PB_FAN_OUTPUT_PIN                   GPIO_PIN_6
#define PB_FAN_OUTPUT_PORT                  GPIOB

extern volatile unsigned char openLeftMotor;       
extern volatile unsigned char closeLeftMotor;    
extern volatile unsigned char stopLeftMotor;
extern volatile unsigned char openRightMotor;      
extern volatile unsigned char closeRightMotor;     
extern volatile unsigned char stopRightMotor;      
extern volatile unsigned char isThereAnOpenRequest;
extern volatile unsigned char isThereACloseRequest;  


void pb_init(void);