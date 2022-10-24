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

void delay_time_ms(uint mil_sec)
{
	uint i, j;
	for (i = mil_sec; i > 0; i--)
		for (j = 70; j > 0; j--)
			;
}

void main()
{
	delay_time_ms(500);

	init_modules();

	while (1)
	{
		receive_cmd();
		delay_time_ms(300);
	}
}