#include "../include/motors.h"


void motors_init(void)
{
    SET_BIT(SYSCTL_RCGCGPIO_REG, 1);
    while (!GET_BIT(SYSCTL_PRGPIO_REG, 1));

    GPIO_PORTB_AMSEL_REG &= 0x0F;
    GPIO_PORTB_PCTL_REG  &= 0x0000FFFF;
    GPIO_PORTB_DIR_REG   |= 0xF0;
    GPIO_PORTB_AFSEL_REG &= 0xF0;
    GPIO_PORTB_DEN_REG   |= 0xF0;
    GPIO_PORTB_DATA_REG  &= 0x0F;
}


void motors_start(eMotor_t motor_id, eDir_t direction)
{
    switch (motor_id)
    {
        case LEFT_MOTOR:

            switch (direction)
            {
                case DIR_CW:
                    SET_BIT(GPIO_PORTB_DATA_REG, LEFT_MOTOR_IN1_PIN);
                    CLEAR_BIT(GPIO_PORTB_DATA_REG, LEFT_MOTOR_IN2_PIN);
                    break;

                case DIR_CCW:
                    CLEAR_BIT(GPIO_PORTB_DATA_REG, LEFT_MOTOR_IN1_PIN);
                    SET_BIT(GPIO_PORTB_DATA_REG, LEFT_MOTOR_IN2_PIN);
                    break;

                default: break;
            }
            break;

        case RIGHT_MOTOR:

            switch (direction)
            {
                case DIR_CW:
                    CLEAR_BIT(GPIO_PORTB_DATA_REG, RIGHT_MOTOR_IN1_PIN);
                    SET_BIT(GPIO_PORTB_DATA_REG, RIGHT_MOTOR_IN2_PIN);
                    break;

                case DIR_CCW:
                    SET_BIT(GPIO_PORTB_DATA_REG, RIGHT_MOTOR_IN1_PIN);
                    CLEAR_BIT(GPIO_PORTB_DATA_REG, RIGHT_MOTOR_IN2_PIN);
                    break;

                default: break;
            }
            break;

        default: break;
    }
}


void motors_stop(eMotor_t motor_id)
{
    switch (motor_id)
    {
        case LEFT_MOTOR:
            CLEAR_BIT(GPIO_PORTB_DATA_REG, LEFT_MOTOR_IN1_PIN);
            CLEAR_BIT(GPIO_PORTB_DATA_REG, LEFT_MOTOR_IN2_PIN);
            break;

        case RIGHT_MOTOR:
            CLEAR_BIT(GPIO_PORTB_DATA_REG, RIGHT_MOTOR_IN1_PIN);
            CLEAR_BIT(GPIO_PORTB_DATA_REG, RIGHT_MOTOR_IN2_PIN);
            break;
    
        default:
            break;
    }
}
