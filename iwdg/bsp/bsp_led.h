#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#include "stm32f10x.h"


#define LED_PORT    GPIOC
#define LED_PIN      GPIO_Pin_2

#define LED_SET(X)  ((X)?(GPIO_ResetBits(GPIOC, GPIO_Pin_2)):(GPIO_SetBits(GPIOC, GPIO_Pin_2)))



void Led_Init(void);




#endif



