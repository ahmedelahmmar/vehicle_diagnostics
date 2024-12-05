#ifndef __MOTORS_H__
#define __MOTORS_H__


#include  "../tm4c123gh6pm_registers.h"
#include "../common_macros.h"

// Pins below are on gpio port b
#define LEFT_MOTOR_IN1_PIN          4
#define LEFT_MOTOR_IN2_PIN          5
#define RIGHT_MOTOR_IN1_PIN         6
#define RIGHT_MOTOR_IN2_PIN         7


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