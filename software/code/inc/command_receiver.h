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

#define uint unsigned int
#define uchar unsigned char

#define COMMANDS_LENGTH 8

// define commands id
#define COMMAND_NULL         0
#define COMMAND_LEFT_TOP     1
#define COMMAND_LEFT_DOWN    2
#define COMMAND_LEFT_LEFT    3
#define COMMAND_LEFT_RIGHT   4
#define COMMAND_RIGHT_TOP    5
#define COMMAND_RIGHT_RIGHT  6
#define COMMAND_RIGHT_LEFT   7
#define COMMAND_RIGHT_DOWN   8

// define led monitor
#define LED_GROUP_MONITOR   P0
#define LED_LEFT_TOP        P0_0
#define LED_LEFT_DOWN       P0_1
#define LED_LEFT_LEFT       P0_2
#define LED_LEFT_RIGHT      P0_3
#define LED_RIGHT_TOP       P0_4
#define LED_RIGHT_RIGHT     P0_5
#define LED_RIGHT_LEFT      P0_6
#define LED_RIGHT_DOWN      P0_7

struct module_command_receiver
{
	void (*init)();
	void (*update_state)(int *car_cmds);
};

extern void delay_time_ms(uint mil_sec);

#endif