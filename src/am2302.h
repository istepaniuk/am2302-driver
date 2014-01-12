#include <stdbool.h>
#include <stdint.h>

struct am2302_sensor_data_t
{
    uint16_t humidity;
    int16_t temperature;
};

void am2302_start_acquire(int device_index);
bool am2302_acquire_has_finished(void);
struct am2302_sensor_data_t am2302_get_sensor_data(void);
void am2302_init(void);