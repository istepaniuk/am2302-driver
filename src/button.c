#include <stdbool.h>
#include "hardware.h"
#include "button.h"
#include "platform.h"
#include "leds.h"

static bool depressed = false;

static void button_interrupt_handler()
{
    depressed = true;
}

void button_init()
{
    gpio_set_pin_mode(BUTTON_PIN, GPIO_MODE_IN_FLOATING);
    gpio_set_interrupt_on_rising(BUTTON_PIN, button_interrupt_handler);
}

bool button_is_depressed()
{
    if(depressed)
    {
        depressed = false;
        return true;
    }
    return false;
}
