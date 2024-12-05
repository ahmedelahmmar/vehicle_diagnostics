/*
 * LCD.h
 *
 *  Created on: Dec 5, 2024
 *      Author: yusuf
 */

void LCD_init(void);
void LCD_command(unsigned char cmd);
void LCD_data(unsigned char data);
void LCD_print(char* str);
