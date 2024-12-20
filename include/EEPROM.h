/*
 * EEPROM.h
 *
 *  Created on: Dec 20, 2024
 *      Author: yusuf
 */

#include  "../tm4c123gh6pm_registers.h"
#include "../common_macros.h"

void EEPROM_init();
void EEPROM_LogData(uint32_t block, uint32_t offset, uint32_t data) ;
uint32_t EEPROM_RetrieveData(uint32_t block, uint32_t offset);
