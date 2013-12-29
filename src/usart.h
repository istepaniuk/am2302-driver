#include "stm32f10x.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <sys/times.h>

void usart_putc(uint8_t ch);
void usart_puts(char *ptr);
int _write(int file, char *ptr, int len);
void init_usart();