#include "../include/ultrasonic.h"

void SysTick_Init(void)
{
    SYSTICK_CTRL_REG = 0;
    SYSTICK_CURRENT_REG = 0;
    SYSTICK_RELOAD_REG = 0x00FFFFFF;
    SYSTICK_CTRL_REG |= 0x05;
}

void SysTick_Wait(unsigned long delay)
{
    SYSTICK_RELOAD_REG = delay - 1;      // Set reload value
    SYSTICK_CURRENT_REG = 0;             // Clear current value
    while ((SYSTICK_CTRL_REG & 0x00010000) == 0); // Wait for count flag
}

void SysTick_Wait10us(unsigned long delay)
{
    unsigned long i;  // Declare the loop variable at the top
    for (i = 0; i < delay; i++) {
        SysTick_Wait(160);  // 10us delay at 16 MHz clock
    }
}

void Ultrasonic_Init(void) {
    SET_BIT(SYSCTL_RCGCGPIO_REG, 1);    /* enable clock to PORTB */
    while(GET_BIT(SYSCTL_PRGPIO_REG, 1) == 0);
    
    // ECHO pin at PB3
    gpio_initPin(ECHO_PORT, ECHO_PIN, GPIO_INPUT);

    // TRIGGER pin at PB2
    gpio_initPin(TRIGGER_PORT, TRIGGER_PIN, GPIO_OUTPUT);

    SysTick_Init();
}

uint32_t Ultrasonic_ReadDistance(void) {
    uint32_t duration = 0;
    uint32_t distance = 0;

    // Send trigger pulse
    CLEAR_BIT(GPIO_PORTB_DATA_REG, TRIGGER_PIN); // Set Trigger low
    SysTick_Wait10us(1);                // Wait 10us
    SET_BIT(GPIO_PORTB_DATA_REG, TRIGGER_PIN);  // Set Trigger high
    SysTick_Wait10us(1);                // Wait 10us
    CLEAR_BIT(GPIO_PORTB_DATA_REG, TRIGGER_PIN); // Set Trigger low

    // Wait for Echo signal to go high
    while (GET_BIT(GPIO_PORTB_DATA_REG, ECHO_PIN) == 0);
    // Measure time while Echo signal is high
    while (GET_BIT(GPIO_PORTB_DATA_REG, ECHO_PIN) != 0) {
        duration++;
        SysTick_Wait10us(1);
    }

    distance = (duration * 340.0) / (2 * 1000); // Convert to cm

    return distance;
}
