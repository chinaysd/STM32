


#include "hal_led.h"




unsigned char Hal_Led_Init(unsigned char sum)
{
	static unsigned char i;
	if(sum > LED_NUM)
		return LED_ERROR;
	for(i = 0; i < sum; i ++)
	{
		if(BackCall_LED(LED_NUM,Led_App_Handle) != LED_SUCCESS)
			break;
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

unsigned char Hal_Led_Status(unsigned char id,unsigned char status)
{
	if(id > LED_NUM)
		return LED_ERROR;
	if(id == 0)
	{
		if(status == 0)
		{
			GPIO_SetBits(LED1_PORT,LED1_PIN);
		}
		else if(status == 1)
		{
			GPIO_ResetBits(LED1_PORT,LED1_PIN);
		}
	}
	else if(id == 1)
	{
		if(status == 0)
		{
			GPIO_SetBits(LED2_PORT,LED2_PIN);
		}
		else if(status == 1)
		{
			GPIO_ResetBits(LED2_PORT,LED2_PIN);
		}
	}
	return LED_ERROR;
}




