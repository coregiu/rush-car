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

#define COMMANDS_LENGTH 12

#include "log.h"

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
    MOTOR   = 0,
    MUSIC   = 1,
    LED     = 2
};

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

struct module_command_receiver
{
	void (*init)();
	void (*update_state)(int *car_cmds);
};

extern uchar command_flag;

extern void delay_time_ms(uint mil_sec);

#endif