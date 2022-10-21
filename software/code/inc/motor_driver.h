/**
  ******************************************************************************
  *
  * the switch of motor
  * author: coregiu
  * 
  * P2_0 : LEFT_EN   L298N_EnB
  * P2_1 : LEFT_MV   L298N_IN4
  * P2_2 : LEFT_BK   L298N_IN3
  * P2_3 : RIGHT_EN  L298N_EnA
  * P2_4 : RIGHT_MV  L298N_IN2
  * P2_5 : RIGHT_BK  L298N_IN1 
  * 
  ******************************************************************************
**/
#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

#include <command_receiver.h>

#define   LEFT_EN    P2_0
#define   LEFT_MV    P2_1
#define   LEFT_BK    P2_2
#define   RIGHT_EN   P2_3
#define   RIGHT_MV   P2_4
#define   RIGHT_BK   P2_5

extern const struct module_command_receiver motor_driver;

#endif