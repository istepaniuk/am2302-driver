#include "stm32f10x.h"
#include <stdbool.h>

bool finished = false;

void timer2_init()
{
    // Set timer
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    // 50000/24 should give us a 1us tick, 50ms total
    TIM_TimeBaseStructure.TIM_Period = 50000;
    TIM_TimeBaseStructure.TIM_Prescaler = 24;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);    
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void timer2_start()
{
    finished = false;
    TIM_SetCounter(TIM2, 0);
    TIM_Cmd(TIM2, ENABLE);
}

void timer2_stop()
{
    TIM_Cmd(TIM2, DISABLE);
}

bool timer2_has_finished()
{
    return finished;
}

int timer2_get_current_counter()
{
    TIM_GetCounter(TIM2)
    return 0;
}

void timer2_interrupt_handler()
{
    timer2_stop();
    finished = true;    
}
