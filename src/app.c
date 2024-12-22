#include "../include/app.h"

static uint8_t current_temperature, last_temperature;
static uint8_t current_distance, last_distance;
static uint8_t fan_shutdown_flag = 0;


static void handle_motors(void);



void app_start_operation(void)
{
    lcd_send_command(LCD_COMMAND_CLEAR_DISPLAY);
    lcd_set_cursor(0, 0);
    lcd_write_string("Temp:");
    lcd_set_cursor(0, 7);
    lcd_write_string("C");
    lcd_set_cursor(0, 9);
    lcd_write_string("D:");
    lcd_set_cursor(0, 14);
    lcd_write_string("cm");
    lcd_set_cursor(1, 0);
    lcd_write_string("Left: C");
    lcd_set_cursor(1, 8);
    lcd_write_string("Right: C");

    while ( uart0_getLastRecievedByte() != '3' )
    {
        handle_motors();

        last_distance = current_distance;
        current_distance = Ultrasonic_ReadDistance();
        lcd_set_cursor(0, 11);
        lcd_write_string("   ");
        lcd_set_cursor(0, 11);
        lcd_write_int(current_distance);

        if ( (current_distance < 10) and (last_distance >= 10) )
        {
            app_log_error(P001_ACCIDENT_MIGHT_HAPPEN);
        }

        current_temperature = adc0_temp();
        lcd_set_cursor(0, 5);
        lcd_write_string("  ");
        lcd_set_cursor(0,5);
        lcd_write_int(current_temperature);

        if ( (current_temperature > 30) and (last_temperature <= 30) )
        {
            app_log_error(P002_ENGINE_HIGH_TEMPERATURE);
        }

        if (gpio_getPinLogic(PB_FAN_INPUT_PORT, PB_FAN_INPUT_PIN))
        {
            delay_ms(100);
            if (gpio_getPinLogic(PB_FAN_INPUT_PORT, PB_FAN_INPUT_PIN))
            {
                gpio_togglePinLogic(PB_FAN_OUTPUT_PORT, PB_FAN_OUTPUT_PIN);
            }
        }

        if ((GPIO_LOW == gpio_getPinLogic(PB_FAN_OUTPUT_PORT, PB_FAN_OUTPUT_PIN)) and !(fan_shutdown_flag))
        {
            app_log_error(P003_ENGINE_FAN_SHUTDOWN);
            fan_shutdown_flag = 1;
        }

        if (gpio_getPinLogic(PB_FAN_OUTPUT_PORT, PB_FAN_OUTPUT_PIN))
        {
            fan_shutdown_flag = 0;
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
            lcd_set_cursor(1, 5);
            lcd_write_string("  ");
            lcd_set_cursor(1, 5);
            lcd_write_string(" O");
        }

        if (openRightMotor) 
        {
            motors_start(RIGHT_MOTOR, DIR_CCW);
            lcd_set_cursor(1, 14);
            lcd_write_string("  ");
            lcd_set_cursor(1, 14);
            lcd_write_string(" O");
        }
    }

    if (isThereACloseRequest)
    {
        if (closeLeftMotor) 
        {
            motors_start(LEFT_MOTOR, DIR_CCW);
            lcd_set_cursor(1, 5);
             lcd_write_string("  ");
             lcd_set_cursor(1, 5);
             lcd_write_string(" C");
        }
        if (closeRightMotor) 
        {
            motors_start(RIGHT_MOTOR, DIR_CW);
            lcd_set_cursor(1, 14);
            lcd_write_string("  ");
            lcd_set_cursor(1, 14);
            lcd_write_string(" C");
        }
    }

    if (stopLeftMotor or stopRightMotor)
    {
        if (stopLeftMotor) motors_stop(LEFT_MOTOR);
        if (stopRightMotor) motors_stop(RIGHT_MOTOR);
    }
}


void app_log_error(DTC_Code_t error)
{
    // Static counters for block and offset
        static uint8_t block_counter = 0;
        static uint8_t offset_counter = 2; // Start from offset 2 as 0 and 1 are reserved

        // Read saved counters from EEPROM (only during the first call)
        static uint8_t initialized = 0;
        if (!initialized) {
            block_counter = EEPROM_RetrieveData(0, 0);  // Block counter saved in Block 0, Offset 0
            offset_counter = EEPROM_RetrieveData(0, 1); // Offset counter saved in Block 0, Offset 1
            initialized = 1;

            if ( (0 == block_counter) and (offset_counter < 2) ) offset_counter = 2;
        }

        // Write the error code to the current block and offset
        EEPROM_LogData(block_counter, offset_counter++, error);

        if (offset_counter == 16)
        { // Max offset is 15
            offset_counter = 0;
            block_counter++;

            if (block_counter == 16)
            { // Max block is 15
                block_counter = 0;
                offset_counter = 2;
            }


            EEPROM_LogData(0, 0, block_counter);
        }

        // Save offset counter to Offset 1
        EEPROM_LogData(0, 1, offset_counter);
}


void app_display_logged_errors(void)
{
    uint8_t block_counter = EEPROM_RetrieveData(0, 0);
    uint8_t offset_counter = EEPROM_RetrieveData(0, 1);

    if ( (0 == block_counter) and (2 == offset_counter) )
    {
        uart0_sendString("No Errors Logged.");
        return;
    }

    uart0_sendString("Fetching Logged Errors");

    uint8_t i = 0;
    for (; i < 10; i++)
    {
        uart0_sendByte('.');
        delay_ms(250);
    }

    uart0_sendString("\n\r");

    for (i = 0; i <= block_counter; i++)
    {
        uint8_t j = (0 == i) ? 2 : 0;

        for (; j < offset_counter; j++)
        {
            uint8_t current_logged_error = EEPROM_RetrieveData(i, j);

            switch (current_logged_error)
            {
                case 1:
                    uart0_sendString("[P001] Accident Might Happen\n\r");
                    break;

                case 2:
                    uart0_sendString("[P002] Engine High Temperature\n\r");
                    break;

                default: break;
            }
        }
    }

    uart0_sendString("\n\r");
}
