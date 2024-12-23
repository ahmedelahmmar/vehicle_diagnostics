#include "./include/app.h"

volatile recieved_byte = 0xFF;

int main(void)
{
    pb_init();
    motors_init();
    lcd_init();
    adc0_init();
    uart0_init();
    Ultrasonic_Init();
    EEPROM_init();
    delay_ms(250);

    uart0_sendString("Vehicle Fault Detection and Logging System (VFDLS)\n\n\r");
    uart0_sendString("Please select one of the following options:\n\r");
    uart0_sendString("1. Start Operation Cycle.\n\r");
    uart0_sendString("2. Retrieve Logged Errors.\n\r");

    lcd_send_command(LCD_COMMAND_CLEAR_DISPLAY);
    lcd_set_cursor(0, 3);
    lcd_write_string("VFDL System");
    lcd_set_cursor(1, 1);
    lcd_write_string("1:Start 2:Logs");

    while (1)
    {
        recieved_byte = uart0_getLastRecievedByte();

        if (0xFF != recieved_byte)
        {
            if ('1' == recieved_byte)
            {
                uart0_sendString("Initializing Operation Cycle");
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

                uart0_sendString("\n\rOperation Started Succesfully\n\r");
                uart0_sendString("Press 3 to terminate the operation cycle\n\r");

                app_start_operation();

                uart0_sendString("Operation Cycle Terminated.\n\r");
            }
            else
            {
                uart0_sendString("Invalid Option!\n\r");
            }

            lcd_send_command(LCD_COMMAND_CLEAR_DISPLAY);
            lcd_set_cursor(0, 3);
            lcd_write_string("VFDL System");
            lcd_set_cursor(1, 1);
            lcd_write_string("1: Initialize");
        }
    }
}
