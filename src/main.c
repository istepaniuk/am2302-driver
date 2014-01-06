#include <stdio.h>
#include "stm32f10x.h"
#include "usart.h"
#include "button.h"
#include "leds.h"

void delay(int count) { while(count--){}; }

int main(void)
{
    // Enable GPIO clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    usart_init();
    button_init();
    leds_init();
    am2302_init();
    
    leds_turn_blue_on();

    while(1) { 
        if(button_is_depressed())
        {
            leds_turn_green_on();
            delay(1000000);
            am2302_acquire();
            leds_turn_green_off();
            delay(10000000);
        }
    }
}