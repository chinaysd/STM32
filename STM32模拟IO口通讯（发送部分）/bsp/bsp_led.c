#include "bsp_led.h"

LED_PARA_T   Led_Para[LED_NUM];
GPIO_InitTypeDef LED_InitStruct;


unsigned char Led_Init(unsigned char id)
{
	if(id > LED_NUM)
		return LED_ERROR;
	if(id == 0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		LED_InitStruct.GPIO_Pin = LED1_PIN;
		LED_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		LED_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(LED1_PORT, &LED_InitStruct);
		return LED_SUCCESS;
	}
	else if(id == 1)
	{
		LED_InitStruct.GPIO_Pin = LED2_PIN;
		GPIO_Init(LED2_PORT, &LED_InitStruct);
		return LED_SUCCESS;
	}
	return LED_ERROR;
}




unsigned char Led_App_Init(LED_PARA_T *p)
{
   unsigned char Led_Init(unsigned char ID);
	 return Led_Init(p->ID);
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

unsigned char BackCall_LED(unsigned char n,unsigned char (*ptr)(unsigned char))
{
	(*ptr)(n);
	return LED_SUCCESS;
}






	