#ifndef __APP_H__
#define __APP_H__

#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

#include "./include/uart0.h"
#include "./include/motors.h"
#include "./include/pb.h"
#include "./include/LCD.h"
#include "./include/adc.h"
#include "./include/ultrasonic.h"

void handleMotors(void);

#endif /* __APP_H__*/
