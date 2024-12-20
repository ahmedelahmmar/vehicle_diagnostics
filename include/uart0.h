#ifndef UART_H
#define UART_H

#include "../tm4c123gh6pm_registers.h"
#include "../common_macros.h"

#define UART0_FR_RXFE_BIT           4       // rx fifo empty flag
#define UART0_FR_TXFF_BIT           5       // tx fifo full flag

#define UART0_NVIC_ISE_BIT          5

#define UART0_CTL_EN_MASK           0x00000001
#define UART0_CTL_TXE_MASK          0x00000100
#define UART0_CTL_RXE_MASK          0x00000200

#define UART0_IM_RXIM_BIT           4

#define ASCII_RETURN                0x0D
#define ASCII_BACKSPACE             0x08

void uart0_init(void);
void uart0_sendByte(unsigned char data);
void uart0_sendString(unsigned char * const buffer);
void uart0_print_str(char* s);
unsigned char uart0_getLastRecievedByte(void);

#endif /* UART_H */
