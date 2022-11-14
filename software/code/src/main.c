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
/* 71ms per period */
#define DEFAULT_CAR_RUN_DELAY_TIMES 10
#define READ_PS2_INTVAL_TIME_MS_H   0X00
#define READ_PS2_INTVAL_TIME_MS_L   0X00

const struct car_config g_car_config = {DEFAULT_CAR_RUN_DELAY_TIMES, READ_PS2_INTVAL_TIME_MS_H, READ_PS2_INTVAL_TIME_MS_L};

struct pt pt_cmd_receiver, pt_motor_inspector;
struct car_status g_car_status = {STOP, 0, 0, 0};

void delay_time_ms(uint mil_sec)
{
	uint i, j;
	for (i = mil_sec; i > 0; i--)
		for (j = 70; j > 0; j--)
			;
}

/**
 * init timer 0.
 */
void init_timer()
{
	// init timer0
	TMOD |= 0X01;
	ET0 = 1;
    TR0 = 1;
    TH0 = g_car_config.interval_of_read_ps2_h;
    TL0 = g_car_config.interval_of_read_ps2_l; 
	EA  = 1; //开启总中断
}

/**
 * init uart.
 */
void init_uart()
{
	// init uart
	TMOD |= 0x20; //用定时器设置串口波特率	   9600
	TH1  = 0xfd;
	TL1  = 0xfd;
	TR1  = 1;
	ES   = 0;
	SCON = 0X50; 
	EA   = 1; //开启总中断
}

void main()
{
	delay_time_ms(500);

	init_timer();
	init_uart();
	init_modules();

	PT_INIT(&pt_cmd_receiver);
	PT_INIT(&pt_motor_inspector);

	uart_log_start_info();
	while (1)
	{

	}
}

/**
 * timer 0 interrupt function.
 * read ps2 command and execute it by 50ms interval.
 */
void time_0_isr(void) __interrupt 1
{
	// reset number of beginning.
	TH0 = g_car_config.interval_of_read_ps2_h;
	TL0 = g_car_config.interval_of_read_ps2_l;
	
	// read ps2 command and set is_has_command/non_motor_cmd_times value.
	uint commands[COMMANDS_LENGTH][2] = {{0}};
	read_ps2(commands);
	// executet the commands.
	execute_commands(&pt_cmd_receiver, commands); 
	// inspect motor status.
	inspect_motor(&pt_motor_inspector); 
}