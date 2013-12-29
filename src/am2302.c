#include "stm32f10x_it.h"
#include "usart.h"

enum { false, true };

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

void delay(unsigned long delay)
{
    while(delay) {
        delay--;
    }
}

int acquiring = false;
int ready = true;

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == RESET)
	    return;


    if(ready)
    {
        ready = false;
        acquiring = false;
        GPIO_WriteBit(GPIOC, GPIO_Pin_8, 1);
        
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);        
       
        GPIO_WriteBit(GPIOB, GPIO_Pin_9, 1);
        delay(50000);
        GPIO_WriteBit(GPIOB, GPIO_Pin_9, 0);
        delay(25000);
        GPIO_WriteBit(GPIOB, GPIO_Pin_9, 1);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);        

        TIM_Cmd(TIM2, ENABLE);
        TIM_SetCounter(TIM2, 0);
        while(!ready && (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 1)) { }
        while(!ready && (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0)) { }

        TIM_SetCounter(TIM2, 0);
        acquiring = true;
    }

    EXTI_ClearITPendingBit(EXTI_Line0);
}

int thecount = 0;

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line9) == RESET)
	    return;

    if(acquiring)
    { 
        thecount++;
        GPIOC->ODR ^= GPIO_Pin_9;
	}

  	EXTI_ClearITPendingBit(EXTI_Line9);
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == RESET)
        return;
    if(!acquiring)
        return;

    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    GPIO_WriteBit(GPIOC, GPIO_Pin_8, 0);
    TIM_Cmd(TIM2, DISABLE);
    delay(500000);
    acquiring = false;
    ready = true;
    while(thecount) {
        usart_putc('X');
        thecount--;
    }
}
