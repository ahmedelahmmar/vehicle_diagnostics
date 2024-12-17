#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>
#include "../common_macros.h"
#include "../tm4c123gh6pm_registers.h"
#include "gpio.h"

#define TRIGGER_PIN 0x20  // PB5
#define ECHO_PIN    0x40  // PB6
#define THRESHOLD_DISTANCE 10 // 10 cm
#define ERROR_CODE "P001 - ACCIDENT_MIGHT_HAPPENED"

// Timer0 Registers
#define TIMER0_CFG_REG          (*((volatile unsigned long *)0x40030000))
#define TIMER0_TAMR_REG         (*((volatile unsigned long *)0x40030004))
#define TIMER0_CTL_REG          (*((volatile unsigned long *)0x4003000C))
#define TIMER0_TAV_REG          (*((volatile unsigned long *)0x40030050))

// Timer1 Registers
#define TIMER1_CFG_REG          (*((volatile unsigned long *)0x40031000))
#define TIMER1_TAMR_REG         (*((volatile unsigned long *)0x40031004))
#define TIMER1_CTL_REG          (*((volatile unsigned long *)0x4003100C))
#define TIMER1_RIS_REG          (*((volatile unsigned long *)0x4003101C))
#define TIMER1_ICR_REG          (*((volatile unsigned long *)0x40031024))
#define TIMER1_TAILR_REG        (*((volatile unsigned long *)0x40031028))
#define TIMER1_TAV_REG          (*((volatile unsigned long *)0x40031050))

void Delay_MicroSecond(int time); // Function to generate delay in microseconds

void Ultrasonic_Init(void); // Function to initialize the HC-SR04 ultrasonic sensor

uint32_t Ultrasonic_ReadDistance(void); // Function to trigger the ultrasonic sensor and get the distance

void GPIO_PortB_Handler(void); // Function to handle the interrupt for the ultrasonic sensor

#endif // ULTRASONIC_H