#ifndef __ADC_H__
#define __ADC_H__

#include  "../tm4c123gh6pm_registers.h"
#include "../common_macros.h"

#define ADC0_ACTSS_REG          (*((volatile unsigned long *)0x40038000))
#define ADC0_EMUX_REG          (*((volatile unsigned long *)0x40038014))
#define ADC0_SSMUX3_REG          (*((volatile unsigned long *)0x400380A0))
#define ADC0_SSCTL3_REG          (*((volatile unsigned long *)0x400380A4))

void adc0_init(void);

#endif /* __ADC_H__ */