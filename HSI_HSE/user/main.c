#include "system.h"





int main(void)
{
	System_Init();
	while(1)
	{
		System_Handle();
	}
}


