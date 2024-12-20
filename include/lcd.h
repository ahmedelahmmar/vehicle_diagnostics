#ifndef __LCD_H__
#define __LCD_H__

#include "gpio.h"
#include "ultrasonic.h"
#include "../common_macros.h"
/*
 * Pin Connections for LCD with Tiva C (Port C and Port D) in 4-bit mode:
 * ------------------------------------------------------------
 * Tiva C Pin    |   LCD Pin    |   Description
 * -----------------------------------------------
 * PD0           |   RS         |   Register Select (1 = Data, 0 = Command)
 * PD1           |   RW         |   Read/Write (0 = Write, 1 = Read)
 * PD2           |   EN         |   Enable (Pulse High to Low to latch data)
 * PC4           |   D4         |   Data bit 4
 * PC5           |   D5         |   Data bit 5
 * PC6           |   D6         |   Data bit 6
 * PC7           |   D7         |   Data bit 7
 */

#define LCD_RS_PORT     GPIOD
#define LCD_RS_PIN      GPIO_PIN_0

#define LCD_RW_PORT     GPIOD
#define LCD_RW_PIN      GPIO_PIN_1

#define LCD_EN_PORT     GPIOD
#define LCD_EN_PIN      GPIO_PIN_2

#define LCD_D4_PORT     GPIOD
#define LCD_D4_PIN      GPIO_PIN_3

#define LCD_D5_PORT     GPIOC
#define LCD_D5_PIN      GPIO_PIN_5

#define LCD_D6_PORT     GPIOC
#define LCD_D6_PIN      GPIO_PIN_6

#define LCD_D7_PORT     GPIOC
#define LCD_D7_PIN      GPIO_PIN_7

typedef enum
{
    LCD_COMMAND_CLEAR_DISPLAY       = 0x01,
    LCD_COMMAND_RETURN_HOME         = 0x02,
    LCD_COMMAND_DECREMENT_CURSOR    = 0x04, 
    LCD_COMMAND_INCREMENT_CURSOR    = 0x06,
    LCD_COMMAND_DISPLAY_OFF         = 0x08,
    LCD_COMMAND_DISPLAY_ON          = 0x0C,
    LCD_COMMAND_4BIT_MODE_1LINE     = 0x20,
    LCD_COMMAND_4BIT_MODE_2LINE     = 0x28,
    LCD_COMMAND_8BIT_MODE_1LINE     = 0x30,
    LCD_COMMAND_8BIT_MODE_2LINE     = 0x38,
    LCD_COMMAND_CGRAM_BASE          = 0x40,
    LCD_COMMAND_DDRAM_BASE          = 0x80,

} LCD_CommandsTypeDef;

void lcd_init(void);
void lcd_send_command(const LCD_CommandsTypeDef command);
void lcd_write_char(const uint8_t data);
void lcd_write_string(const uint8_t *data);
void lcd_write_int(const int32_t data);
void lcd_write_float(const float data, const uint8_t precision);
void lcd_set_cursor(const uint8_t row, const uint8_t col);
void lcd_clear_row(const uint8_t row);

#endif /* __LCD_H__ */
