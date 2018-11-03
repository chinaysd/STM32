#include "bsp_key.h"


void Key_Init(void)
{
	GPIO_InitTypeDef KEY_InitStruct[2];
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	KEY_InitStruct[0].GPIO_Pin = KEY_PIN;
	KEY_InitStruct[0].GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(KEY_PORT,&KEY_InitStruct[0]);
}

unsigned char Key_Down(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if(KEY_DOWN_TRUE == GPIO_ReadInputDataBit(GPIOx,GPIO_Pin))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
