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

#define COMMAND_NULL         0
#define COMMAND_LEFT_TOP     1
#define COMMAND_LEFT_DOWN    2
#define COMMAND_LEFT_LEFT    3
#define COMMAND_LEFT_RIGHT   4

#define COMMAND_RIGHT_TOP    5
#define COMMAND_RIGHT_DOWN   6
#define COMMAND_RIGHT_LEFT   7
#define COMMAND_RIGHT_RIGHT  8

struct module_command_receiver
{
  void (*init)();
  void (*update_state)(int *car_cmds);
};

#endif