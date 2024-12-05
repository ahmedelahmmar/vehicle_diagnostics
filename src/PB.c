/*
 * PB.c
 *
 *  Created on: Dec 5, 2024
 *      Author: yusuf
 */
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
#include "../include/PB.h"

void PB_init (void)
{
    SET_BIT(SYSCTL_RCGCGPIO_REG,3); //Enable clock GPIO for port D
    while (!GET_BIT(SYSCTL_PRGPIO_REG, 3));

    CLEAR_BIT(GPIO_PORTD_DIR_REG,0); //set pin 0 as input
    CLEAR_BIT(GPIO_PORTD_DIR_REG,1); //set pin 1 as input
    CLEAR_BIT(GPIO_PORTD_DIR_REG,2); //set pin 2 as input
    CLEAR_BIT(GPIO_PORTD_DIR_REG,3); //set pin 3 as input

    SET_BIT(GPIO_PORTD_DEN_REG,0);  //Pin 0 is Digital Enabled
    SET_BIT(GPIO_PORTD_DEN_REG,1);  //Pin 1 is Digital Enabled
    SET_BIT(GPIO_PORTD_DEN_REG,2);  //Pin 2 is Digital Enabled
    SET_BIT(GPIO_PORTD_DEN_REG,3);  //Pin 3 is Digital Enabled

    SET_BIT(GPIO_PORTD_PDR_REG,0);  //Pin 0 is Pull down Enabled
    SET_BIT(GPIO_PORTD_PDR_REG,1);  //Pin 1 is Pull down Enabled
    SET_BIT(GPIO_PORTD_PDR_REG,2);  //Pin 2 is Pull down Enabled
    SET_BIT(GPIO_PORTD_PDR_REG,3);  //Pin 3 is Pull down Enabled

    CLEAR_BIT(GPIO_PORTD_IS_REG,0); //Pin 0 is edge sensitive
    CLEAR_BIT(GPIO_PORTD_IS_REG,1); //Pin 1 is edge sensitive
    CLEAR_BIT(GPIO_PORTD_IS_REG,2); //Pin 2 is edge sensitive
    CLEAR_BIT(GPIO_PORTD_IS_REG,3); //Pin 3 is edge sensitive

    SET_BIT(GPIO_PORTD_IEV_REG,0); // A rising edge on the corresponding pin0 triggers an interrupt.
    SET_BIT(GPIO_PORTD_IEV_REG,1); // A rising edge on the corresponding pin1 triggers an interrupt.
    SET_BIT(GPIO_PORTD_IEV_REG,2); // A rising edge on the corresponding pin2 triggers an interrupt.
    SET_BIT(GPIO_PORTD_IEV_REG,3); // A rising edge on the corresponding pin3 triggers an interrupt.

    SET_BIT(GPIO_PORTD_IM_REG,0); // The interrupt from the corresponding pin0 is sent to the interrupt controller.
    SET_BIT(GPIO_PORTD_IM_REG,1); // The interrupt from the corresponding pin1 is sent to the interrupt controller.
    SET_BIT(GPIO_PORTD_IM_REG,2); // The interrupt from the corresponding pin2 is sent to the interrupt controller.
    SET_BIT(GPIO_PORTD_IM_REG,3); // The interrupt from the corresponding pin3 is sent to the interrupt controller.

    SET_BIT(NVIC_EN0_REG,3);    // interrupt enabled
    NVIC_PRI0_REG = NVIC_PRI0_REG & 0x00FFFFFF;     //set priority to zero



}


char PB_check(pb_t button_id)
{

}
