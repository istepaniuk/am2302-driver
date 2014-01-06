#include "stm32f10x.h"
//#include <stdio.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <sys/times.h>


void usart_putc(uint8_t ch)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {}
    USART_SendData(USART1, (uint8_t) ch);
    //Loop until the end of transmission
    //while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}
}

void usart_puts(volatile char *s)
{
    while(*s){
        usart_putc(*s);
        *s++;
    }
}

int _write(int file, char *ptr, int len) {
    int n;
    switch (file) {
    case STDOUT_FILENO: //stdout
        for (n = 0; n < len; n++) {
            usart_putc(*ptr++ & (uint16_t)0x01FF);
        }
        break;
    case STDERR_FILENO: //stderr 
        for (n = 0; n < len; n++) {
            usart_putc(*ptr++ & (uint16_t)0x01FF);
        }
        break;
    default:
        //errno = EBADF;
        return -1;
    }
    return len;
}

void printf(char *ptr)
{
    usart_puts(ptr);
}

void usart_init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 

    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure USART Rx as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* USART configuration */
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    
    /* Enable USART */
    USART_Cmd(USART1, ENABLE);

    printf("USART Initialized.\n");
}

void reverse(char* str, int length){
    int i = 0, j = length-1;
    char tmp;
    while (i < j) {
        tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++; j--;
    }
}

int itoa(int n, char* out)
{
    int sign = n < 0? 1: 0;
    int i = 0;
    if (n == 0) {
        out[i++] = '0';
    } else if (n < 0) {
        out[i++] = '-';
        n = -n;
    }
    while (n > 0) {
        out[i++] = '0' + n % 10;
        n /= 10;
    }
    out[i] = '\0';
    reverse(out + sign, i - sign);
    return 0;
}

void tohex(uint32_t n, char* out)
{
    int i;
    char* hex = "0123456789ABCDEF";
    
    out[0] = '0';
    out[1] = 'x';
    for(i = 2; i < 10; i++)
        out[i] = hex[(n >> ((9-i) * 4)) % 16];
    out[10] = '\0';
}

void dump32h(uint32_t n)
{
    char str_v[12];
    tohex(n, str_v);
    usart_puts(str_v);
    usart_putc('\n');
}
