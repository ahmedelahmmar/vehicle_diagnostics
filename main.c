#include "./include/app.h"


void SysTick_Init(void)
{
    SYSTICK_CTRL_REG = 0;
    SYSTICK_CURRENT_REG = 0;
    SYSTICK_RELOAD_REG = 7999999;
    SYSTICK_CTRL_REG |= 0x05;
}



void Leds_Init(void)
{
    SET_BIT(SYSCTL_RCGCGPIO_REG, 5);
    while(GET_BIT(SYSCTL_PRGPIO_REG, 5) == 0);

    GPIO_PORTF_AMSEL_REG &= 0xF1;
    GPIO_PORTF_PCTL_REG  &= 0xFFFF000F;
    GPIO_PORTF_DIR_REG   |= 0x0E;
    GPIO_PORTF_AFSEL_REG &= 0xF1;
    GPIO_PORTF_DEN_REG   |= 0x0E;
    GPIO_PORTF_DATA_REG  &= 0xF1;
}

unsigned char recieved;

int main(void)
{
    LCD_init(); // Initialize the LCD


        while(1)
        {
            LCD_print("Hello, World!"); // Display message on the LCD
        }
}
