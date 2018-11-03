#include "bsp_led.h"


LED_PARA_T Led_Para[LED_NUM];
GPIO_InitTypeDef GPIO_InitStruct;


unsigned char Led_Init(unsigned char id)
{
	if(id > LED_NUM)
		return LED_ERROR;
	if(id == 0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		GPIO_InitStruct.GPIO_Pin = LED1_PIN;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LED1_PORT,&GPIO_InitStruct);
		GPIO_SetBits(LED1_PORT,LED1_PIN);
		return LED_SUCCESS;
	}
	else if(id == 1)
	{
		GPIO_InitStruct.GPIO_Pin = LED2_PIN;
		GPIO_Init(LED2_PORT,&GPIO_InitStruct);
		GPIO_SetBits(LED2_PORT,LED2_PIN);
	  return LED_SUCCESS;
	}
	return LED_ERROR;
}


unsigned char Led_App_Init(LED_PARA_T *P)
{
	 unsigned char Led_Init(unsigned char ID);
	return Led_Init(P->ID);
}

unsigned char Led_App_Handle(unsigned char sum)
{
	static unsigned char i;
	if(sum > LED_NUM)
		return LED_ERROR;
	for(i = 0; i < sum; i ++)
	{
		Led_Para[i].ID = i;
		Led_App_Init(&Led_Para[i]);
	}
   if(i != sum)
	 {
		 return LED_ERROR;
	 }
	 else 
	 {
		 return LED_SUCCESS;
	 }
}




