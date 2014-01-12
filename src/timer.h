#include <stdbool.h>

void timer2_init(void);
void timer2_start(void);
void timer2_stop(void);
bool timer2_has_finished(void);
int timer2_get_current_counter(void);
void timer2_interrupt_handler(void);
