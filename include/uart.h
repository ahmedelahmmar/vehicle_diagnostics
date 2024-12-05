#ifndef UART_H
#define UART_H

#include "../tm4c123gh6pm_registers.h"
#include "../common_macros.h"

#define UART0_CTL_EN_MASK       0x01
#define UART0_CTL_TXE_MASK      0x100
#define UART0_CTL_RXE_MASK      0x200

void uart_init(void);
void uart_send(unsigned char data);
unsigned char uart_receive(void);

#endif /* UART_H */
