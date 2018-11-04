#ifndef _BSP_BASETIME_H_
#define _BSP_BASETIME_H_

#include "stm32f10x.h"

#define  BASETIME_NUM       2
#define  BASETIME_ERROR     1
#define  BASETIME_SUCCESS   0

typedef struct
{
	unsigned char ID;
}
BASETIME_PARA_T;




unsigned char BaseTime_App_Handle(unsigned char sum);






#endif


