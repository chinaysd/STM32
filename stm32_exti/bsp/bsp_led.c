#include "bsp_led.h"

GPIO_InitTypeDef LED_GPIO_InitStruct;



void Led_Init(void)
{
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	 LED_GPIO_InitStruct.GPIO_Pin = LED_PIN;
	 LED_GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	 LED_GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	 GPIO_Init(LED_PORT,&LED_GPIO_InitStruct);
	 LED_SET(0);
}


