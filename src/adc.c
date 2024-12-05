#include "../include/adc.h"
#include "adc.h"

void adc0_init(void)
{
    SET_BIT(SYSCTL_RCGCGPIO_REG, 3); /* Enable Clock to GPIOE (PE3) */
    while (!GET_BIT(SYSCTL_PRGPIO_REG, 3));

    SET_BIT(SYSCTL_RCGCADC_REG, 0); /* Enable Clock to ADC0 */
    while (!GET_BIT(SYSCTL_PRADC_REG, 0));

    GPIO_PORTE_AFSEL_REG |= (1<<3);         /* enable alternate function */
    GPIO_PORTE_DEN_REG &= ~(1<<3);          /* disable digital function */
    GPIO_PORTE_AMSEL_REG |= (1<<3);         /* enable analog function */

    ADC0_ACTSS_REG &= ~(1<<3);              /* disable SS3 during configuration */
    ADC0_EMUX_REG &= ~(0xF000);             /* software trigger conversion */
    ADC0_SSMUX3_REG = 0;
    ADC0_SSCTL3_REG |= 0x6;
    ADC0_ACTSS_REG |= (1<<3);               /* enable ADC0 SS3 */
}