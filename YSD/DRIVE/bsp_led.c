#include "bsp_led.h"

void Led1_Open(void)
{
  GPIO_ResetBits(LED1_PORT,LED1_PIN);
}

void Led1_Close(void)
{
	GPIO_SetBits(LED1_PORT,LED1_PIN);
}

void Led2_Open(void)
{
	GPIO_ResetBits(LED2_PORT,LED2_PIN);
}

void Led2_Close(void)
{
	GPIO_SetBits(LED2_PORT,LED2_PIN);
}

void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct[2];
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStruct[0].GPIO_Pin = LED1_PIN;
	GPIO_InitStruct[0].GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct[0].GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_InitStruct[1].GPIO_Pin = LED2_PIN;
	GPIO_InitStruct[1].GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct[1].GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(LED1_PORT,&GPIO_InitStruct[0]);
	GPIO_Init(LED2_PORT,&GPIO_InitStruct[1]);
	GPIO_SetBits(LED1_PORT,LED1_PIN);
	GPIO_SetBits(LED2_PORT,LED2_PIN);	
}



