#include "../include/app.h"


void handleMotors(void)
{
    isThereAnOpenRequest = openLeftMotor or openRightMotor;
    isThereACloseRequest = closeLeftMotor or closeRightMotor;

    
    if (isThereAnOpenRequest)
    {
        if (openLeftMotor) motors_start(LEFT_MOTOR, DIR_CW);
        if (openRightMotor) motors_start(RIGHT_MOTOR, DIR_CCW);
    }

    if (isThereACloseRequest)
    {
        if (closeLeftMotor) motors_start(LEFT_MOTOR, DIR_CCW);
        if (closeRightMotor) motors_start(RIGHT_MOTOR, DIR_CW);
    }

    if (stopLeftMotor or stopRightMotor)
    {
        if (stopLeftMotor) motors_stop(LEFT_MOTOR);
        if (stopRightMotor) motors_stop(RIGHT_MOTOR);
    }
}