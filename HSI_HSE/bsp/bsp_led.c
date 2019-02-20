#include "bsp_led.h"


GPIO_InitTypeDef  GPIO_InitStruct;


void Led_Init(void)
{
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
     GPIO_InitStruct.GPIO_Pin = LED_PIN;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
     GPIO_Init(LED_PORT,&GPIO_InitStruct);
     LED_SET(0);
}





