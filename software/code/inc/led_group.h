/**
  ******************************************************************************
  *
  * the switch of leds
  * author: coregiu
  * 
  * The controller of bits: P1_2
  * The command of LED: RIGHT_LEFT and RIGHT_DOWN
  * The monitor of this command: P0_6  P0_6
  * 
  ******************************************************************************
**/
#ifndef MUSIC_LED_GROUP_H
#define MUSIC_LED_GROUP_H

#include <command_receiver.h>

#define  LED_ABOVE_CAR  P1_2

extern const struct module_command_receiver led_group;

#endif