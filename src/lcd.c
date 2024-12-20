#include "../include/lcd.h"

static const uint8_t row_offsets[] = {0x00, 0x40, 0x10, 0x50};

static void lcd_send_high_nibble(const uint8_t data);
static void lcd_send_low_nibble(const uint8_t data);
static void lcd_send_enable(void);

static void lcd_reverse_string(uint8_t * const str, const uint8_t length);
static void lcd_int_to_string(int32_t data, uint8_t * const buffer);
static void lcd_float_to_string(float data, uint8_t * const buffer, uint8_t precision);



void lcd_init(void)
{
    gpio_initPin(LCD_RS_PORT, LCD_RS_PIN, GPIO_OUTPUT);
    gpio_initPin(LCD_RW_PORT, LCD_RW_PIN, GPIO_OUTPUT);
    gpio_initPin(LCD_EN_PORT, LCD_EN_PIN, GPIO_OUTPUT);
    gpio_initPin(LCD_D4_PORT, LCD_D4_PIN, GPIO_OUTPUT);
    gpio_initPin(LCD_D5_PORT, LCD_D5_PIN, GPIO_OUTPUT);
    gpio_initPin(LCD_D6_PORT, LCD_D6_PIN, GPIO_OUTPUT);
    gpio_initPin(LCD_D7_PORT, LCD_D7_PIN, GPIO_OUTPUT);

    delay_ms(15);

    lcd_send_command(LCD_COMMAND_RETURN_HOME);
    lcd_send_command(LCD_COMMAND_DISPLAY_OFF);
    lcd_send_command(LCD_COMMAND_CLEAR_DISPLAY);
    lcd_send_command(LCD_COMMAND_INCREMENT_CURSOR);
    lcd_send_command(LCD_COMMAND_RETURN_HOME);
    lcd_send_command(LCD_COMMAND_DISPLAY_ON);
    lcd_send_command(LCD_COMMAND_DDRAM_BASE);
}


void lcd_send_command(const LCD_CommandsTypeDef command)
{
    gpio_setPinLogic(LCD_RW_PORT, LCD_RW_PIN, GPIO_LOW);
    gpio_setPinLogic(LCD_RS_PORT, LCD_RS_PIN, GPIO_LOW);

    lcd_send_high_nibble(command);
    lcd_send_enable();
    lcd_send_low_nibble(command);
    lcd_send_enable();
}


void lcd_write_char(const uint8_t data)
{
    gpio_setPinLogic(LCD_RW_PORT, LCD_RW_PIN, GPIO_LOW);
    gpio_setPinLogic(LCD_RS_PORT, LCD_RS_PIN, GPIO_HIGH);

    lcd_send_high_nibble(data);
    lcd_send_enable();
    lcd_send_low_nibble(data);
    lcd_send_enable();
}


void lcd_write_string(const uint8_t *data)
{
    if ((void*)0 != data)
    {
        while (*data) lcd_write_char(*data++);
    }
}


void lcd_write_int(const int32_t data)
{
    uint8_t buffer[17];
    lcd_int_to_string(data, buffer);
    lcd_write_string(buffer);
}


void lcd_write_float(const float data, const uint8_t precision)
{
    uint8_t buffer[17];
    lcd_float_to_string(data, buffer, precision);
    lcd_write_string(buffer);
}


void lcd_set_cursor(const uint8_t row, const uint8_t col)
{
    if ((row < 2) and (col < 16))
    {
        lcd_send_command(LCD_COMMAND_DDRAM_BASE + row_offsets[row] + col);
    }
}


void lcd_clear_row(const uint8_t row)
{
    uint8_t buffer[17];
    lcd_set_cursor(row, 0);

    for (uint8_t i = 0; i < 16; ++i) buffer[i] = 0x20;
    buffer[16] = '\0';

    lcd_write_string(buffer);
    lcd_set_cursor(row, 0);
}


static void lcd_send_high_nibble(const uint8_t data)
{
    gpio_setPinLogic(LCD_D4_PORT, LCD_D4_PIN, (data >> 4) & 0x01);
    gpio_setPinLogic(LCD_D5_PORT, LCD_D5_PIN, (data >> 5) & 0x01);
    gpio_setPinLogic(LCD_D6_PORT, LCD_D6_PIN, (data >> 6) & 0x01);
    gpio_setPinLogic(LCD_D7_PORT, LCD_D7_PIN, (data >> 7) & 0x01);
}


static void lcd_send_low_nibble(const uint8_t data)
{
    gpio_setPinLogic(LCD_D4_PORT, LCD_D4_PIN, (data >> 0) & 0x01);
    gpio_setPinLogic(LCD_D5_PORT, LCD_D5_PIN, (data >> 1) & 0x01);
    gpio_setPinLogic(LCD_D6_PORT, LCD_D6_PIN, (data >> 2) & 0x01);
    gpio_setPinLogic(LCD_D7_PORT, LCD_D7_PIN, (data >> 3) & 0x01);
}


static void lcd_send_enable(void)
{
    gpio_setPinLogic(LCD_EN_PORT, LCD_EN_PIN, GPIO_HIGH);
    Delay_MicroSecond(1);
    gpio_setPinLogic(LCD_EN_PORT, LCD_EN_PIN, GPIO_LOW);
    delay_ms(2);
}

static void lcd_reverse_string(uint8_t * const str, const uint8_t length)
{
    uint8_t start = 0;
    uint8_t end = length - 1;
    
    while (start < end) 
    {
        str[start]   ^= str[end];
        str[end]     ^= str[start];
        str[start++] ^= str[end--];
    }
}


static void lcd_int_to_string(int32_t data, uint8_t * const buffer)
{
    uint8_t i = 0;
    uint8_t isNegative = 0;
    
    if (0 == data) 
    {
        buffer[i++] = '0';
        buffer[i] = '\0';

        return;
    }
    
    if (data < 0) 
    {
        isNegative = 1;
        data = -data;
    }
    
    while (data > 0) 
    {
        buffer[i++] = ((data % 10) + '0');
        data /= 10;
    }
    
    if (isNegative) buffer[i++] = '-';

    buffer[i] = '\0';
    
    lcd_reverse_string(buffer, i);
}


static void lcd_float_to_string(float data, uint8_t * const buffer, uint8_t precision)
{   
    int32_t intPart = (int32_t)data;
    float fracPart = data - intPart;

    lcd_int_to_string(intPart, buffer);

    uint8_t i = 0;
    while (buffer[++i]); 

    if (precision > 0) 
    {
        buffer[i++] = '.';

        while (precision-- > 0) fracPart *= 10;

        lcd_int_to_string((fracPart < 0) ? -(int32_t)fracPart : (int32_t)fracPart, (buffer + i));
    }
}
