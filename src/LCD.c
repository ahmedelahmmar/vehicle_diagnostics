/*
 * LCD.c
 *
 *  Created on: Dec 5, 2024
 *      Author: yusuf
 ** Pin Connections for LCD with Tiva C (Port C and Port D) in 4-bit mode:
 * ------------------------------------------------------------
 * Tiva C Pin    |   LCD Pin    |   Description
 * -----------------------------------------------
 * PD0           |   RS         |   Register Select (1 = Data, 0 = Command)
 * PD1           |   RW         |   Read/Write (0 = Write, 1 = Read)
 * PD2           |   EN         |   Enable (Pulse High to Low to latch data)
 * PC4           |   D4         |   Data bit 4
 * PC5           |   D5         |   Data bit 5
 * PC6           |   D6         |   Data bit 6
 * PC7           |   D7         |   Data bit 7
 * GND           |   VSS        |   Ground
 * 5V            |   VDD        |   Power Supply (5V)
 * POT           |   V0         |   Contrast Adjustment (connect to potentiometer)*/

#include "../include/LCD.h"

#define NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND 364


// Define control pins for the LCD (change as needed)
#define RS 0x01 // PC0
#define RW 0x02 // PC1
#define EN 0x04 // PC2

// Define data pins (PC4 - PC7 for 4-bit mode)
#define DATA_MASK 0xF0

void Delay_MS(unsigned long long n)
{
    volatile unsigned long long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}

void LCD_command(unsigned char command)
{
    GPIO_PORTC_DATA_REG = (GPIO_PORTC_DATA_REG & ~DATA_MASK) | (command & 0xF0); // Send high nibble
    GPIO_PORTD_DATA_REG &= ~RS; // RS = 0 for command
    GPIO_PORTD_DATA_REG &= ~RW; // RW = 0 for write
    GPIO_PORTD_DATA_REG |= EN; // Enable pulse
    Delay_MicroSecond(1);
    GPIO_PORTD_DATA_REG &= ~EN;
    GPIO_PORTC_DATA_REG = (GPIO_PORTC_DATA_REG & ~DATA_MASK) | ((command << 4) & 0xF0); // Send low nibble
    GPIO_PORTD_DATA_REG |= EN; // Enable pulse
    Delay_MicroSecond(1);
    GPIO_PORTD_DATA_REG &= ~EN;

}
void LCD_init(void)
{

    SET_BIT(SYSCTL_RCGCGPIO_REG, 2); //Enable clock GPIO for port C
    while (!GET_BIT(SYSCTL_PRGPIO_REG, 2));

    SET_BIT(SYSCTL_RCGCGPIO_REG, 3); //Enable clock GPIO for port D
    while (!GET_BIT(SYSCTL_PRGPIO_REG, 3));

    GPIO_PORTC_DIR_REG |= 0xF0; // Set PC4-PC7 as output
    GPIO_PORTC_DEN_REG |= 0xF0; // Enable digital function for PC4-PC7

    GPIO_PORTD_DIR_REG |= 0x07; // Set PD0-PD2 as output (RS, RW, EN)
    GPIO_PORTD_DEN_REG |= 0x07; // Enable digital function for PD0-PD2

    Delay_MS(20);   // Wait for power-up

    LCD_command(0x30); // Wake-up
    Delay_MS(5);
    LCD_command(0x30); // Wake-up
    Delay_MicroSecond(100);
    LCD_command(0x30); // Wake-up

    LCD_command(0x20); // 4-bit mode
    LCD_command(0x28); // 2-line, 5x8 font
    LCD_command(0x06); // Auto-increment cursor
    LCD_command(0x0F); // Display on, cursor blinking
    LCD_command(0x01); // Clear display
}

void LCD_data(unsigned char data)
{
    GPIO_PORTC_DATA_REG = (GPIO_PORTC_DATA_REG & ~DATA_MASK) | (data & 0xF0); // Send high nibble
    GPIO_PORTD_DATA_REG |= RS; // RS = 1 for data
    GPIO_PORTD_DATA_REG &= ~RW; // RW = 0 for write
    GPIO_PORTD_DATA_REG |= EN; // Enable pulse
    Delay_MicroSecond(1);
    GPIO_PORTD_DATA_REG &= ~EN;

    GPIO_PORTC_DATA_REG = (GPIO_PORTC_DATA_REG & ~DATA_MASK) | ((data << 4) & 0xF0); // Send low nibble
    GPIO_PORTD_DATA_REG |= EN; // Enable pulse
    Delay_MicroSecond(1);
    GPIO_PORTD_DATA_REG &= ~EN;

    Delay_MicroSecond(40);
}

void LCD_print(char *string)
{
    while (*string)
    {
        LCD_data(*string++);
    }

}
