#include "./include/app.h"
#define DTC_ACCIDENT_MIGHT_HAPPENED "P001 - ACCIDENT"
#define DTC_ENGINE_HIGH_TEMPERATURE "P002 - HIGH TEMP"
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

int temp;
int dist;

int main(void)
{

    pb_init();

    adc0_init();
    Ultrasonic_Init();

    while(1)
    {
        handleMotors();
        temp = adc0_temp();
        lcd_set_cursor(0,2);
        lcd_write_int(temp);

        dist = Ultrasonic_ReadDistance();
        lcd_set_cursor(1,2);
        lcd_write_int(dist);
    
        delay_ms(1000);
    }
}
