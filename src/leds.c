#include "leds.h"
#include "platform.h"
#include "hardware.h"

void leds_init()
{
    gpio_set_pin_mode(&GREEN_LED_PIN, GPIO_MODE_OUT_PUSH_PULL);
    gpio_set_pin_mode(&BLUE_LED_PIN, GPIO_MODE_OUT_PUSH_PULL);

    leds_turn_green_off();
    leds_turn_blue_off();
}

void leds_turn_green_off()
{
    gpio_set_pin_low(&GREEN_LED_PIN);
}

void leds_turn_blue_off()
{
    gpio_set_pin_low(&BLUE_LED_PIN);
}

void leds_turn_green_on()
{
    gpio_set_pin_high(&GREEN_LED_PIN);
}

void leds_turn_blue_on()
{
    gpio_set_pin_high(&BLUE_LED_PIN);
}

