/**
  ******************************************************************************
  *
  * main controller
  * author: coregiu
  * 
  * 
  ******************************************************************************
**/

#include <controller.h>

#define MODULE_NUMBER 3

struct module_command_receiver modules[MODULE_NUMBER];

void init_modules()
{
    uart_init();
    // for (int i = 0; i < MODULE_NUMBER; i++)
    // {
    //   modules[i].init();
    // }
    motor_driver.init();
    led_group.init();
    music_switch.init();
}

void receive_cmd()
{
    uint *commands = read_ps2();
    notify_all(commands);
}

void notify_all(uint *car_cmds)
{
    // for (int i = 0; i < MODULE_NUMBER; i++)
    // {
    //   modules[i].update_state(car_cmds);
    // }
    motor_driver.update_state(car_cmds);
    led_group.update_state(car_cmds);
    music_switch.update_state(car_cmds);
}