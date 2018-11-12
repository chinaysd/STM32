

#include "system.h"
extern unsigned int  Temp;
extern unsigned char Rev_String_Data[BUF_SIZE];


TIMEOUT_PARA TimeOut_Para[2];

void Rev_Serial_Handle(void)
{
	if(Rev_Serial_If())
	{
		Temp = (unsigned int)(Get_32Bit(Rev_String_Data[2],Rev_String_Data[3]));
		memset(&Rev_String_Data,0,sizeof(Rev_String_Data));
		switch (Temp)
		{
			case 0x0001:
								 Hal_Led_Status(1,1);
								 break;
			case 0x0002:
								 Hal_Led_Status(1,0);
								 break;
			case 0x0004:
								 
								 break;
			case 0x0008:
									
								 break;
			default:
								 break;
		}
	}
}

void System_Init(void)
{
	TimeOutDet_Init();
	Hal_Led_Init(LED_NUM);
	BaseTime_App_Handle(BASETIME_NUM);
	BackCall_Key(KEY_NUM,Key_App_Handle);
	Usart1_App_Handle(USART1_CONFIG_PROCESS);
}

void System_Handle(void)
{
	#ifdef TimeOut
	static unsigned char Counts;
	if(TimeOutDet_Check(&TimeOut_Para[0]))
  {
		TimeOut_Record(&TimeOut_Para[0],OnLine_Time);
		Rev_Serial_Handle();
		++ Counts;
		if(Counts & 0x01)
		{
			//Protocol_Send(0x55,0xff,0x01);
		}
		else 
		{
			//Protocol_Send(0x55,0xff,0x02);
		}
	}
  #endif 
  
  	
}




