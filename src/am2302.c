#include <stdbool.h>
#include "interrupts.h"
#include "usart.h"
#include "timer.h"

bool acquiring = false;
int thecount = 0;
bool ready = true;

void setup_interrupt()
{
	NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void delay(int count)
{
    while(count--){};
}

void am2302_init()
{
    setup_interrupt();
}

void am2302_acquire(void)
{
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

        timer2_start();
        while(!ready && (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 1)) { }
        while(!ready && (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0)) { }

        acquiring = true;
    }

    EXTI_ClearITPendingBit(EXTI_Line0);
}

void am2302_interrupt_handler(void)
{
    if(acquiring)
    { 
        thecount++;
	}
}

void am2302_finished(void)
{
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
