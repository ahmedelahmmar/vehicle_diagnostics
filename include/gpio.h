#ifndef __GPIO_H__
#define __GPIO_H__

#include "../common_macros.h"
#include "../tm4c123gh6pm_registers.h"


typedef enum
{
    GPIOA=0,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOF,
    GPIOE,

} GPIO_Port_t;


typedef enum
{
    GPIO_PIN_0=0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,

} GPIO_Pin_t;


typedef enum
{
    GPIO_INPUT=0,
    GPIO_INPUT_PULLUP,
    GPIO_INPUT_PULLDOWN,
    GPIO_OUTPUT,

} GPIO_Direction_t;


typedef enum
{
    GPIO_LOW=0,
    GPIO_HIGH,

} GPIO_Logic_t;


void gpio_initPin(GPIO_Port_t port, GPIO_Pin_t pin, GPIO_Direction_t direction);
void gpio_setPinLogic(GPIO_Port_t port, GPIO_Pin_t pin, GPIO_Logic_t logic);
unsigned char gpio_getPinLogic(GPIO_Port_t port, GPIO_Pin_t pin);

#endif /* __GPIO_H__ */
