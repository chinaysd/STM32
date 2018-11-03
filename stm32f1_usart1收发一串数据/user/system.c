

#include "system.h"

unsigned char Temp;
extern unsigned char Rev_String[REV_BUF_SIZE];

void System_Init(void)
{
	TimeOutDet_Init();
	Usart1_Init(Baud);
}

void System_Handle(void)
{
	if(Serial_IF_OR_NO())
	{
		Temp = (unsigned char)Get_32bit(Rev_String[2],Rev_String[3]);
		memset(&Rev_String,0,sizeof(Rev_String));
		switch (Temp)
		{
			case 0x0011:
				          Protocol_Send(0xaa,0x55,0x01);
				          break;
			case 0x0002:
				          Protocol_Send(0xaa,0x55,0x02);
				          break;
			case 0x0004:
				          Protocol_Send(0xaa,0x55,0x04);
			           	break;
			case 0x0008:
				          Protocol_Send(0xaa,0x55,0x08);
				          break;
			default:
				          break;
		}
	}
}



