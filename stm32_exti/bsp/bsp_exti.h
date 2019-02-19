#ifndef _BSP_EXTI_H_
#define _BSP_EXTI_H_


#include "stm32f10x.h"



#define EXTI0_PORT     GPIOA
#define EXTI0_PIN       GPIO_Pin_0

#define EXTI1_PORT    GPIOC
#define EXTI1_PIN      GPIO_Pin_13







#if 1
void Exti_Config(void);
#else
void Exti_Init(void);
#endif


#endif


