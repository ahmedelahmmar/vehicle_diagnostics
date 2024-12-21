#ifndef __APP_H__
#define __APP_H__

#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"

#include "uart0.h"
#include "motors.h"
#include "pb.h"
#include "lcd.h"
#include "adc.h"
#include "ultrasonic.h"


#define DTC_ACCIDENT_MIGHT_HAPPENED "P001 - ACCIDENT"
#define DTC_ENGINE_HIGH_TEMPERATURE "P002 - HIGH TEMP"

void handleMotors(void);
void start_app(void);

#endif /* __APP_H__*/
