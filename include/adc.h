#ifndef __ADC_H__
#define __ADC_H__

#include  "../tm4c123gh6pm_registers.h"
#include "../common_macros.h"
#include "uart0.h"

#define THRESHOLD_TEMP         90

#define ADC0_ACTSS_REG          (*((volatile unsigned long *)0x40038000))
#define ADC0_RIS_REG            (*((volatile unsigned long *)0x40038004))
#define ADC0_IM_REG             (*((volatile unsigned long *)0x40038008))
#define ADC0_ISC_REG            (*((volatile unsigned long *)0x4003800C))
#define ADC0_EMUX_REG           (*((volatile unsigned long *)0x40038014))
#define ADC0_PSSI_REG           (*((volatile unsigned long *)0x40038028))
#define ADC0_SSMUX3_REG         (*((volatile unsigned long *)0x400380A0))
#define ADC0_SSCTL3_REG         (*((volatile unsigned long *)0x400380A4))
#define ADC0_SSFIFO3_REG        (*((volatile unsigned long *)0x400380A8))

void adc0_init(void);
int adc0_temp(void);
void adc0_handler(void); // ADC Interrupt Handler

#endif /* __ADC_H__ */
