/*
 * LCD.c
 *
 *  Created on: Dec 5, 2024
 *      Author: yusuf
 */
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"
#include "../include/LCD.h"
#define RS 2
#define RW 3
#define E 4
void LCD_init(void)
{
    SET_BIT(SYSCTL_RCGCGPIO_REG,0); //Enable clock GPIO for port A
    SET_BIT(SYSCTL_RCGCGPIO_REG,2); //Enable clock GPIO for port C
    while (!(GET_BIT(SYSCTL_PRGPIO_REG, 0) && GET_BIT(SYSCTL_PRGPIO_REG, 2) ));

    GPIO_PORTA_DIR_REG |=0x1c; //set PA2-PA4 as output
    GPIO_PORTA_DEN_REG |=0x1c; //Enable PA2-PA4 Digital


    GPIO_PORTC_DIR_REG |= 0xF0;   // Set PC4-PC7 as Output
    GPIO_PORTC_DEN_REG |= 0xF0;   // Enable PC4-PC7 Digital






}
void LCD_command(unsigned char cmd)
{
    CLEAR_BIT(GPIO_PORTA_DATA_REG,RS); //RS=0 to command
    CLEAR_BIT(GPIO_PORTA_DATA_REG,RW); //RW=0 to write

}
void LCD_data(unsigned char data)
{

    SET_BIT(GPIO_PORTA_DATA_REG,RS); //RS=1 to data
    CLEAR_BIT(GPIO_PORTA_DATA_REG,RW); //RW=0 to write

}
void LCD_print(char* str)
{
    while(*str)
    {
        LCD_data(*str);
        str++;
    }
}

