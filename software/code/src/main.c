/**
  ******************************************************************************
  *
  * main function
  * author: coregiu
  * 
  * 
  ******************************************************************************
**/

#include <controller.h>

void delayms(uint xms)
{
	uint i, j;
	for (i = xms; i > 0; i--)
		for (j = 70; j > 0; j--)
			;
}

void main()
{
	delayms(500);

	init_modules();

	while (1)
	{
		receive_cmd();
		delayms(500);
	}
}