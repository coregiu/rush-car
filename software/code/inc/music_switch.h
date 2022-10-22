/**
  ******************************************************************************
  *
  * the switch of music
  * author: coregiu
  * 
  * play switch: P2_6
  * The command of play: RIGHT_TOP
  * The monitor led of this command: P0_4
  * 
  * next switch: P2_7
  * The command of play: RIGHT_RIGHT
  * The monitor led of this command: P0_5
  * 
  * 
  ******************************************************************************
**/

#ifndef MUSIC_SWITCH_H
#define MUSIC_SWITCH_H

#include <command_receiver.h>

#define SWITCH_PLAY P2_6
#define SWITCH_NEXT P2_7

extern const struct module_command_receiver music_switch;

#endif