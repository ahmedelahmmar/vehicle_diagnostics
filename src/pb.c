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

#define GPIO_PORTD_MIS_REG  (*(volatile unsigned long*)0x40007418)

volatile unsigned char openLeftMotor = 0;       
volatile unsigned char closeLeftMotor = 0;    
volatile unsigned char stopLeftMotor = 0;
volatile unsigned char openRightMotor = 0;      
volatile unsigned char closeRightMotor = 0;     
volatile unsigned char stopRightMotor = 0;      
volatile unsigned char isThereAnOpenRequest = 0;
volatile unsigned char isThereACloseRequest = 0;  


void pb_init (void)
{
    SET_BIT(SYSCTL_RCGCGPIO_REG, 3); //Enable clock GPIO for port D
    while (!GET_BIT(SYSCTL_PRGPIO_REG, 3));

    GPIO_PORTD_DIR_REG &= 0xF0;
    GPIO_PORTD_DEN_REG |= 0x0F;
    GPIO_PORTD_PDR_REG |= 0x0F;
    GPIO_PORTD_IS_REG  &= 0xF0;
    GPIO_PORTD_IBE_REG |= 0x0F;
    GPIO_PORTD_IM_REG  |= 0x0F;

    SET_BIT(NVIC_EN0_REG, 3);    // interrupt enabled
    NVIC_PRI0_REG &= 0x00FFFFFF;     //set priority to zero

//    gpio_initPin(PB_FAN_INPUT_PORT, PB_FAN_INPUT_PIN, GPIO_INPUT_PULLDOWN);
//    gpio_initPin(PB_FAN_OUTPUT_PORT, PB_FAN_OUTPUT_PIN, GPIO_OUTPUT);
//    gpio_setPinLogic(PB_FAN_OUTPUT_PORT, PB_FAN_OUTPUT_PIN, GPIO_HIGH);
}


void pb_eventISR(void)
{
    if (GET_BIT(GPIO_PORTD_MIS_REG, PB_LEFT_MOTOR_OPEN_PIN))
    {
        if (GET_BIT(GPIO_PORTD_DATA_REG, PB_LEFT_MOTOR_OPEN_PIN)) // rising edge
        {
            openLeftMotor = 1;
            stopLeftMotor = 0;
        }
        else
        {
            openLeftMotor = 0;
            stopLeftMotor = 1;
        }

        closeLeftMotor = 0;

//        SET_BIT(GPIO_PORTD_ICR_REG, PB_LEFT_MOTOR_OPEN_PIN);
//        GPIO_PORTD_ICR_REG |= 0xFF;
//        return;
    }
    if (GET_BIT(GPIO_PORTD_MIS_REG, PB_LEFT_MOTOR_CLOSE_PIN))
    {
        if (GET_BIT(GPIO_PORTD_DATA_REG, PB_LEFT_MOTOR_CLOSE_PIN)) // rising edge
        {
            closeLeftMotor = 1;
            stopLeftMotor = 0;
        }
        else
        {
            closeLeftMotor = 0;
            stopLeftMotor = 1;
        }

        openLeftMotor = 0;

//        SET_BIT(GPIO_PORTD_ICR_REG, PB_LEFT_MOTOR_CLOSE_PIN);
//        GPIO_PORTD_ICR_REG |= 0xFF;
//        return;
    }
    if (GET_BIT(GPIO_PORTD_MIS_REG, PB_RIGHT_MOTOR_OPEN_PIN))
    {
        if (GET_BIT(GPIO_PORTD_DATA_REG, PB_RIGHT_MOTOR_OPEN_PIN)) // rising edge
        {
            openRightMotor = 1;
            stopRightMotor = 0;
        }
        else
        {
            openRightMotor = 0;
            stopRightMotor = 1;
        }

        closeRightMotor = 0;

//        SET_BIT(GPIO_PORTD_ICR_REG, PB_RIGHT_MOTOR_OPEN_PIN);
//        GPIO_PORTD_ICR_REG |= 0xFF;
//        return;
    }
    if (GET_BIT(GPIO_PORTD_MIS_REG, PB_RIGHT_MOTOR_CLOSE_PIN))
    {
        if (GET_BIT(GPIO_PORTD_DATA_REG, PB_RIGHT_MOTOR_CLOSE_PIN)) // rising edge
        {
            closeRightMotor = 1;
            stopRightMotor = 0;
        }
        else
        {   
            closeRightMotor = 0;
            stopRightMotor = 1;
        }

        openRightMotor = 0;

//        SET_BIT(GPIO_PORTD_ICR_REG, PB_RIGHT_MOTOR_CLOSE_PIN);
//        GPIO_PORTD_ICR_REG |= 0xFF;
//        return;
    }
    GPIO_PORTD_ICR_REG |= 0xFF;
}
