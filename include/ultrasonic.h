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

void SysTick_Init(void);
void SysTick_Wait(unsigned long delay);

void Ultrasonic_Init(void); // Function to initialize the HC-SR04 ultrasonic sensor
uint32_t Ultrasonic_ReadDistance(void); // Function to trigger the ultrasonic sensor and get the distance

#endif // ULTRASONIC_H
