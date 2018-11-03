#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#include "stm32f10x.h"

#define LED_ENABLE      1
#define LED_DISABLE     0

#if LED_ENABLE
#define LED1_PORT     GPIOC
#define LED1_PIN      GPIO_Pin_2

#define LED2_PORT     GPIOC
#define LED2_PIN      GPIO_Pin_3
#endif

void Led1_Open(void);
void Led1_Close(void);
void Led2_Open(void);
void Led2_Close(void);
void Led_Init(void);

#endif

