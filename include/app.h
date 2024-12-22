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
#include "EEPROM.h"


typedef enum
{
    P001_ACCIDENT_MIGHT_HAPPEN=1,
    P002_ENGINE_HIGH_TEMPERATURE,
    P003_ENGINE_FAN_SHUTDOWN

} DTC_Code_t;


void app_start_operation(void);
void app_log_error(DTC_Code_t error);
void app_display_logged_errors(void);

#endif /* __APP_H__*/
