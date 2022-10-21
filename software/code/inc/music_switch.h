/**
  ******************************************************************************
  *
  * the switch of music
  * author: coregiu
  * 
  * play switch: P2_6
  * next switch: P2_7
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