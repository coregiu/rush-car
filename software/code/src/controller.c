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

// 50ms per time. dafault 10 times, equals 0.5 second.
const uint CAR_RUN_DELAY_TIMES = 10;

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
    non_motor_cmd_times++;
    uint **commands = read_ps2();
    for (uchar i = 0; i < COMMANDS_LENGTH; i++)
    {
        notify_all(commands[i][1], commands[i][0]);
    }
}

/**
 * inspect motor status.
 * if no motor command after 10 interval(500ms), stop the car.
 */
void inspect_motor_cmd()
{
    if (non_motor_cmd_times >= CAR_RUN_DELAY_TIMES)
    {
        notify_all(MOTOR, COMMAND_LEFT_2); // stop the car
    }
}

/**
 * notify modules to execute the commands.
 * car_module: the module of car, such as motor, music, led
 * car_cmd: the command
 * 
 */
void notify_all(enum module car_module, uint car_cmd)
{
    switch (car_module)
    {
    case MOTOR:
        non_motor_cmd_times = 0;
        motor_driver.update_state(car_cmd);
        break;
    case LED:
        led_group.update_state(car_cmd);
        break;
    case MUSIC:
        music_switch.update_state(car_cmd);
        break;
    
    default:
        break;
    }
}