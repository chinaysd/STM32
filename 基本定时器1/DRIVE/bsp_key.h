#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_

#include "stm32f10x.h"

#define KEY_ENABLE      1
#define KEY_DISABLE     0

#define KEY_DOWN_TRUE   1
#define KEY_UP_FALSE    0

#if KEY_ENABLE
#define KEY_PORT        GPIOA
#define KEY_PIN         GPIO_Pin_0
#endif

void Key_Init(void);

unsigned char Key_Down(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);



#endif
