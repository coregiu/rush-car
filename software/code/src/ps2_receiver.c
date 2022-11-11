/**
  ******************************************************************************
  *
  * PS2 Receiver
  * author: coregiu
  * Baudrate 9600
  * 
  ******************************************************************************
**/

/*****************************PS2遥控器说明
out[3]==0xEF//左4个按键中上
out[3]==0xBF//左4个按键中下
out[3]==0x7F//左4个按键中左
out[3]==0xDF//左4个按键中右

out[4]==0xEF//右4个按键中上
out[4]==0xBF//右4个按键中下
out[4]==0x7F//右4个按键中左
out[4]==0xDF//右4个按键中右

out[4]==0xFB//左1,2个按键中1
out[4]==0xFE//左1,2个按键中2
out[4]==0xF7//右1,2个按键中1
out[4]==0xFD//右1,2个按键中2

当按下MODE键手柄MODE LED灯亮起时
out[7] 00——80——FF 左摇杆从左到右
out[8] 00——7F——FF 左摇杆从上到下
out[5] 00——80——FF 右摇杆从左到右
out[6] 00——7F——FF 右摇杆从上到下
当手柄MODE LED灯不亮时，手柄功能同左四右四按键
*******************************/

#include <ps2_receiver.h>


#define Fosc 11059200 //Crystal frequency
#define _nop_() __asm NOP __endasm

#define DATA P1_4  //D0
#define CMND P1_5  //D1
#define ATT  P1_6  //CS
#define CLK  P1_7  //CLK

/********vars of ps2*********/
const uchar scan[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint command_map[COMMANDS_LENGTH][4] = {{3, 0xEF, COMMAND_LEFT_TOP, MOTOR}, 
										      {3, 0xBF, COMMAND_LEFT_DOWN, MOTOR}, 
										      {3, 0x7F, COMMAND_LEFT_LEFT, MOTOR}, 
										      {3, 0xDF, COMMAND_LEFT_RIGHT, MOTOR}, 
										      {4, 0xEF, COMMAND_RIGHT_TOP, MUSIC}, 
										      {4, 0xBF, COMMAND_RIGHT_DOWN, MUSIC}, 
										      {4, 0x7F, COMMAND_RIGHT_LEFT, LED}, 
										      {4, 0xDF, COMMAND_RIGHT_RIGHT, LED}, 
										      {4, 0xFB, COMMAND_LEFT_1, MOTOR}, 
										      {4, 0xFE, COMMAND_LEFT_2, MOTOR}, 
										      {4, 0xF7, COMMAND_RIGHT_1, MOTOR}, 
										      {4, 0xFD, COMMAND_RIGHT_2, MOTOR}};

uchar out[9];

/********************************************************************
* name : void uart_init()
* func : 串口设置
* in   : 无
* out  : 无
***********************************************************************/
void uart_init()
{
	TMOD = 0x20; //用定时器设置串口波特率	   9600
	TH1  = 0xfd;
	TL1  = 0xfd;
	TR1  = 1;
	REN  = 1; //串口初始化
	SM0  = 0;
	SM1  = 1;
	EA   = 1; //开启总中断
	ES   = 1;
}

void send_ps2_key_info()
{
	for (uchar i = 0; i < 9; i++)
	{
		uart_log_hex_data(out[i]);
	}
	uart_log_enter_char();
}

void delay_empty_order(uint n) //delay_empty_order(x)=(2.5+x)us;
{
	uint i;
	for (i = 0; i < n; i++)
	{
		_nop_();
	}	
}

uchar scan_input_from_ps2(uchar command)
{
	uchar i, j = 1;
	uchar res = 0;
	for (i = 0; i <= 7; i++) //receive by bit
	{
		if (command & 0x01)
		{
			CMND = 1;
		}			
		else
		{
			CMND = 0;
		}
		command = command >> 1;
		delay_empty_order(2);
		CLK = 0;
		delay_empty_order(10);
		if (DATA)
		{
			res = res + j;
		}
		j = j << 1;
		CLK = 1;
		delay_empty_order(3);
	}
	CMND = 1;
	return res;
}

/********************************************************************
* name : void convert_commands()
* func : convert ps2 key to execute commands
* in   : void
* out  : unit[]
***********************************************************************/
uint *convert_commands()
{
	uint car_commands[COMMANDS_LENGTH] = {0}; // default is COMMAND_NULL
	for (char i = 0; i < COMMANDS_LENGTH; i++)
	{
		if (out[command_map[i][0]] == command_map[i][1])
		{
			car_commands[i] = command_map[i][2];
			uart_log_hex_data(command_map[i][2]);
		}
	}
	return car_commands;
}

/********************************************************************
* name : void read_ps2()
* func : read commands from ps2, and return commands.
* in   : void
* out  : unit[]
***********************************************************************/
uint *read_ps2(void)
{
	ATT = 0;
	for (uchar i = 0; i < 9; i++) //scan keys
	{
		out[i] = scan_input_from_ps2(scan[i]);
	}
	ATT = 1;
	return convert_commands();
}