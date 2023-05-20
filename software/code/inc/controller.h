/**
  ******************************************************************************
  *
  * main controller
  * author: coregiu
  * 
  * 
  ******************************************************************************
**/

#ifndef PS2_CONTROLLER_H
#define PS2_CONTROLLER_H

#include <mcs51/8051.h>
#include <ps2_receiver.h>
#include <music_switch.h>
#include <led_group.h>
#include <motor_driver.h>
#include <servos_driver.h>
#include <command_receiver.h>
#include "pt.h"

/**
 * init uart and all receive modules
 * 
 */
void init_modules();

/**
 * execute commands;
 * 
 */
int execute_commands(struct pt *pt, int **commands);

/**
 * inspect motor status.
 * if no motor command after 10 interval(500ms), stop the car.
 */
int inspect_motor(struct pt *pt);

/**
 * notify modules to execute the commands.
 * car_module: the module of car, such as motor, music, led
 * car_cmd: the command
 * 
 */
void notify_all(enum module car_module, uint car_cmd);

#endif