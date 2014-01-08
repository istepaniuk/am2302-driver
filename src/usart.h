#include "stm32f10x.h"

void usart_putc(uint8_t ch);
void usart_puts(char *ptr);
void usart_init();
void printhex(uint16_t n);
void printint(uint16_t n);