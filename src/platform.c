#include "stm32f10x.h"
#include "platform.h"
#include "interrupts.h"

int exti_channels[];
int exti_lines[];


static void setup_interrupt_controller(uint16_t pin)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = exti_channels[pin];
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void gpio_set_interrupt_on_rising(GPIO_TypeDef* port, uint16_t pin, void *callback){

    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = exti_lines[pin];
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    setup_interrupt_controller(pin);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
}

void gpio_set_pin_mode(GPIO_TypeDef* port, uint16_t pin, uint16_t mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = mode;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(port, &GPIO_InitStructure);
}
