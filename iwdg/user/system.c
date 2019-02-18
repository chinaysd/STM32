#include "system.h"



void Delay_Time(unsigned int Time)
{
	static unsigned int i,j;
	for(i = Time; i > 0; i--)
	{
		for(j = 200; j > 0; j --);
	}
}


void System_Init(void)
{
     Led_Init();
     Iwdg_Init();
}

void System_Handle(void)
{
	Iwdg_Feed();
	LED_SET(1);
	Delay_Time(1000);
	LED_SET(0);
	Delay_Time(1000);
}



