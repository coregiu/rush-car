/**
  ******************************************************************************
  *
  * the switch of leds
  * author: coregiu
  * 
  * led light switch: P2_7
  * 
  * The command of play: 
  *     RIGHT_LEFT  - switch on,  command 7; 
  *     RIGHT_RIGHT - switch off, command 8;
  * 
  * The monitor led of this command: P0_6  P0_7
  * 
  ******************************************************************************
**/

#ifndef MUSIC_LED_GROUP_H
#define MUSIC_LED_GROUP_H

#include <command_receiver.h>

#define  LED_ABOVE_CAR  P2_7

extern const struct module_command_receiver led_group;

#endif