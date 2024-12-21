#include "../include/app.h"


void handleMotors(void)
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
