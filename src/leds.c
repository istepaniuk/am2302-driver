#include "stm32f10x.h"
#include "leds.h"

void leds_init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    leds_green_off();
    leds_blue_off();
}

void leds_green_off()
{
    GPIO_WriteBit(GPIOC, GPIO_Pin_9, 0);
}

void leds_blue_off()
{
    GPIO_WriteBit(GPIOC, GPIO_Pin_8, 0);
}

void leds_green_on()
{
    GPIO_WriteBit(GPIOC, GPIO_Pin_9, 1);
}

void leds_blue_on()
{
    GPIO_WriteBit(GPIOC, GPIO_Pin_8, 1);
}

