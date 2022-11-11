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
#include <command_receiver.h>

/**
 * init uart and all receive modules
 * 
 */
void init_modules();

/**
 * receive ps2 data, convert to commands,
 * and notify modules to execute commands;
 * 
 */
void receive_exe_cmd();

/**
 * inspect motor status.
 * if no motor command after 10 interval(500ms), stop the car.
 */
void inspect_motor_cmd(); 

/**
 * notify modules to execute the commands.
 * car_module: the module of car, such as motor, music, led
 * car_cmd: the command
 * 
 */
void notify_all(enum module car_module, uint car_cmd);

#endif