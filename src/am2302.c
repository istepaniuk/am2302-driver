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

struct sensor_data
{
    uint16_t humidity;
    int16_t temperature;
    uint8_t _padding;
    uint8_t parity;
};


uint64_t raw_data;

static void delay(int count)
{
    while(count--){ };
}

static void interrupt_handler()
{
    if(!acquiring)
        return;
    int timestamp = timer2_get_current_counter();
    uint64_t bit_value = (timestamp - last_timestamp) > HI_BIT_THRESHOLD_TIME;
    last_timestamp = timestamp;
    
    if (timestamp > VALID_DATA_START_TIME)
        raw_data |= bit_value << bit_position++;
}

static void reset()
{
    bit_position = 0;
    last_timestamp = 0;
    raw_data = 0;
    acquiring = false;
}

static int16_t sm2tc(uint16_t x) 
{
    int16_t sign_mask = ~(1 << 15);
    int16_t positive_part = x & sign_mask;
    bool is_negative = (~sign_mask & x);
    return is_negative ? -positive_part : positive_part;
}

static struct sensor_data get_sensor_data()
{
    struct sensor_data sdata;
    uint64_t *psdata = &sdata;
    *psdata = 0;
    int i;
    for(i = 0; i < 40; i++)
    {
        uint64_t bit = (raw_data & ((int64_t) 1 << i)) > 0;
        int new_position = 15 - (i % 16) + (i / 16) * 16;
        *psdata |= bit << new_position;
    }
    sdata.temperature = sm2tc(sdata.temperature);
    return sdata;
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
    
    struct sensor_data a = get_sensor_data();
    
    usart_putc('h');
    printint(a.humidity);
    
    usart_putc('t');
    printint(a.temperature);
    
    usart_putc('p');
    printhex(a.parity);
    
    usart_putc('\n');
}

void am2302_init()
{
    timer2_init();
    gpio_set_interrupt_on_rising(AM2302_PIN, interrupt_handler);
}