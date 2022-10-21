/**
  ******************************************************************************
  *
  * PS2 Receiver
  * author: coregiu
  * Baudrate 9600
  * 
  ******************************************************************************
**/

#include <ps2_receiver.h>


#define Fosc 11059200 //晶振频率
#define _nop_() __asm NOP __endasm

#define DATA P1_4  //D0
#define CMND P1_5  //D1
#define ATT  P1_6  //CS
#define CLK  P1_7  //CLK

#define COMMANDS_LENGTH 8

/********手柄定义变量*********/
const uchar scan[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const uint command_map[COMMANDS_LENGTH][3] = {{3, 0xEF, COMMAND_LEFT_TOP}, 
											{3, 0xBF, COMMAND_LEFT_DOWN}, 
											{3, 0x7F, COMMAND_LEFT_LEFT}, 
											{3, 0xDF, COMMAND_LEFT_RIGHT}, 
											{4, 0xEF, COMMAND_RIGHT_TOP}, 
											{4, 0xBF, COMMAND_RIGHT_DOWN}, 
											{4, 0x7F, COMMAND_RIGHT_LEFT}, 
											{4, 0xDF, COMMAND_RIGHT_RIGHT}};

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
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
	REN = 1; //串口初始化
	SM0 = 0;
	SM1 = 1;
	EA = 1; //开启总中断
	ES = 1;
}

/********************************************************************
* name : uart_sendata(uchar n)
* func : 发送字节
* in   : 有
* out  : 无
***********************************************************************/
void uart_sendata(uchar n)
{
	ES = 0;
	TI = 0;
	SBUF = n;
	while (!TI)
	{
		//如果发送完毕，硬件会置位TI
	}
	TI = 0;
	ES = 1;
}

void delay(uint n) //delay(x)=(2.5+x)us;
{
	uint i;
	for (i = 0; i < n; i++)
	{
		_nop_();
	}	
}

uchar scanout(uchar command) //手柄发送子程序
{
	uchar i, j = 1;
	uchar res = 0;
	for (i = 0; i <= 7; i++) //逐位接收
	{
		if (command & 0x01)
			CMND = 1;
		else
			CMND = 0;
		command = command >> 1;
		_nop_();
		_nop_();
		CLK = 0;
		delay(10);
		if (DATA)
			res = res + j;
		j = j << 1;
		CLK = 1;
		delay(3);
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
	uint commands[COMMANDS_LENGTH]; // default is COMMAND_NULL
	for (char i = 0; i < COMMANDS_LENGTH; i++)
	{
		if (out[command_map[i][0]] == command_map[i][1])
		{
			commands[i] = command_map[i][2];
		}
	}
	return commands;
}

/********************************************************************
* name : void read_ps2()
* func : read commands from ps2, and return commands.
* in   : void
* out  : unit[]
***********************************************************************/
uint *read_ps2(void)
{
	uchar i;
	ATT = 0;
	for (i = 0; i < 9; i++) //scan keys
	{
		out[i] = scanout(scan[i]);
	}
	ATT = 1;
	for (i = 0; i < 9; i++)
	{
		uart_sendata(0x30);
		uart_sendata(0x78);
		if (out[i] / 16 < 10)
		{
			uart_sendata(out[i] / 16 + 0x30);
		}
		else
		{
			uart_sendata(out[i] / 16 + 0x37);
		}

		if (out[i] % 16 < 10)
		{
			uart_sendata(out[i] % 16 + 0x30);
		}
		else
		{
			uart_sendata(out[i] % 16 + 0x37);
		}
		uart_sendata(' ');
		uart_sendata(' ');
	}
	uart_sendata(0x0d);
	uart_sendata(0x0a);
	return convert_commands();
}