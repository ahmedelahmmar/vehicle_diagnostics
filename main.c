#include "./include/app.h"

volatile recieved_byte = 0xFF;

int main(void)
11{
    pb_init();
    motors_init();
    lcd_init();
    adc0_init();
    uart0_init();
    Ultrasonic_Init();
    EEPROM_init();
    delay_ms(250);

    uart0_sendString("\n\rVehicle Fault Detection and Logging System [VFDLS]\n\n\r");
    uart0_sendString("Please press [1] to initialize the system.\n\n\r");

    lcd_send_command(LCD_COMMAND_CLEAR_DISPLAY);
    lcd_set_cursor(0, 3);
    lcd_write_string("VFDL System");
    lcd_set_cursor(1, 1);
    lcd_write_string("1: Initialize");

    while (1)
    {
        recieved_byte = uart0_getLastRecievedByte();

        if (0xFF != recieved_byte)
        {
            if ('1' == recieved_byte)
            {
                uart0_sendString("\n\rInitializing");
                lcd_send_command(LCD_COMMAND_CLEAR_DISPLAY);
                lcd_set_cursor(0, 2);
                lcd_write_string("Initializing");
                lcd_set_cursor(1, 5);
                lcd_write_string("System");

                uint8_t i = 0;
                for (; i < 10; i++)
                {
                    uart0_sendByte('.');
                    delay_ms(250);
                }

                uart0_sendString("\n\n\r\tSystem Started Succesfully!\n\n\r");
                uart0_sendString("\tPress [2] to fetch logged errors.\n\r");
                uart0_sendString("\tPress [3] to terminate operation.\n\n\r");

                app_start_operation();

                uart0_sendString("\n\r\tSystem Operation Terminated!\n\n\r");

                uart0_sendString("\n\rVehicle Fault Detection and Logging System [VFDLS]\n\n\r");
                uart0_sendString("Please press [1] to initialize the system.\n\r");

                lcd_send_command(LCD_COMMAND_CLEAR_DISPLAY);
                lcd_set_cursor(0, 3);
                lcd_write_string("VFDL System");
                lcd_set_cursor(1, 1);
                lcd_write_string("1: Initialize");
            }
            else
            {
                uart0_sendString("Invalid Option!\n\r");
            }
        }
    }
}
