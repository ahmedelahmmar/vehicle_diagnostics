/*
 * PB.c
 *
 *  Created on: Dec 5, 2024
 *      Author: yusuf
 */
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
#include "../include/pb.h"
#include "../include/motors.h"

#define GPIO_PORTB_MIS_REG  (*(volatile unsigned long*)0x40005418)

volatile struct
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


void pb_init (void)
{
    SET_BIT(SYSCTL_RCGCGPIO_REG,3); //Enable clock GPIO for port D
    while (!GET_BIT(SYSCTL_PRGPIO_REG, 3));

    GPIO_PORTD_DIR_REG &= 0xF0;
    GPIO_PORTD_DEN_REG |= 0x0F;
    GPIO_PORTD_PDR_REG |= 0x0F;
    GPIO_PORTD_IS_REG  &= 0xF0;
    GPIO_PORTD_IBE_REG |= 0x0F;
    GPIO_PORTD_IM_REG  |= 0x0F;

    SET_BIT(NVIC_EN0_REG, 3);    // interrupt enabled
    NVIC_PRI0_REG &= 0x00FFFFFF;     //set priority to zero

    *(unsigned char*)&sFlags = 0;
}


void pb_eventISR(void)
{
    if (GPIO_PORTB_MIS_REG & PB_LEFT_MOTOR_OPEN_PIN)
    {
        if (GPIO_PORTB_DATA_REG & PB_LEFT_MOTOR_OPEN_PIN) // rising edge
        {
            sFlags.openLeftMotor = 1;
            sFlags.stopLeftMotor = 0;
        }
        else
        {
            sFlags.openLeftMotor = 0;
            sFlags.stopLeftMotor = 1;
        }

        sFlags.closeLeftMotor = 0;

        return;
    }
    else if (GPIO_PORTB_MIS_REG & PB_LEFT_MOTOR_CLOSE_PIN)
    {
        if (GPIO_PORTB_DATA_REG & PB_LEFT_MOTOR_CLOSE_PIN) // rising edge
        {
            sFlags.closeLeftMotor = 1;
            sFlags.stopLeftMotor = 0;
        }
        else
        {
            sFlags.closeLeftMotor = 0;
            sFlags.stopLeftMotor = 1;
        }

        sFlags.openLeftMotor = 0;
            
        return;
    }
    else if (GPIO_PORTB_MIS_REG & PB_RIGHT_MOTOR_OPEN_PIN)
    {
        if (GPIO_PORTB_DATA_REG & PB_RIGHT_MOTOR_OPEN_PIN) // rising edge
        {
            sFlags.openRightMotor = 1;
            sFlags.stopRightMotor = 0;
        }
        else
        {
            sFlags.openRightMotor = 0;
            sFlags.stopRightMotor = 1;
        }

        sFlags.closeRightMotor = 0;
        
        return;   
    }
    else if (GPIO_PORTB_MIS_REG & PB_RIGHT_MOTOR_CLOSE_PIN)
    {
        if (GPIO_PORTB_DATA_REG & PB_RIGHT_MOTOR_CLOSE_PIN) // rising edge
        {
            sFlags.closeRightMotor = 1;
            sFlags.stopRightMotor = 0;
        }
        else
        {   
            sFlags.closeRightMotor = 0;
            sFlags.stopRightMotor = 1;
        }

        sFlags.openRightMotor = 0;

        return;
    }
}
