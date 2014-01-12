#include "stm32f10x.h"
#include "interrupts.h"

#define EXTI_Lines15_10 EXTI_Line10 | EXTI_Line11 | EXTI_Line12 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15

static void default_handler(void) { }
static void (*exti_line0_interrupt_callback)()  = default_handler;
static void (*exti_line10_interrupt_callback)() = default_handler;
static void (*exti_line11_interrupt_callback)() = default_handler;
static void (*exti_line12_interrupt_callback)() = default_handler;
static void (*timer2_interrupt_callback)() = default_handler;

void set_exti_line_interrupt_callback(int line, void *callback)
{
    switch(line)
    {
        case EXTI_Line0:  exti_line0_interrupt_callback  = callback; break;
        case EXTI_Line10: exti_line10_interrupt_callback = callback; break;
        case EXTI_Line11: exti_line11_interrupt_callback = callback; break;
        case EXTI_Line12: exti_line12_interrupt_callback = callback; break;
    }
}

void set_timer2_interrupt_callback(void *callback)
{
    timer2_interrupt_callback = callback;
}

void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0) == RESET)
        return;
    exti_line0_interrupt_callback();
    EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line10) != RESET)
        exti_line10_interrupt_callback();
    if(EXTI_GetITStatus(EXTI_Line11) != RESET)
        exti_line11_interrupt_callback();
    if(EXTI_GetITStatus(EXTI_Line12) != RESET)
        exti_line12_interrupt_callback();
    EXTI_ClearITPendingBit(EXTI_Lines15_10);
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == RESET)
        return;
    timer2_interrupt_callback();
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void NMI_Handler(void) { }

void HardFault_Handler(void)
{
    while (1) { }
}

void MemManage_Handler(void)
{
    while (1) { }
}

void BusFault_Handler(void)
{
    while (1) { }
}

void UsageFault_Handler(void)
{
    while (1) { }
}

void SVC_Handler(void) { }

void DebugMon_Handler(void) { }

void PendSV_Handler(void) { }

void SysTick_Handler(void) { }

