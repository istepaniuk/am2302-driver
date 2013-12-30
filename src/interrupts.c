#include "stm32f10x.h"
#include "interrupts.h"

static void default_handler(void) { }
static void (*exti_line0_interrupt_callback)() = default_handler;
static void (*exti_line9_interrupt_callback)() = default_handler;
static void (*timer2_interrupt_callback)() = default_handler;

void set_exti_line0_interrupt_callback(void *callback)
{
    exti_line0_interrupt_callback = callback;
}

void set_exti_line9_interrupt_callback(void *callback)
{
    exti_line9_interrupt_callback = callback;
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

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line9) == RESET)
	    return;
    exti_line9_interrupt_callback();
  	EXTI_ClearITPendingBit(EXTI_Line9);
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

