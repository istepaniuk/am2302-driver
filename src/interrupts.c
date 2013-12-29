#include "interrupts.h"
#include "usart.h"
#include "timer.h"
#include "button.h"

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

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == RESET)
	    return;
    button_interrupt_handler();
  	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line9) == RESET)
	    return;
    am2302_interrupt_handler();
  	EXTI_ClearITPendingBit(EXTI_Line9);
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == RESET)
        return;
    timer2_interrupt_handler();
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}
