#include "stm32f10x.h"

#define GPIO_MODE_IN_ANALOG      GPIO_Mode_AIN
#define GPIO_MODE_IN_FLOATING    GPIO_Mode_IN_FLOATING
#define GPIO_MODE_IN_PULL_DOWN   GPIO_Mode_IPD
#define GPIO_MODE_IN_PULL_UP     GPIO_Mode_IPU
#define GPIO_MODE_OUT_OPEN_DRAIN GPIO_Mode_Out_OD
#define GPIO_MODE_OUT_PUSH_PULL  GPIO_Mode_Out_PP
#define GPIO_MODE_AF_OPEN_DRAIN  GPIO_Mode_AF_ODC
#define GPIO_MODE_AF_PUSH_PULL   GPIO_Mode_AF_PP

#define GPIO_PIN_A0 GPIOA, GPIO_Pin_0
#define GPIO_PIN_A1 GPIOA, GPIO_Pin_1
#define GPIO_PIN_A2 GPIOA, GPIO_Pin_2
#define GPIO_PIN_A3 GPIOA, GPIO_Pin_3
#define GPIO_PIN_A4 GPIOA, GPIO_Pin_4
#define GPIO_PIN_A5 GPIOA, GPIO_Pin_5
#define GPIO_PIN_A6 GPIOA, GPIO_Pin_6
#define GPIO_PIN_A7 GPIOA, GPIO_Pin_7
#define GPIO_PIN_A8 GPIOA, GPIO_Pin_8
#define GPIO_PIN_A9 GPIOA, GPIO_Pin_9
#define GPIO_PIN_A10 GPIOA, GPIO_Pin_10
#define GPIO_PIN_A11 GPIOA, GPIO_Pin_11
#define GPIO_PIN_A12 GPIOA, GPIO_Pin_12
#define GPIO_PIN_A13 GPIOA, GPIO_Pin_13
#define GPIO_PIN_A14 GPIOA, GPIO_Pin_14
#define GPIO_PIN_A15 GPIOA, GPIO_Pin_15

#define GPIO_PIN_B0 GPIOB, GPIO_Pin_0
#define GPIO_PIN_B1 GPIOB, GPIO_Pin_1
#define GPIO_PIN_B2 GPIOB, GPIO_Pin_2
#define GPIO_PIN_B3 GPIOB, GPIO_Pin_3
#define GPIO_PIN_B4 GPIOB, GPIO_Pin_4
#define GPIO_PIN_B5 GPIOB, GPIO_Pin_5
#define GPIO_PIN_B6 GPIOB, GPIO_Pin_6
#define GPIO_PIN_B7 GPIOB, GPIO_Pin_7
#define GPIO_PIN_B8 GPIOB, GPIO_Pin_8
#define GPIO_PIN_B9 GPIOB, GPIO_Pin_9

#define GPIO_PIN_C0 GPIOC, GPIO_Pin_0
#define GPIO_PIN_C1 GPIOC, GPIO_Pin_1
#define GPIO_PIN_C2 GPIOC, GPIO_Pin_2
#define GPIO_PIN_C3 GPIOC, GPIO_Pin_3
#define GPIO_PIN_C4 GPIOC, GPIO_Pin_4
#define GPIO_PIN_C5 GPIOC, GPIO_Pin_5
#define GPIO_PIN_C6 GPIOC, GPIO_Pin_6
#define GPIO_PIN_C7 GPIOC, GPIO_Pin_7
#define GPIO_PIN_C8 GPIOC, GPIO_Pin_8
#define GPIO_PIN_C9 GPIOC, GPIO_Pin_9
#define GPIO_PIN_C10 GPIOC, GPIO_Pin_10
#define GPIO_PIN_C11 GPIOC, GPIO_Pin_11
#define GPIO_PIN_C12 GPIOC, GPIO_Pin_12
#define GPIO_PIN_C13 GPIOC, GPIO_Pin_13
#define GPIO_PIN_C14 GPIOC, GPIO_Pin_14
#define GPIO_PIN_C15 GPIOC, GPIO_Pin_15

#define gpio_set_pin_high(PIN) GPIO_WriteBit(PIN, 1);

#define gpio_set_pin_low(PIN) GPIO_WriteBit(PIN, 0);

#define gpio_get_pin_state(PIN) GPIO_ReadInputDataBit(PIN)

void gpio_set_pin_mode(GPIO_TypeDef* port, uint16_t pin, uint16_t mode);
