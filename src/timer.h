#include <stdbool.h>

void timer2_init();
void timer2_start();
void timer2_stop();
bool timer2_has_finished();
int timer2_get_current_counter();
void timer2_interrupt_handler();
