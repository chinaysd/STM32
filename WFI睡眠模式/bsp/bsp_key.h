#ifndef _BSP_KEY_H_
#define _BSP_KEY_H_


#include "stm32f10x.h"

#define KEY_NUM      2
#define KEY_ERROR    1
#define KEY_SUCCESS  0

#define KEY1_PORT    GPIOA
#define KEY1_PIN     GPIO_Pin_0

#define KEY2_PORT    GPIOC
#define KEY2_Pin     GPIO_Pin_13

typedef struct
{
	unsigned char ID;
}
KEY_PARA_T;






unsigned char Key_App_Handle(unsigned char sum);









#endif



