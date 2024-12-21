#include "./include/app.h"


int temp;
int dist;

volatile recieved_byte = 0xFF;

int main(void)
{
    // pb_init();

    // adc0_init();

    // lcd_init();
    // delay_ms(200);
    // lcd_set_cursor(0, 0);
    // lcd_write_string("T:");
    // lcd_set_cursor(0, 5);
    // lcd_write_string("C");
    // lcd_set_cursor(0, 7);
    // lcd_write_string("D:");
    // lcd_set_cursor(0, 13);
    // lcd_write_string("cm");
    // lcd_set_cursor(1, 0);
    // lcd_write_string("L:Closed");
    // lcd_set_cursor(1, 8);
    // lcd_write_string("R:Closed");
    // Ultrasonic_Init();

    // while(1)
    // {
    //     handleMotors();
    //     temp = adc0_temp();
    //     lcd_set_cursor(0,5);
    //     lcd_write_int(temp);

    //     dist = Ultrasonic_ReadDistance();
    //     lcd_set_cursor(0, 9);
    //     lcd_write_string("    ");
    //     lcd_set_cursor(0, 9);
    //     lcd_write_int(dist);
    
    //     delay_ms(1000);
    // }

    uart0_init();

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
                uart0_sendString("\n\rInitializing Operation Cycle");

                for (uint8_t i = 0; i < 10; i++)
                {
                    uart0_sendByte('.');
                    delay_ms(250);
                }

                uart0_sendString("\n\rOperation Started Succesfully\n\r");
                uart0_sendString("Press 3 to terminate the operation cycle");

                // start_app();
            }
            else if ('2' == recieved_byte)
            {
                eeprom_retrieve_logged_errors();
            }
        }
    }


}
