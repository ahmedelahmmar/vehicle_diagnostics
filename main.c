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

void delayMs(int n)
{
    int32_t i, j;
    for(i = 0 ; i < n; i++)
        for(j = 0; j < 3180; j++)
            {;}  /* do nothing for 1 ms */
}

char temp_str[18];
int temp;

int main(void)
{
    adc0_init();
    uart0_init();
    LCD_init();
    lcd_set_cursor(0, 0);
    lcd_write_string("Hello, World!");

    while(1)
    {
        temp = adc0_temp();
        sprintf(temp_str, "\r\nTemp = %dC", temp);
        uart0_print_str(temp_str);
        delayMs(1000);
    }
}
