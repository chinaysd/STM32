#ifndef _SYSTEM_H_
#define _SYSTEM_H_




#include "stm32f10x.h"


//#include "bsp_led.h"

#include "hal_led.h"
#include "bsp_basetime.h"
#include "TimeOut.h"
#include "bsp_key.h"
#include "bsp_usart1.h"
#include "string.h"
#include "stdio.h"


#define OnLine_Time       1000

#define TimeOut
void System_Init(void);
void System_Handle(void);





#endif



