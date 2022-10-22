/**
  ******************************************************************************
  *
  * the switch of leds
  * author: coregiu
  * 
  * Command:
  * change led type command: right right and right down.
  * 
  * The controller of bits:
  * LED_1: P0_0
  * LED_2: P0_1
  * LED_3: P0_2
  * LED_4: P0_3
  * LED_5: P0_4
  * LED_6: P0_5
  * LED_7: P0_6
  * LED_8: P0_7
  * 
  ******************************************************************************
**/

#include <led_group.h>
#include <mcs51/8051.h>

void init_led_group()
{
    // all leds light on
    P0 = 0;
}

void change_led_type()
{
}

void update_led_state(int *car_cmds)
{
    for (char i = 0; i < COMMANDS_LENGTH; i++)
    {
        if (car_cmds[i] == COMMAND_RIGHT_RIGHT || car_cmds[i] == COMMAND_RIGHT_DOWN)
        {
            change_led_type();
        }
    }
}

const struct module_command_receiver led_group = {init_led_group, update_led_state};