#include "stm32f10x.h"
#include "platform.h"
#include "interrupts.h"

static void setup_interrupt_controller(uint16_t pin)
{
    int exti_channel;
    if(pin == GPIO_Pin_0) exti_channel = EXTI0_IRQn;
    if(pin == GPIO_Pin_9) exti_channel = EXTI9_5_IRQn;
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = exti_channel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void gpio_set_interrupt_on_rising(GPIO_TypeDef* port, uint16_t pin, void *callback)
{
    uint32_t exti_line;
    uint8_t port_source;
    uint8_t pin_source;
    void (*interrupt_service_setup_function)();
    
    if(pin == GPIO_Pin_0) 
    {
        exti_line = EXTI_Line0;
        port_source = GPIO_PortSourceGPIOA;
        pin_source = GPIO_PinSource0;
        interrupt_service_setup_function = set_exti_line0_interrupt_callback;
    }
    
    if(pin == GPIO_Pin_9)
    {
        exti_line = EXTI_Line9;
        port_source = GPIO_PortSourceGPIOB;
        pin_source = GPIO_PinSource9;
        interrupt_service_setup_function = set_exti_line9_interrupt_callback;
    }
        
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = exti_line;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    GPIO_EXTILineConfig(port_source, pin_source);
    setup_interrupt_controller(pin);
    interrupt_service_setup_function(callback);
}

void gpio_set_pin_mode(GPIO_TypeDef* port, uint16_t pin, uint16_t mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = mode;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(port, &GPIO_InitStructure);
}
