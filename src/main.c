#include <stdio.h>
#include "stm32f10x.h"
#include "usart.h"
#include "am2302.h"
#include "button.h"
#include "leds.h"

void delay(int count) { while(count--){}; }

void print_sensor_data(struct am2302_sensor_data_t sdata)
{
    usart_puts(" humi: "); printint(sdata.humidity); usart_puts("\n");
    usart_puts(" temp: "); printint(sdata.temperature); usart_puts("\n");
}

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
    
    int i = 0;
    while(1) { 
        leds_turn_green_on();
        am2302_start_acquire(i % 3);
        while(!am2302_acquire_has_finished()) { }
        usart_puts("\nsensor: "); printint(i%3); usart_puts("\n");
        print_sensor_data(am2302_get_sensor_data());
        leds_turn_green_off();
        delay(3000000);
        i++;
    }
}