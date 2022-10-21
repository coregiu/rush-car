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
#include <music_switch.h>

void init_music_switch()
{

}

void next_music()
{

}

void play_music()
{

}

void update_music_state(int *car_cmds)
{
  for(char i = 0; i < COMMANDS_LENGTH; i++)
  {
    car_cmds[i];
  }
}

const struct module_command_receiver music_switch = {init_music_switch, update_music_state};