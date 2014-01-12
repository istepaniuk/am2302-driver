#include "stm32f10x.h"
#include "platform.h"
#include "interrupts.h"

static const uint16_t pins[] = 
    {
        GPIO_Pin_0,GPIO_Pin_1,GPIO_Pin_2,GPIO_Pin_3,
        GPIO_Pin_4,GPIO_Pin_5,GPIO_Pin_6,GPIO_Pin_7,
        GPIO_Pin_8,GPIO_Pin_9,GPIO_Pin_10,GPIO_Pin_11,
        GPIO_Pin_12,GPIO_Pin_13,GPIO_Pin_14,GPIO_Pin_15
    }; 

static void setup_interrupt_controller(uint16_t pin)
{
    int exti_channel;
    if(pin == GPIO_Pin_0) exti_channel = EXTI0_IRQn;
    if(pin == GPIO_Pin_10) exti_channel = EXTI15_10_IRQn;
    if(pin == GPIO_Pin_11) exti_channel = EXTI15_10_IRQn;
    if(pin == GPIO_Pin_12) exti_channel = EXTI15_10_IRQn;
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = exti_channel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void gpio_set_interrupt_on_rising(GPIO_TypeDef* port, uint16_t pin, void* callback)
{
    uint32_t exti_line;
    uint8_t port_source;
    uint8_t pin_source;
    int i;
    for (i = 0; i < 15; i++) 
    {
        if(pins[i] == pin) 
        {
            pin_source = i;
            exti_line = pin;
            break;
        }
    }       
    
    if(port == GPIOA) port_source = GPIO_PortSourceGPIOA;
    if(port == GPIOB) port_source = GPIO_PortSourceGPIOB;
    if(port == GPIOC) port_source = GPIO_PortSourceGPIOC;
        
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = exti_line;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    
    GPIO_EXTILineConfig(port_source, pin_source);
    setup_interrupt_controller(pin);
    
    set_exti_line_interrupt_callback(exti_line, callback);
}

void gpio_set_pin_mode(GPIO_TypeDef* port, uint16_t pin, uint16_t mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = mode;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(port, &GPIO_InitStructure);
}
