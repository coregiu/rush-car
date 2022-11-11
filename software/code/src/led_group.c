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

#include <led_group.h>
#include <mcs51/8051.h>

void init_led_group()
{
    // leds light on
    LED_ABOVE_CAR = SWITCH_OFF;
}

void led_switch_on()
{
    if (LED_ABOVE_CAR != SWITCH_ON)
    {
        LED_ABOVE_CAR = SWITCH_ON;
    }
}

void led_switch_off()
{
    if (LED_ABOVE_CAR != SWITCH_OFF)
    {
        LED_ABOVE_CAR = SWITCH_OFF;
    }
}


void update_led_state(uint car_cmd)
{
    if (car_cmd == COMMAND_RIGHT_LEFT)
    {
        uart_log_string_data("e:7"); // send 7
        LED_RIGHT_LEFT = !LED_RIGHT_LEFT;
        led_switch_on();
    } else if (car_cmd == COMMAND_RIGHT_RIGHT)
    {
        uart_log_string_data("e:8"); // send 8
        LED_RIGHT_RIGHT = !LED_RIGHT_RIGHT;
        led_switch_off();
    }
}

const struct module_command_receiver led_group = {init_led_group, update_led_state};