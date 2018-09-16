#include "system.h"
static uint Cnt;
extern volatile unsigned int timer;
		
void System_Init(void)
{
	Led_Init();
	Key_Init();
	BaseTime_Config();
}

void System_Handle(void)
{	
	if(Key_Down(KEY_PORT,KEY_PIN))
	{	
		++ Cnt;
		if(Cnt & 0x01)
		{
			Led1_Open();
	    Led2_Open();
		}
		else
		{
			Led1_Close();
	    Led2_Close();
		}
		while(Key_Down(KEY_PORT,KEY_PIN));
	}
	if(timer > 500)
	{
		++ Cnt;
		if(Cnt & 0x01)
		{
			Led1_Open();
	    Led2_Open();
		}
		else
		{
			Led1_Close();
	    Led2_Close();
		}
		timer = 0;
	}
}


