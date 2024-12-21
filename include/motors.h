#ifndef __MOTORS_H__
#define __MOTORS_H__

#include "gpio.h"
#include  "../tm4c123gh6pm_registers.h"
#include "../common_macros.h"

// Pins below are on gpio port b
#define LEFT_MOTOR_IN1_PORT         GPIOB
#define LEFT_MOTOR_IN2_PORT         GPIOB
#define RIGHT_MOTOR_IN1_PORT        GPIOB
#define RIGHT_MOTOR_IN2_PORT        GPIOB
/****************************************/
#define LEFT_MOTOR_IN1_PIN          GPIO_PIN_4
#define LEFT_MOTOR_IN2_PIN          GPIO_PIN_5
#define RIGHT_MOTOR_IN1_PIN         GPIO_PIN_6
#define RIGHT_MOTOR_IN2_PIN         GPIO_PIN_7


typedef enum 
{
    LEFT_MOTOR=0,
    RIGHT_MOTOR

} eMotor_t;


typedef enum
{
    DIR_CW=0,
    DIR_CCW

} eDir_t;


void motors_init(void);
void motors_start(eMotor_t motor_id, eDir_t direction);
void motors_stop(eMotor_t motor_id);

#endif /* __MOTORS_H__ */
