#include <stdbool.h>
#include "interrupts.h"
#include "leds.h" 
#include "usart.h"
#include "timer.h"
#include "platform.h"
#include "hardware.h"

static bool acquiring = false;
static int thecount = 0;

static void delay(int count)
{
    while(count--){};
}

void am2302_interrupt_handler(void)
{
    if(!acquiring)
        return;
    thecount++;
}

void am2302_init()
{
    timer2_init();
    gpio_set_interrupt_on_rising(AM2302_PIN, am2302_interrupt_handler);
}

void am2302_acquire(void)
{
    gpio_set_pin_mode(AM2302_PIN, GPIO_MODE_OUT_PUSH_PULL);
    gpio_set_pin_high(AM2302_PIN);
    delay(50000);
    gpio_set_pin_low(AM2302_PIN);
    delay(25000);
    gpio_set_pin_high(AM2302_PIN);
    gpio_set_pin_mode(AM2302_PIN, GPIO_MODE_IN_FLOATING);
    timer2_start();
    
    //while(gpio_get_pin_state(AM2302_PIN) == 1) { }
    //while(gpio_get_pin_state(AM2302_PIN) == 0) { }

    acquiring = true;
    
    while(!timer2_has_finished())
    {
    
    }
    leds_turn_blue_off();
    
    acquiring = false;
    leds_turn_blue_off();
    while(thecount) {
        usart_putc('X');
        thecount--;
    }
}
