#ifndef _HARDWARE_H
#define _HARDWARE_H
#include "platform.h"

#define BLUE_LED_PIN GPIO_PIN_C8
#define GREEN_LED_PIN GPIO_PIN_C9

#define USART_TX_PIN GPIO_PIN_A9
#define USART_RX_PIN GPIO_PIN_A10

#define BUTTON_PIN GPIO_PIN_A0

#define AM2302_PINS (pin_def_t []) { GPIO_PIN_C10, GPIO_PIN_C11, GPIO_PIN_C12 }

#endif