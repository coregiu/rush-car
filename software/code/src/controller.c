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
    motor_driver.init();
    led_group.init();
    music_switch.init();
    servos_driver.init();
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
		PT_WAIT_UNTIL(pt, g_car_status.is_has_command);
        for (uchar i = 0; i < COMMANDS_LENGTH; i++)
        {
            notify_all(commands[i][1], commands[i][0]);
        }

		/* We then reset the other protothread's flag. */
		g_car_status.is_has_command = 0;
        g_car_status.is_need_stop_auto = 1;

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
		PT_WAIT_UNTIL(pt, g_car_status.non_motor_cmd_times >= g_car_config.car_run_delay_times 
                          && g_car_status.is_need_stop_auto);
		notify_all(MODULE_MOTOR, COMMAND_LEFT_2); // stop the car
        notify_all(MODULE_SERVO, COMMAND_LEFT_2); // set servo to receive new command

		/* We then reset the other protothread's flag. */
        g_car_status.non_motor_cmd_times = 0;
        g_car_status.is_need_stop_auto = 0;
        
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
        g_car_status.non_motor_cmd_times = 0;
        motor_driver.update_state(car_cmd);
        break;
    case MODULE_LED:
        g_car_status.non_motor_cmd_times++;
        led_group.update_state(car_cmd);
        break;
    case MODULE_MUSIC:
        g_car_status.non_motor_cmd_times++;
        music_switch.update_state(car_cmd);
        break;
    case MODULE_SERVO:
        g_car_status.non_motor_cmd_times++;
        servos_driver.update_state(car_cmd);
        break;
    
    default:
        g_car_status.non_motor_cmd_times++;
        break;
    }
}