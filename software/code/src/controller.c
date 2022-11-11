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

/**
 * init uart and all receive modules
 * 
 */
void init_modules()
{
    uart_init();

    motor_driver.init();
    led_group.init();
    music_switch.init();
}

/**
 * receive ps2 data, convert to commands,
 * and notify modules to execute commands;
 * 
 */
void receive_exe_cmd()
{
    uint *commands = read_ps2();
    notify_all(commands);
}

/**
 * inspect motor status.
 * if no motor command after 10 interval(500ms), stop the car.
 */
void inspect_motor_cmd()
{

}

/**
 * notify modules to execute the commands.
 * 
 */
void notify_all(uint *car_cmds)
{
    motor_driver.update_state(car_cmds);
    led_group.update_state(car_cmds);
    music_switch.update_state(car_cmds);
}