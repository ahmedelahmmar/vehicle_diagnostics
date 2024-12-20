#include "../include/adc.h"

void adc0_init(void)
{
    SET_BIT(SYSCTL_RCGCGPIO_REG, 4); /* Enable Clock to GPIOE (PE3) */
    while (!GET_BIT(SYSCTL_PRGPIO_REG, 4));

    SET_BIT(SYSCTL_RCGCADC_REG, 0); /* Enable Clock to ADC0 */
    while (!GET_BIT(SYSCTL_PRADC_REG, 0));

    GPIO_PORTE_AFSEL_REG |= (1<<3);         /* enable alternate function */
    GPIO_PORTE_DEN_REG &= ~(1<<3);          /* disable digital function */
    GPIO_PORTE_AMSEL_REG |= (1<<3);         /* enable analog function */

    /* initialize sample sequencer3 */
    ADC0_ACTSS_REG &= ~(1<<3);              /* disable SS3 during configuration */
    ADC0_EMUX_REG &= ~(0xF000);             /* software trigger conversion */
    ADC0_SSMUX3_REG = 0;
    ADC0_SSCTL3_REG |= 0x6;
    ADC0_ACTSS_REG |= (1<<3);               /* Re-enable ADC0 SS3 */
}

int adc0_temp(void)
{
    ADC0_PSSI_REG |= (1<<3);                /* Begin sampling on Sample Sequencer 3 */
    while(!GET_BIT(ADC0_RIS_REG, 3));       /* wait for conversion to complete */
    int temprature = ((ADC0_SSFIFO3_REG * 330) / 4096);
    ADC0_ISC_REG |= (1<<3);                 /* clear completion flag  */
    return temprature;
}
