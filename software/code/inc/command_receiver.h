/**
  ******************************************************************************
  *
  * command define and command receiver.
  * author: coregiu
  * 
  * 
  ******************************************************************************
**/

#ifndef COMMAND_DEFINE_H
#define COMMAND_DEFINE_H

#define _nop_() __asm NOP __endasm

#define COMMANDS_LENGTH 12

#include "log.h"

// define led monitor
#define LED_GROUP_MONITOR   P0
#define LED_LEFT_TOP        P0_0
#define LED_LEFT_DOWN       P0_1
#define LED_LEFT_LEFT       P0_2
#define LED_LEFT_RIGHT      P0_3
#define LED_RIGHT_TOP       P0_4
#define LED_RIGHT_DOWN      P0_5
#define LED_RIGHT_LEFT      P0_6
#define LED_RIGHT_RIGHT     P0_7

// define swtich const var
enum control_switch
{
  SWITCH_ON=1, SWITCH_OFF=0
};

// define commands id
enum car_commands
{
    COMMAND_NULL         = 0,
    COMMAND_LEFT_TOP     = 1,
    COMMAND_LEFT_DOWN    = 2,
    COMMAND_LEFT_LEFT    = 3,
    COMMAND_LEFT_RIGHT   = 4,
    COMMAND_RIGHT_TOP    = 5,
    COMMAND_RIGHT_DOWN   = 6,
    COMMAND_RIGHT_LEFT   = 7,
    COMMAND_RIGHT_RIGHT  = 8,
    COMMAND_LEFT_1       = 9,
    COMMAND_LEFT_2       = 10,
    COMMAND_RIGHT_1      = 11,
    COMMAND_RIGHT_2      = 12
};

// define module id
enum module
{
    MODULE_MOTOR   = 0,
    MODULE_MUSIC   = 1,
    MODULE_LED     = 2,
    MODULE_SERVO   = 3
};

// CAR run state
enum car_run_state
{
    STOP = 0, MOVE = 1, BACK = 2, LEFT = 3, RIGHT = 4
};

// current global status of car.
struct car_status
{
	// motor status of current car
	enum car_run_state current_car_status;

	// check is need stop the car by the inspect_motor function.
	uchar is_need_stop_auto;

	// if thereis a command.
	uchar is_has_command;
};

extern struct car_status g_car_status;

// the main configuration of car.
struct car_config
{
	// 50ms per time. dafault 10 times, equals 0.5 second.
	uchar car_run_delay_times;
  uchar interval_of_read_ps2_h;
  uchar interval_of_read_ps2_l;
};

extern const struct car_config g_car_config;

struct module_command_receiver
{
	void (*init)();
	void (*update_state)(uint car_cmd);
};

extern void delay_time_ms(uint mil_sec);

#endif