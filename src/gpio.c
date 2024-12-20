#include "../include/gpio.h"
  
static volatile unsigned long * const DEN[6]   = {&GPIO_PORTA_DEN_REG,
                                                  &GPIO_PORTB_DEN_REG,
                                                  &GPIO_PORTC_DEN_REG,
                                                  &GPIO_PORTD_DEN_REG,
                                                  &GPIO_PORTE_DEN_REG,
                                                  &GPIO_PORTF_DEN_REG};

static volatile unsigned long * const AMSEL[6] = {&GPIO_PORTA_AMSEL_REG,
                                                  &GPIO_PORTB_AMSEL_REG,
                                                  &GPIO_PORTC_AMSEL_REG,
                                                  &GPIO_PORTD_AMSEL_REG,
                                                  &GPIO_PORTE_AMSEL_REG,
                                                  &GPIO_PORTF_AMSEL_REG};

static volatile unsigned long * const AFSEL[6] = {&GPIO_PORTA_AFSEL_REG,
                                                  &GPIO_PORTB_AFSEL_REG,
                                                  &GPIO_PORTC_AFSEL_REG,
                                                  &GPIO_PORTD_AFSEL_REG,
                                                  &GPIO_PORTE_AFSEL_REG,
                                                  &GPIO_PORTF_AFSEL_REG};

static volatile unsigned long * const PCTL[6]  = {&GPIO_PORTA_PCTL_REG,
                                                  &GPIO_PORTB_PCTL_REG,
                                                  &GPIO_PORTC_PCTL_REG,
                                                  &GPIO_PORTD_PCTL_REG,
                                                  &GPIO_PORTE_PCTL_REG,
                                                  &GPIO_PORTF_PCTL_REG};


static volatile unsigned long * const DIR[6]   = {&GPIO_PORTA_DIR_REG,
                                                  &GPIO_PORTB_DIR_REG,
                                                  &GPIO_PORTC_DIR_REG,
                                                  &GPIO_PORTD_DIR_REG,
                                                  &GPIO_PORTE_DIR_REG,
                                                  &GPIO_PORTF_DIR_REG};

static volatile unsigned long * const PUR[6]   = {&GPIO_PORTA_PUR_REG,
                                                  &GPIO_PORTB_PUR_REG,
                                                  &GPIO_PORTC_PUR_REG,
                                                  &GPIO_PORTD_PUR_REG,
                                                  &GPIO_PORTE_PUR_REG,
                                                  &GPIO_PORTF_PUR_REG};

static volatile unsigned long * const PDR[6]   = {&GPIO_PORTA_PDR_REG,
                                                  &GPIO_PORTB_PDR_REG,
                                                  &GPIO_PORTC_PDR_REG,
                                                  &GPIO_PORTD_PDR_REG,
                                                  &GPIO_PORTE_PDR_REG,
                                                  &GPIO_PORTF_PDR_REG};


static volatile unsigned long * const DATA[6]  = {&GPIO_PORTA_DATA_REG,
                                                  &GPIO_PORTB_DATA_REG,
                                                  &GPIO_PORTC_DATA_REG,
                                                  &GPIO_PORTD_DATA_REG,
                                                  &GPIO_PORTE_DATA_REG,
                                                  &GPIO_PORTF_DATA_REG};


void gpio_initPin(GPIO_Port_t port, GPIO_Pin_t pin, GPIO_Direction_t direction)
{
    SYSCTL_RCGCGPIO_REG |= (1 << port);
    while (!((SYSCTL_PRGPIO_REG >> port) & 1));

    SET_BIT(*DEN[port], pin);
    CLEAR_BIT(*AMSEL[port], pin);
    CLEAR_BIT(*AFSEL[port], pin);
    CLEAR_BIT(*PCTL[port], pin);

    switch (direction)
    {
        case GPIO_INPUT:
            CLEAR_BIT(*DIR[port], pin);
            break;
        
        case GPIO_OUTPUT:
            SET_BIT(*DIR[port], pin);
            break;

        default:    
            (direction == GPIO_INPUT_PULLUP) ? SET_BIT(*PUR[port], pin) : SET_BIT(*PDR[port], pin);
            break;
    }
}


void gpio_setPinLogic(GPIO_Port_t port, GPIO_Pin_t pin, GPIO_Logic_t logic)
{
    switch (logic)
    {
        case GPIO_HIGH:
            SET_BIT(*DATA[port], pin);
            break;

        case GPIO_LOW:
            CLEAR_BIT(*DATA[port], pin);
            break;
        
        default:
            break;
    }
}


unsigned char gpio_getPinLogic(GPIO_Port_t port, GPIO_Pin_t pin)
{
    return GET_BIT(*DATA[port], pin);
}
