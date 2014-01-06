#include <stdbool.h>
#include "interrupts.h"
#include "leds.h" 
#include "usart.h"
#include "timer.h"
#include "platform.h"
#include "hardware.h"

#define HI_BIT_THRESHOLD_TIME 100

static bool acquiring = false;
static int bit_position;
static int last_timestamp;
static uint32_t raw_data_lo;
static uint32_t raw_data_hi;

static void delay(int count)
{
    while(count--){};
}

static void am2302_interrupt_handler(void)
{
    if(!acquiring)
        return;
    int timestamp = timer2_get_current_counter();
    int bit_value = (timestamp - last_timestamp) > HI_BIT_THRESHOLD_TIME ? 0 : 1;
    last_timestamp = timestamp;
    if( timestamp < 250 ) 
        return;
    
    if (bit_position < 32)
        raw_data_lo |= bit_value << bit_position;
    else
        raw_data_hi |= bit_value << (bit_position - 32);
    
    bit_position++;
}

void am2302_init()
{
    timer2_init();
    gpio_set_interrupt_on_rising(AM2302_PIN, am2302_interrupt_handler);
}

void am2302_acquire(void)
{
    bit_position = 0;
    last_timestamp = 0;
    raw_data_lo = 0;
    raw_data_hi = 0;
    
    gpio_set_pin_mode(AM2302_PIN, GPIO_MODE_OUT_PUSH_PULL);
    gpio_set_pin_high(AM2302_PIN);
    delay(50000);
    gpio_set_pin_low(AM2302_PIN);
    delay(25000);
    gpio_set_pin_high(AM2302_PIN);
    gpio_set_pin_mode(AM2302_PIN, GPIO_MODE_IN_FLOATING);
    
    timer2_start();
    
    acquiring = true;
    
    while(!timer2_has_finished() && bit_position < 40) { }
    timer2_stop();
    
    acquiring = false;
    if(bit_position < 40)
        usart_puts("Timeout!\n");

    usart_putc('L');
    dump32h(raw_data_lo);
    
    usart_putc('H');
    dump32h(raw_data_hi);
    
    usart_putc('P');
    dump32h(bit_position);
}
