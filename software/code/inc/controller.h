/**
  ******************************************************************************
  *
  * main controller
  * author: coregiu
  * 
  * 
  ******************************************************************************
**/

#ifndef PS2_CONTROLLER_H
#define PS2_CONTROLLER_H

#include <mcs51/8051.h>
#include <ps2_receiver.h>
#include <music_switch.h>
#include <led_group.h>
#include <motor_driver.h>
#include <command_receiver.h>

void init_modules();

void receive_cmd();

void notify_all(uint *car_cmds);

#endif