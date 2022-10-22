/**
  ******************************************************************************
  *
  * the switch of leds
  * author: coregiu
  * 
  * The command of LED: RIGHT_LEFT
  * The monitor led of this command: P0_6
  * 
  ******************************************************************************
**/
#ifndef MUSIC_LED_GROUP_H
#define MUSIC_LED_GROUP_H

#include <command_receiver.h>

#define  LED_ABOVE_CAR  P1_2

extern const struct module_command_receiver led_group;

#endif