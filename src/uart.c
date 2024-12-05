#include "../include/uart.h"

#define RXFE 4 // UART Receive FIFO Empty
#define TRANSMITTER_FULL  5

void uart_send(unsigned char data)
{
    while (GET_BIT(UART0_FR_REG, TRANSMITTER_FULL)); // wait for the transmitter to be free
    UART0_DR_REG = data;
}

unsigned char uart_receive(void)
{
    unsigned char data = 0xFF;
    while (GET_BIT(UART0_FR_REG, RXFE));
    data = UART0_DR_REG;
    return data;
}

void uart_init(void)
{
    // Enable all UART Module-0
    SET_BIT(SYSCTL_RCGCUART_REG,0);
    while(GET_BIT(SYSCTL_PRUART_REG, 0) == 0);

    // Enable the clock to GPIO module(Port_A)
    SET_BIT(SYSCTL_RCGCGPIO_REG,0);
    while(GET_BIT(SYSCTL_PRGPIO_REG, 0) == 0);

    //Activate Alternate function into UART
    SET_BIT(GPIO_PORTA_AFSEL_REG,0);
    SET_BIT(GPIO_PORTA_AFSEL_REG,1);

   //Digital Function (GPIOPCTL PMCx Bit Field Encoding)
    GPIO_PORTA_PCTL_REG |= 0x11;

    //DIGITAL Enable
    SET_BIT(GPIO_PORTA_DEN_REG,0);
    SET_BIT(GPIO_PORTA_DEN_REG,1);

    // Direction depend on functionality
    CLEAR_BIT(GPIO_PORTA_DIR_REG,0); //PA0 input
    SET_BIT(GPIO_PORTA_DIR_REG,1);  //PA1 Output

    // baud 9600
    UART0_CTL_REG = 0; // disable uart0
    UART0_CC_REG = 0;
    UART0_IBRD_REG = 104;
    UART0_FBRD_REG = 11;
    UART0_LCRH_REG = 0x70;
    UART0_CTL_REG |=  (UART0_CTL_EN_MASK | UART0_CTL_RXE_MASK | UART0_CTL_TXE_MASK); // enable uart0
}
