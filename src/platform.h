#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "stm32f10x.h"

#define GPIO_MODE_IN_ANALOG      GPIO_Mode_AIN
#define GPIO_MODE_IN_FLOATING    GPIO_Mode_IN_FLOATING
#define GPIO_MODE_IN_PULL_DOWN   GPIO_Mode_IPD
#define GPIO_MODE_IN_PULL_UP     GPIO_Mode_IPU
#define GPIO_MODE_OUT_OPEN_DRAIN GPIO_Mode_Out_OD
#define GPIO_MODE_OUT_PUSH_PULL  GPIO_Mode_Out_PP
#define GPIO_MODE_AF_OPEN_DRAIN  GPIO_Mode_AF_ODC
#define GPIO_MODE_AF_PUSH_PULL   GPIO_Mode_AF_PP

#define GPIO_PIN_A0  (pin_def_t) { GPIOA, GPIO_Pin_0  }
#define GPIO_PIN_A1  (pin_def_t) { GPIOA, GPIO_Pin_1  }
#define GPIO_PIN_A2  (pin_def_t) { GPIOA, GPIO_Pin_2  }
#define GPIO_PIN_A3  (pin_def_t) { GPIOA, GPIO_Pin_3  }
#define GPIO_PIN_A4  (pin_def_t) { GPIOA, GPIO_Pin_4  }
#define GPIO_PIN_A5  (pin_def_t) { GPIOA, GPIO_Pin_5  }
#define GPIO_PIN_A6  (pin_def_t) { GPIOA, GPIO_Pin_6  }
#define GPIO_PIN_A7  (pin_def_t) { GPIOA, GPIO_Pin_7  }
#define GPIO_PIN_A8  (pin_def_t) { GPIOA, GPIO_Pin_8  }
#define GPIO_PIN_A9  (pin_def_t) { GPIOA, GPIO_Pin_9  }
#define GPIO_PIN_A10 (pin_def_t) { GPIOA, GPIO_Pin_10 }
#define GPIO_PIN_A11 (pin_def_t) { GPIOA, GPIO_Pin_11 }
#define GPIO_PIN_A12 (pin_def_t) { GPIOA, GPIO_Pin_12 }
#define GPIO_PIN_A13 (pin_def_t) { GPIOA, GPIO_Pin_13 }
#define GPIO_PIN_A14 (pin_def_t) { GPIOA, GPIO_Pin_14 }
#define GPIO_PIN_A15 (pin_def_t) { GPIOA, GPIO_Pin_15 }

#define GPIO_PIN_B0  (pin_def_t) { GPIOB, GPIO_Pin_0  }
#define GPIO_PIN_B1  (pin_def_t) { GPIOB, GPIO_Pin_1  }
#define GPIO_PIN_B2  (pin_def_t) { GPIOB, GPIO_Pin_2  }
#define GPIO_PIN_B3  (pin_def_t) { GPIOB, GPIO_Pin_3  }
#define GPIO_PIN_B4  (pin_def_t) { GPIOB, GPIO_Pin_4  }
#define GPIO_PIN_B5  (pin_def_t) { GPIOB, GPIO_Pin_5  }
#define GPIO_PIN_B6  (pin_def_t) { GPIOB, GPIO_Pin_6  }
#define GPIO_PIN_B7  (pin_def_t) { GPIOB, GPIO_Pin_7  }
#define GPIO_PIN_B8  (pin_def_t) { GPIOB, GPIO_Pin_8  }
#define GPIO_PIN_B9  (pin_def_t) { GPIOB, GPIO_Pin_9  }
#define GPIO_PIN_B10 (pin_def_t) { GPIOB, GPIO_Pin_10 }
#define GPIO_PIN_B11 (pin_def_t) { GPIOB, GPIO_Pin_11 }
#define GPIO_PIN_B12 (pin_def_t) { GPIOB, GPIO_Pin_12 }
#define GPIO_PIN_B13 (pin_def_t) { GPIOB, GPIO_Pin_13 }
#define GPIO_PIN_B14 (pin_def_t) { GPIOB, GPIO_Pin_14 }
#define GPIO_PIN_B15 (pin_def_t) { GPIOB, GPIO_Pin_15 }

#define GPIO_PIN_C0  (pin_def_t) { GPIOC, GPIO_Pin_0  }
#define GPIO_PIN_C1  (pin_def_t) { GPIOC, GPIO_Pin_1  }
#define GPIO_PIN_C2  (pin_def_t) { GPIOC, GPIO_Pin_2  }
#define GPIO_PIN_C3  (pin_def_t) { GPIOC, GPIO_Pin_3  }
#define GPIO_PIN_C4  (pin_def_t) { GPIOC, GPIO_Pin_4  }
#define GPIO_PIN_C5  (pin_def_t) { GPIOC, GPIO_Pin_5  }
#define GPIO_PIN_C6  (pin_def_t) { GPIOC, GPIO_Pin_6  }
#define GPIO_PIN_C7  (pin_def_t) { GPIOC, GPIO_Pin_7  }
#define GPIO_PIN_C8  (pin_def_t) { GPIOC, GPIO_Pin_8  }
#define GPIO_PIN_C9  (pin_def_t) { GPIOC, GPIO_Pin_9  }
#define GPIO_PIN_C10 (pin_def_t) { GPIOC, GPIO_Pin_10 }
#define GPIO_PIN_C11 (pin_def_t) { GPIOC, GPIO_Pin_11 }
#define GPIO_PIN_C12 (pin_def_t) { GPIOC, GPIO_Pin_12 }
#define GPIO_PIN_C13 (pin_def_t) { GPIOC, GPIO_Pin_13 }
#define GPIO_PIN_C14 (pin_def_t) { GPIOC, GPIO_Pin_14 }
#define GPIO_PIN_C15 (pin_def_t) { GPIOC, GPIO_Pin_15 }

typedef struct pin_def_t {
    GPIO_TypeDef* port;
    uint16_t number;
} pin_def_t;

void gpio_set_pin_mode(pin_def_t* pin, uint16_t mode);
void gpio_set_interrupt_on_rising(pin_def_t* pin, void* callback);
int gpio_get_pin_state(pin_def_t* pin);
void gpio_set_pin_high(pin_def_t* pin);
void gpio_set_pin_low(pin_def_t* pin);

#endif