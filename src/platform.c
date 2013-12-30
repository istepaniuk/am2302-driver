#include "stm32f10x.h"
#include "platform.h"

#define GPIO_MODE_IN_ANALOG      GPIO_Mode_AIN,
#define GPIO_MODE_IN_FLOATING    GPIO_Mode_IN_FLOATING,
#define GPIO_MODE_IN_PULL_DOWN   GPIO_Mode_IPD,
#define GPIO_MODE_IN_PULL_UP     GPIO_Mode_IPU,
#define GPIO_MODE_OUT_OPEN_DRAIN GPIO_Mode_Out_OD,
#define GPIO_MODE_OUT_PUSH_PULL  GPIO_Mode_Out_PP,
#define GPIO_MODE_AF_OPEN_DRAIN  GPIO_Mode_AF_ODC,
#define GPIO_MODE_AF_PUSH_PULL   GPIO_Mode_AF_PP

void gpio_set_pin_mode(uint16_t pin, gpio_pin_mode mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = mode;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}
