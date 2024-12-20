#include "../include/ultrasonic.h"

volatile uint32_t startTime, endTime;
volatile uint8_t edge = 0;

void Delay_MicroSecond(int time) {
    int i;
    SET_BIT(SYSCTL_RCGCTIMER_REG, 1); /* enable clock to Timer Block 1 */
    while(GET_BIT(SYSCTL_PRTIMER_REG, 1) == 0);

    TIMER1_CTL_REG = 0;            /* disable Timer before initialization */
    TIMER1_CFG_REG = 0x04;         /* 16-bit option */ 
    TIMER1_TAMR_REG = 0x02;        /* periodic mode and down-counter */
    TIMER1_TAILR_REG = 16 - 1;     /* TimerA interval load value reg */
    TIMER1_ICR_REG = 0x1;          /* clear the TimerA timeout flag */
    TIMER1_CTL_REG |= 0x01;        /* enable Timer A after initialization */

    for(i = 0; i < time; i++) {
        while ((TIMER1_RIS_REG & 0x1) == 0); /* wait for TimerA timeout flag */
        TIMER1_ICR_REG = 0x1;      /* clear the TimerA timeout flag */
    }
}

void Ultrasonic_Init(void) {
    SET_BIT(SYSCTL_RCGCTIMER_REG, 0); /* enable clock to Timer Block 0 */
    while(GET_BIT(SYSCTL_PRTIMER_REG, 0) == 0);

    SET_BIT(SYSCTL_RCGCGPIO_REG, 1);    /* enable clock to PORTB */
    while(GET_BIT(SYSCTL_PRGPIO_REG, 1) == 0);
    
    GPIO_PORTB_DIR_REG &= ~ECHO_PIN;        /* make PB6 an input pin */
    GPIO_PORTB_AMSEL_REG &= ~ECHO_PIN;     /* Disable Analog on PF1 */
    GPIO_PORTB_DEN_REG |= ECHO_PIN;         /* make PB6 as digital pin */
    GPIO_PORTB_AFSEL_REG |= ECHO_PIN;       /* use PB6 alternate function */
    GPIO_PORTB_PCTL_REG &= ~0x0F000000;     /* configure PB6 for T0CCP0 */
    GPIO_PORTB_PCTL_REG |= 0x07000000;
    
    /* PB5 as a digital output signal to provide trigger signal */
    GPIO_PORTB_DIR_REG |= TRIGGER_PIN;      /* set PB5 as a digital output pin */
    GPIO_PORTB_AMSEL_REG &= ~TRIGGER_PIN;     /* Disable Analog on PF1 */
    GPIO_PORTB_DEN_REG |= TRIGGER_PIN;      /* make PB5 as digital pin */
    GPIO_PORTB_AFSEL_REG &= ~TRIGGER_PIN;      /* Disable PB6 alternate function */
    GPIO_PORTB_PCTL_REG  &= 0xFF0FFFFF;   /* Clear PMCx bits for PF1 to use it as GPIO pin */

    TIMER0_CTL_REG &= ~1;          /* disable timer0A during setup */
    TIMER0_CFG_REG = 4;            /* 16-bit timer mode */
    TIMER0_TAMR_REG = 0x17;        /* up-count, edge-time, capture mode */
    TIMER0_CTL_REG |= 0x0C;        /* capture the rising edge */
    TIMER0_CTL_REG |= 1;           /* enable timer0A */

    // Configure interrupt for PB6 (ECHO_PIN)
    GPIO_PORTB_IS_REG &= ~ECHO_PIN;     /* make PB6 edge sensitive */
    GPIO_PORTB_IBE_REG |= ECHO_PIN;     /* both edges trigger */
    GPIO_PORTB_ICR_REG |= ECHO_PIN;     /* clear any prior interrupt */
    GPIO_PORTB_IM_REG |= ECHO_PIN;      /* unmask interrupt */

    NVIC_EN0_REG |= (1 << 1);         /* enable IRQ5 for PORTB */
}

uint32_t Ultrasonic_ReadDistance(void) {
    uint32_t duration;

    GPIO_PORTB_DATA_REG &= ~TRIGGER_PIN;  // Set Trigger pin low
    Delay_MicroSecond(2);
    GPIO_PORTB_DATA_REG |= TRIGGER_PIN;   // Set Trigger pin high
    Delay_MicroSecond(10);
    GPIO_PORTB_DATA_REG &= ~TRIGGER_PIN;  // Set Trigger pin low

    // Wait for both edges to be captured
    while (edge != 0);

    duration = endTime - startTime;
    uint32_t distance = (duration * 10625) / 10000000;  // Calculate distance in cm

    return distance;
}

void GPIO_PortB_Handler(void) {
    if (GPIO_PORTB_RIS_REG & ECHO_PIN) {
        if (edge == 0) {
            startTime = TIMER0_TAV_REG;
            edge = 1;
        } else {
            endTime = TIMER0_TAV_REG;
            edge = 0;
        }
        GPIO_PORTB_ICR_REG |= ECHO_PIN;  // Clear interrupt flag
    }
}
