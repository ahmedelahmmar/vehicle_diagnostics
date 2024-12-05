#include "../include/uart0.h"


static volatile unsigned char last_recieved_byte = 0xFF; // default value


void uart0_init(void)
{
    // Enable all UART Module-0
    SET_BIT(SYSCTL_RCGCUART_REG, 0);
    while(GET_BIT(SYSCTL_PRUART_REG, 0) == 0);

    // Enable the clock to GPIO module(Port_A)
    SET_BIT(SYSCTL_RCGCGPIO_REG, 0);
    while(GET_BIT(SYSCTL_PRGPIO_REG, 0) == 0);

    //Activate Alternate function into UART
    SET_BIT(GPIO_PORTA_AFSEL_REG, 0);
    SET_BIT(GPIO_PORTA_AFSEL_REG, 1);

   //Digital Function (GPIOPCTL PMCx Bit Field Encoding)
    GPIO_PORTA_PCTL_REG |= 0x11;

    //DIGITAL Enable
    SET_BIT(GPIO_PORTA_DEN_REG, 0);
    SET_BIT(GPIO_PORTA_DEN_REG, 1);

    // Direction depend on functionality
    CLEAR_BIT(GPIO_PORTA_DIR_REG, 0); //PA0 input
    SET_BIT(GPIO_PORTA_DIR_REG, 1);  //PA1 Output

    // Enable NVIC uart0 interrupt
    NVIC_EN0_REG |= (1 << UART0_NVIC_ISE_BIT);

    // Priority = 0
    NVIC_PRI1_REG &= 0xFFFF00FF;

    // Enable rx interrupts
    SET_BIT(UART0_IM_REG, UART0_IM_RXIM_BIT);

    
    UART0_CTL_REG = 0; // disable uart0
    UART0_CC_REG = 0;

    // baud 9600
    UART0_IBRD_REG = 104;
    UART0_FBRD_REG = 11;

    UART0_LCRH_REG = 0x60; // Parity off, 8 bits data, 1 stop bit
    UART0_CTL_REG |=  (UART0_CTL_EN_MASK | UART0_CTL_RXE_MASK | UART0_CTL_TXE_MASK); // enable uart0
}


void uart0_sendByte(unsigned char data)
{
    while (GET_BIT(UART0_FR_REG, UART0_FR_TXFF_BIT)); // wait for the transmitter to be free
    UART0_DR_REG = data;
}


void uart0_sendString(unsigned char * const buffer)
{
    if ((void*)0 != buffer)
    {
        unsigned short i = 0;
        while (buffer[i]) uart0_sendByte(buffer[i++]);
    }
}



unsigned char uart0_getLastRecievedByte(void)
{
    unsigned char buffer = last_recieved_byte;
    last_recieved_byte = 0xFF;
    return buffer;
}


void uart0_receiveByteISR(void)
{
    if (!GET_BIT(UART0_FR_REG, UART0_FR_RXFE_BIT))
    {
        unsigned char buffer = UART0_DR_REG;

        if ((ASCII_RETURN != buffer) && (ASCII_BACKSPACE != buffer))
        {
            last_recieved_byte = buffer;
        }
    }
}