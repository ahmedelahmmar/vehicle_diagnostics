/*
 * EEPROM.c
 *
 *  Created on: Dec 20, 2024
 *      Author: yusuf
 */
#include "../include/EEPROM.h"

#define EEPROM_EEDONE          (*((volatile unsigned long *)0x400AF018))
#define EEPROM_EEUNLOCK        (*((volatile unsigned long *)0x400AF020))
#define EEPROM_EEBLOCK         (*((volatile unsigned long *)0x400AF004))
#define EEPROM_EEOFFSET        (*((volatile unsigned long *)0x400AF008))
#define EEPROM_EERDWR          (*((volatile unsigned long *)0x400AF010))

void EEPROM_init(void)
{
    SET_BIT(SYSCTL_RCGCEEPROM_REG,0);   // Enable and provide a clock to the EEPROM module in Run mode.
    while (!GET_BIT(SYSCTL_PREEPROM_REG, 0));   //Wait Until EEPROM is Ready
    while (GET_BIT(EEPROM_EEDONE, 0) != 0);     // Wait for "WORKING" bit to clear
    EEPROM_EEUNLOCK = 0xA442;       // Unlock sequence for Tiva-C
    while (GET_BIT(EEPROM_EEDONE, 0) != 0);  // Wait for "WORKING" bit to clear
}

void EEPROM_LogData(uint32_t block, uint32_t offset, uint32_t data)
{

    EEPROM_EEBLOCK = block;  // Select the block

    EEPROM_EEOFFSET = offset;     // Set the offset in the block

    EEPROM_EERDWR = data;   //  Write the data

    while (GET_BIT(EEPROM_EEDONE, 0) != 0);  // Wait for "WORKING" bit to clear
}

uint32_t EEPROM_RetrieveData(uint32_t block, uint32_t offset)
{

    EEPROM_EEBLOCK = block; //Select the block


    EEPROM_EEOFFSET = offset;     // Set the offset in the block


    uint32_t data = EEPROM_EERDWR;  //Read the data


    while (GET_BIT(EEPROM_EEDONE, 0) != 0);  // Wait for "WORKING" bit to clear

    return data;
}
