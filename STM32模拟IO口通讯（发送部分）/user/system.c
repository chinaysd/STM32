

#include "system.h"


TIMEOUT_PARA TimeOut_Para[2];

void System_Init(void)
{
	TimeOutDet_Init();
	Hal_Led_Init(LED_NUM);
	BaseTime_App_Handle(BASETIME_NUM);
	BackCall_Key(KEY_NUM,Key_App_Handle);
}

void System_Handle(void)
{
	#ifdef TimeOut
	static unsigned char Counts;
	if(TimeOutDet_Check(&TimeOut_Para[0]))
  {
		TimeOut_Record(&TimeOut_Para[0],OnLine_Time);
		++ Counts;
		if(Counts & 0x01)
		{
			Hal_Led_Status(1,1);
		}
		else 
		{
			Hal_Led_Status(1,0);
		}
	}
  #endif  
	
}




