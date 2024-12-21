#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>
#include "../common_macros.h"
#include "../tm4c123gh6pm_registers.h"
#include "gpio.h"

#define TRIGGER_PORT            GPIOB
#define ECHO_PORT               GPIOB
#define TRIGGER_PIN             GPIO_PIN_2  // PB2
#define ECHO_PIN                GPIO_PIN_3  // PB3
#define THRESHOLD_DISTANCE      10 // 10 cm
#define ERROR_CODE              "P001 - ACCIDENT_MIGHT_HAPPENED"

#define GPIO_PORTB_MIS_REG  (*(volatile unsigned long*)0x40005418)

// Timer0 Registers
#define TIMER3_CFG_REG          (*((volatile unsigned long *)0x40033000))
#define TIMER3_TBMR_REG         (*((volatile unsigned long *)0x40033008))
#define TIMER3_CTL_REG          (*((volatile unsigned long *)0x4003300C))
#define TIMER3_IMR_REG          (*((volatile unsigned long *)0x40033018))
#define TIMER3_TBR_REG          (*((volatile unsigned long *)0x4003304C))

void SysTick_Init(void);
void SysTick_Wait(unsigned long delay);
void SysTick_Wait10us(unsigned long delay);

void Ultrasonic_Init(void); // Function to initialize the HC-SR04 ultrasonic sensor

void Ultrasonic_Trigger(void); // Function to trigger the ultrasonic sensor

uint32_t Ultrasonic_ReadDistance(void); // Function to trigger the ultrasonic sensor and get the distance

void GPIO_PortB_Handler(void); // Function to handle the interrupt for the ultrasonic sensor

#endif // ULTRASONIC_H
