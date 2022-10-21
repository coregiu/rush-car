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
#include <motor_driver.h>

void init_motor_switch()
{

}

void move()
{

}

void back()
{

}

void turn_left()
{

}

void turn_right()
{

}

void update_motor_state(int *car_cmds)
{
  for(char i = 0; i < COMMANDS_LENGTH; i++)
  {
    car_cmds[i];
  }
}

const struct module_command_receiver motor_driver = {init_motor_switch, update_motor_state};