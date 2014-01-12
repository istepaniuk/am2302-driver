#include <stdbool.h>
#include <limits.h>
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

#define element_count(A) (sizeof(A) / sizeof(A[0]))

static bool acquiring = false;
static int bit_position;
static int last_timestamp;
static uint64_t raw_data;

static inline void wait_1ms(void)
{
    int loops = 35200;
    while(loops--) { };
}

static void interrupt_handler(void)
{
    if(!acquiring)
        return;
    int timestamp = timer2_get_current_counter();
    int bit_value = (timestamp - last_timestamp) > AM_HI_BIT_THRESHOLD_TIME;
    if (timestamp > AM_VALID_DATA_START_TIME)
        raw_data |= (uint64_t) bit_value << bit_position++;
    last_timestamp = timestamp;
}

static inline int16_t get_2complement_from_signed_magnitude(uint16_t x) 
{
    int16_t sign_mask = 0x7FFF;
    int16_t magintude = x & sign_mask;
    bool is_negative = x & ~sign_mask;
    return is_negative ? -magintude : magintude;
}

static uint16_t get_int16_from_bits(uint64_t bits, int offset)
{
    int size = sizeof(uint16_t) * CHAR_BIT;
    int ouput_bit_pos = size;
    uint16_t result = 0;
    for (int i = 0; i < size; i++)
    {
        uint64_t bit_mask = ((uint64_t) 1) << (offset + i);
        int bit = (bits & bit_mask) > 0;
        result |= bit << --ouput_bit_pos;
    }
    return result;
}

static inline struct am2302_sensor_data_t get_converted_sensor_data(void)
{
    struct am2302_sensor_data_t sdata;
    sdata.humidity = get_int16_from_bits(raw_data, AM_HUMIDITY_DATA_OFFSET);
    sdata.temperature = get_int16_from_bits(raw_data, AM_TEMPERATURE_DATA_OFFSET);
    sdata.temperature = get_2complement_from_signed_magnitude(sdata.temperature);
    return sdata;
}

static inline uint8_t calculate_checksum(void)
{
    uint8_t checksum = 0;
    for (int i = 0; i < 4; i++)
        checksum += get_int16_from_bits(raw_data, i * CHAR_BIT) >> CHAR_BIT;
    return checksum;
}

static inline bool has_parity_errors(void)
{
    uint8_t parity = get_int16_from_bits(raw_data, AM_PARITY_DATA_OFFSET) >> CHAR_BIT;
    return parity != calculate_checksum();
}

static inline void send_start_signal(int device_index)
{
    pin_def_t* device_pin = &AM2302_PINS[device_index];
    gpio_set_pin_mode(device_pin, GPIO_MODE_OUT_PUSH_PULL);
    gpio_set_pin_low(device_pin);
    wait_1ms();
    gpio_set_pin_high(device_pin);
    gpio_set_pin_mode(device_pin, GPIO_MODE_IN_FLOATING);
}

void am2302_start_acquire(int device_index)
{
    if(acquiring)
        return;
    last_timestamp = 0;
    bit_position = 0;
    raw_data = 0;
    send_start_signal(device_index); 
    timer2_start();
    acquiring = true;
}

bool am2302_acquire_has_finished(void)
{
    if(timer2_has_finished() || bit_position >= AM_DATA_SIZE) 
    {
        acquiring = false;
        timer2_stop();
    }
    return !acquiring;
}

struct am2302_sensor_data_t am2302_get_sensor_data()
{
    //TODO: Move this error result to the struct
    if(acquiring)
        usart_puts("BUSY\n");
    else if(!acquiring && bit_position < AM_DATA_SIZE)
        usart_puts("TIMEOUT\n");
    else if(has_parity_errors())
        usart_puts("PARITY ERROR\n");
    
    return get_converted_sensor_data();
}

void am2302_init(void)
{
    pin_def_t* pins = &AM2302_PINS;
    for(int i = 0; i < element_count(AM2302_PINS) ;i++)
        gpio_set_interrupt_on_rising(&pins[i], interrupt_handler);
    timer2_init();
}
