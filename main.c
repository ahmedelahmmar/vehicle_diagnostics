#include "./include/app.h"

volatile recieved_byte = 0xFF;

int main(void)
{
    pb_init();
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


    while (1)
    {
        recieved_byte = uart0_getLastRecievedByte();

        if (0xFF != recieved_byte)
        {
            if ('1' == recieved_byte)
            {
                uart0_sendString("Initializing Operation Cycle");

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
            else if ('2' == recieved_byte)
            {
                app_display_logged_errors();
            }
        }
    }
}
