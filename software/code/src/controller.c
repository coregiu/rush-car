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
    motor_driver.init();
    led_group.init();
    music_switch.init();
}

/**
 * receive ps2 data, convert to commands,
 * and notify modules to execute commands;
 * 
 */
int execute_commands(struct pt *pt, int **commands)
{
    PT_BEGIN(pt);

	while (1)
	{
		/* Wait until the other protothread has set its flag. */
		PT_WAIT_UNTIL(pt, is_has_command);
        for (uchar i = 0; i < COMMANDS_LENGTH; i++)
        {
            notify_all(commands[i][1], commands[i][0]);
        }

		/* We then reset the other protothread's flag. */
		is_has_command = 0;

		/* And we loop. */
	}
	PT_END(pt);
}

/**
 * inspect motor status.
 * if no motor command after 10 interval(500ms), stop the car.
 */
int inspect_motor(struct pt *pt)
{
    PT_BEGIN(pt);

	while (1)
	{
		/* Wait until the other protothread has set its flag. */
		PT_WAIT_UNTIL(pt, non_motor_cmd_times >= CAR_RUN_DELAY_TIMES && is_need_stop_auto);
		notify_all(MODULE_MOTOR, COMMAND_LEFT_2); // stop the car

		/* We then reset the other protothread's flag. */
        non_motor_cmd_times = 0;
        is_need_stop_auto = 0;
        
		/* And we loop. */
	}
	PT_END(pt);
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
    case MODULE_MOTOR:
        non_motor_cmd_times = 0;
        motor_driver.update_state(car_cmd);
        break;
    case MODULE_LED:
        non_motor_cmd_times++;
        led_group.update_state(car_cmd);
        break;
    case MODULE_MUSIC:
        non_motor_cmd_times++;
        music_switch.update_state(car_cmd);
        break;
    
    default:
        break;
    }
}