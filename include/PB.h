/*
 * PB.h
 *
 *  Created on: Dec 5, 2024
 *      Author: yusuf
 */
#include "tm4c123gh6pm_registers.h"
#include "common_macros.h"



typedef enum
{
    LM_FRONT=0,
    LM_REAR,
    RM_FRONT,
    RM_REAR,

} pb_t;

void PB_init(void);
char PB_check(pb_t button_id);
