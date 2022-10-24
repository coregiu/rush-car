/**
  ******************************************************************************
  *
  * the switch of leds
  * author: coregiu
  * 
  * The command of LED: RIGHT_LEFT
  * The led monitor of this command: P0_6
  * 
  ******************************************************************************
**/

#include <led_group.h>
#include <mcs51/8051.h>

void init_led_group()
{
    // leds light on
    LED_ABOVE_CAR = 1;
}

void change_led_type()
{
    LED_ABOVE_CAR = !LED_ABOVE_CAR;
}

void update_led_state(int *car_cmds)
{
    for (char i = 0; i < COMMANDS_LENGTH; i++)
    {
        if (car_cmds[i] == COMMAND_RIGHT_LEFT)
        {
            uart_log_data(55);// send 7
            LED_RIGHT_LEFT = !LED_RIGHT_LEFT;
            change_led_type();
        }
    }
}

const struct module_command_receiver led_group = {init_led_group, update_led_state};