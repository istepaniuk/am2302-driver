#include <stdbool.h>
#include "am2302.h"
#include "interrupts.h"
#include "usart.h"
#include "timer.h"
#include "platform.h"
#include "hardware.h"

#define AM_HI_BIT_THRESHOLD_TIME 100
#define AM_VALID_DATA_START_TIME 250
#define AM_DATA_SIZE 40
#define AM_HUMIDITY_DATA_OFFSET 0
#define AM_TEMPERATURE_DATA_OFFSET 16
#define AM_PARITY_DATA_OFFSET 32
#define CHAR_BIT 8

static bool acquiring = false;
static int bit_position;
static int last_timestamp;
uint64_t raw_data;

struct am2302_sensor_data
{
    uint16_t humidity;
    int16_t temperature;
};

static inline void wait_1ms()
{
    int loops = 35200;
    while(loops--){ };
}

static void interrupt_handler()
{
    if(!acquiring)
        return;
    int timestamp = timer2_get_current_counter();
    int bit_value = (timestamp - last_timestamp) > AM_HI_BIT_THRESHOLD_TIME;
    last_timestamp = timestamp;
    
    if (timestamp > AM_VALID_DATA_START_TIME)
        raw_data |= (uint64_t) bit_value << bit_position++;
}

static inline void reset()
{
    bit_position = 0;
    last_timestamp = 0;
    raw_data = 0;
    acquiring = false;
}

static inline int16_t get_2complement_from_signed_magnitude(uint16_t x) 
{
    int16_t sign_mask = 0x8FFF;
    int16_t positive_part = x & sign_mask;
    bool is_negative = (~sign_mask & x);
    return is_negative ? -positive_part : positive_part;
}

static uint16_t get_int16_from_bits(uint64_t bits, int offset)
{
    int i;
    int size = sizeof(uint16_t) * CHAR_BIT;
    int ouput_bit_pos = size;
    uint16_t result = 0;
    for (i = 0; i < size; i++)
    {
        uint64_t bit_mask = ((uint64_t) 1) << (offset + i);
        int bit = (bits & bit_mask) > 0;
        result |= bit << --ouput_bit_pos;
    }
    return result;
}

static inline struct am2302_sensor_data get_converted_sensor_data()
{
    struct am2302_sensor_data sdata;
    sdata.humidity = get_int16_from_bits(raw_data, AM_HUMIDITY_DATA_OFFSET);
    sdata.temperature = get_int16_from_bits(raw_data, AM_TEMPERATURE_DATA_OFFSET);
    sdata.temperature = get_2complement_from_signed_magnitude(sdata.temperature);
    return sdata;
}

static inline uint8_t calculate_checksum()
{
    int i; 
    uint8_t checksum = 0;
    for (i = 0; i < 4; i++)
        checksum += get_int16_from_bits(raw_data, i * CHAR_BIT) >> CHAR_BIT;
    return checksum;
}

static inline bool has_parity_errors()
{
    uint8_t parity = get_int16_from_bits(raw_data, AM_PARITY_DATA_OFFSET) >> CHAR_BIT;
    return parity != calculate_checksum();
}

static inline void send_start_signal()
{
    gpio_set_pin_mode(AM2302_PIN, GPIO_MODE_OUT_PUSH_PULL);
    gpio_set_pin_low(AM2302_PIN);
    wait_1ms();
    gpio_set_pin_high(AM2302_PIN);
    gpio_set_pin_mode(AM2302_PIN, GPIO_MODE_IN_FLOATING);
}

void am2302_acquire()
{
    reset();
    send_start_signal();  
    timer2_start();
    acquiring = true;
    while(!timer2_has_finished() && bit_position < AM_DATA_SIZE) { }
    acquiring = false;
    timer2_stop();
    
    if(bit_position < AM_DATA_SIZE)
        usart_puts("Timeout\n");
    
    if(has_parity_errors())
        usart_puts("Invalid data\n");
    
    struct am2302_sensor_data a = get_converted_sensor_data();
    
    usart_putc('h');
    printint(a.humidity);
    usart_putc('t');
    printint(a.temperature);
    
    usart_putc('\n');
}

void am2302_init()
{
    timer2_init();
    gpio_set_interrupt_on_rising(AM2302_PIN, interrupt_handler);
}
