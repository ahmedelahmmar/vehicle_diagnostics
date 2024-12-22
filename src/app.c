#include "../include/app.h"


static uint8_t current_temperature;
static uint8_t current_distance;


static void handle_motors(void);
static void handle_temperature_sensor(void);
static void handle_ultrasonic_sesnor(void);


void app_start_operation(void)
{
    lcd_send_command(LCD_COMMAND_CLEAR_DISPLAY);
    lcd_set_cursor(0, 0);
    lcd_write_string("T:");
    lcd_set_cursor(0, 5);
    lcd_write_string("C");
    lcd_set_cursor(0, 7);
    lcd_write_string("D:");
    lcd_set_cursor(0, 13);
    lcd_write_string("cm");
    lcd_set_cursor(1, 0);
    lcd_write_string("L:Closed");
    lcd_set_cursor(1, 8);
    lcd_write_string("R:Closed");

    while ( uart0_getLastRecievedByte() != '3' )
    {
        handleMotors();

        current_distance = Ultrasonic_ReadDistance();
        lcd_set_cursor(0, 9);
        lcd_write_string("    ");
        lcd_set_cursor(0, 9);
        lcd_write_int(current_distance);

        if (current_distance < 10)
        {
            app_log_error(P001_ACCIDENT_MIGHT_HAPPEN);
        }

        current_temperature = adc0_temp();
        lcd_set_cursor(0, 5);
        lcd_write_string("    ");
        lcd_set_cursor(0,5);
        lcd_write_int(current_temperature);

        if (current_temperature > 90)
        {
            app_log_error(P002_ENGINE_HIGH_TEMPERATURE);
        }
    
        delay_ms(1000);
    }

    lcd_send_command(LCD_COMMAND_CLEAR_DISPLAY);
}

void handle_motors(void)
{
    isThereAnOpenRequest = openLeftMotor or openRightMotor;
    isThereACloseRequest = closeLeftMotor or closeRightMotor;

    if (isThereAnOpenRequest)
    {
        if (openLeftMotor)
        {
            motors_start(LEFT_MOTOR, DIR_CW);
            lcd_set_cursor(1, 2);
            lcd_write_string("      ");
            lcd_set_cursor(1, 2);
            lcd_write_string("Open");
        }

        if (openRightMotor) 
        {
            motors_start(RIGHT_MOTOR, DIR_CCW);
            lcd_set_cursor(1, 10);
            lcd_write_string("      ");
            lcd_set_cursor(1, 10);
            lcd_write_string("Open");
        }
    }

    if (isThereACloseRequest)
    {
        if (closeLeftMotor) 
        {
            motors_start(LEFT_MOTOR, DIR_CCW);
            lcd_set_cursor(1, 2);
            lcd_write_string("      ");
            lcd_set_cursor(1, 2);
            lcd_write_string("Closed");
        }
        if (closeRightMotor) 
        {
            motors_start(RIGHT_MOTOR, DIR_CW);
            lcd_set_cursor(1, 10);
            lcd_write_string("      ");
            lcd_set_cursor(1, 10);
            lcd_write_string("Closed");
        }
    }

    if (stopLeftMotor or stopRightMotor)
    {
        if (stopLeftMotor) motors_stop(LEFT_MOTOR);
        if (stopRightMotor) motors_stop(RIGHT_MOTOR);
    }
}
