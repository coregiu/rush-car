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

#include <music_switch.h>
#include <mcs51/8051.h>

void init_music_switch()
{
    SWITCH_PLAY = 0;
    SWITCH_NEXT = 0;
}

void next_music()
{
    SWITCH_NEXT = 1;
    delay_time_ms(500);
    SWITCH_NEXT = 0;
}

void play_music()
{
    SWITCH_NEXT = !SWITCH_NEXT;
}

void update_music_state(int *car_cmds)
{
    for (char i = 0; i < COMMANDS_LENGTH; i++)
    {
        if (car_cmds[i] == COMMAND_RIGHT_TOP)
        {
            LED_RIGHT_TOP = !LED_RIGHT_TOP;
            play_music();
        }
        else if (car_cmds[i] == COMMAND_RIGHT_RIGHT) 
        {
            LED_RIGHT_RIGHT = !LED_RIGHT_RIGHT;
            next_music();
        }
    }
}

const struct module_command_receiver music_switch = {init_music_switch, update_music_state};