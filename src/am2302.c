#include <stdbool.h>
#include "interrupts.h"
#include "leds.h" 
#include "usart.h"
#include "timer.h"
#include "platform.h"
#include "hardware.h"

#define HI_BIT_THRESHOLD_TIME 100
#define VALID_DATA_START_TIME 250

static bool acquiring = false;
static int bit_position;
static int last_timestamp;

struct amdata
{
    uint16_t humidity;  
    int16_t temperature;
    uint8_t parity;
    uint8_t empty;
};


struct amdata a;
uint64_t *buffer = &a;

static void delay(int count)
{
    while(count--){ };
}

static void interrupt_handler()
{
    if(!acquiring)
        return;
    int timestamp = timer2_get_current_counter();
    int bit_value = (timestamp - last_timestamp) > HI_BIT_THRESHOLD_TIME;
    last_timestamp = timestamp;
    if( timestamp < VALID_DATA_START_TIME ) 
        return;
    
    *buffer |= bit_value << bit_position;
    
    bit_position++;
}

static void reset()
{
    bit_position = 0;
    last_timestamp = 0;
    *buffer = 0;
    acquiring = false;
}

void am2302_init()
{
    timer2_init();
    gpio_set_interrupt_on_rising(AM2302_PIN, interrupt_handler);
}

void am2302_acquire()
{
    reset();
    gpio_set_pin_mode(AM2302_PIN, GPIO_MODE_OUT_PUSH_PULL);
    gpio_set_pin_low(AM2302_PIN);
    delay(35200);
    gpio_set_pin_high(AM2302_PIN);
    gpio_set_pin_mode(AM2302_PIN, GPIO_MODE_IN_FLOATING);
    
    timer2_start();
    acquiring = true;
    while(!timer2_has_finished() && bit_position < 40) { }
    acquiring = false;
    timer2_stop();
    
    if(bit_position < 40)
        usart_puts("Timeout!\n");
    
    usart_putc('h');
    dump16h(a.humidity);
    
    //usart_putc('H');dump16(a.humidity);
 
    usart_putc('t');
    dump16h(a.temperature);
    
    //usart_putc('T');dump16(a.temperature);
        
    usart_putc('p');
    dump16h(a.parity);
    
    usart_putc('e');
    dump16h(a.empty);
    
    usart_putc('+');
    dump16h(bit_position);
    
    usart_putc('\n');
}