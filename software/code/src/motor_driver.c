/**
  ******************************************************************************
  *
  * the switch of motor
  * author: coregiu
  * 
  * MOVE command:
  *     key: LEFT_TOP
  *     monitor led: P0_0
  *     gpio:
  *         LEFT_EN = 1
  *         LEFT_MV = 1
  *         LEFT_BK = 0
  *         RIGHT_EN = 1
  *         RIGHT_MV = 1
  *         RIGHT_BK = 0
  * 
  * BACK command:
  *     key: LEFT_DOWN
  *     monitor led: P0_1
  *     gpio:
  *         LEFT_EN = 1
  *         LEFT_MV = 0
  *         LEFT_BK = 1
  *         RIGHT_EN = 1
  *         RIGHT_MV = 0
  *         RIGHT_BK = 1
  * 
  * TURN LEFT command:
  *     key: LEFT_LEFT
  *     monitor led: P0_2
  *     gpio:
  *         LEFT_EN = 0
  *         LEFT_MV = 0
  *         LEFT_BK = 0
  *         RIGHT_EN = 1
  *         RIGHT_MV = 1
  *         RIGHT_BK = 0
  * 
  * TURN RIGHT command:
  *     key: LEFT_RIGHT
  *     monitor led: P0_3
  *     gpio:
  *         LEFT_EN = 1
  *         LEFT_MV = 1
  *         LEFT_BK = 0
  *         RIGHT_EN = 0
  *         RIGHT_MV = 0
  *         RIGHT_BK = 0
  * 
  * STOP command:
  *     key: RIGHT_DOWN
  *     monitor led: P0_7
  *     gpio:
  *         LEFT_EN = 0
  *         LEFT_MV = 0
  *         LEFT_BK = 0
  *         RIGHT_EN = 0
  *         RIGHT_MV = 0
  *         RIGHT_BK = 0
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
#include <mcs51/8051.h>

void stop()
{
    LEFT_EN = 0;
    LEFT_MV = 0;
    LEFT_BK = 0;
    RIGHT_EN = 0;
    RIGHT_MV = 0;
    RIGHT_BK = 0;
}

void init_motor_switch()
{
    stop();
}

void move()
{
    LEFT_EN = 1;
    LEFT_MV = 1;
    LEFT_BK = 0;
    RIGHT_EN = 1;
    RIGHT_MV = 1;
    RIGHT_BK = 0;
}

void back()
{
    LEFT_EN = 1;
    LEFT_MV = 0;
    LEFT_BK = 1;
    RIGHT_EN = 1;
    RIGHT_MV = 0;
    RIGHT_BK = 1;
}

void turn_left()
{
    LEFT_EN = 0;
    LEFT_MV = 0;
    LEFT_BK = 0;
    RIGHT_EN = 1;
    RIGHT_MV = 1;
    RIGHT_BK = 0;
}

void turn_right()
{
    LEFT_EN = 1;
    LEFT_MV = 1;
    LEFT_BK = 0;
    RIGHT_EN = 0;
    RIGHT_MV = 0;
    RIGHT_BK = 0;
}

void update_motor_state(int *car_cmds)
{
    for (char i = 0; i < COMMANDS_LENGTH; i++)
    {
        if (car_cmds[i] == COMMAND_LEFT_TOP)
        {
            uart_log_data(49); // send 1
            LED_LEFT_TOP = !LED_LEFT_TOP;
            move();
        }
        else if (car_cmds[i] == COMMAND_LEFT_DOWN) 
        {
            uart_log_data(50); // send 2
            LED_LEFT_DOWN = !LED_LEFT_DOWN;
            back();
        }
        else if (car_cmds[i] == COMMAND_LEFT_LEFT) 
        {
            uart_log_data(51); // send 3
            LED_LEFT_LEFT = !LED_LEFT_LEFT;
            turn_left();
        }
        else if (car_cmds[i] == COMMAND_LEFT_RIGHT) 
        {
            uart_log_data(52); // send 4
            LED_LEFT_RIGHT = !LED_LEFT_RIGHT;
            turn_right();
        }
        else if (car_cmds[i] == COMMAND_RIGHT_DOWN) 
        {
            uart_log_data(56); // send 8
            LED_RIGHT_DOWN = !LED_RIGHT_DOWN;
            stop();
        }
    }
}

const struct module_command_receiver motor_driver = {init_motor_switch, update_motor_state};