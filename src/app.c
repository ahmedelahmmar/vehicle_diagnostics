#include "../include/app.h"


void handleMotors(void)
{
    sFlags.isThereAnOpenRequest = sFlags.openLeftMotor or sFlags.openRightMotor;
    sFlags.isThereACloseRequest = sFlags.closeLeftMotor or sFlags.closeRightMotor;

    
    if (sFlags.isThereAnOpenRequest)
    {
        if (sFlags.openLeftMotor) motors_start(LEFT_MOTOR, DIR_CW);
        if (sFlags.openRightMotor) motors_start(RIGHT_MOTOR, DIR_CCW);
    }

    if (sFlags.isThereACloseRequest)
    {
        if (sFlags.closeLeftMotor) motors_start(LEFT_MOTOR, DIR_CCW);
        if (sFlags.closeRightMotor) motors_start(RIGHT_MOTOR, DIR_CW);
    }

    if (sFlags.stopLeftMotor or sFlags.stopRightMotor)
    {
        if (sFlags.stopLeftMotor) motors_stop(LEFT_MOTOR);
        if (sFlags.stopRightMotor) motors_stop(RIGHT_MOTOR);
    }
}