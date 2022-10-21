/**
  ******************************************************************************
  *
  * the switch of leds
  * author: coregiu
  * 
  * The controller of bits:
  * LED_1: P0_0
  * LED_2: P0_1
  * LED_3: P0_2
  * LED_4: P0_3
  * LED_5: P0_4
  * LED_6: P0_5
  * LED_7: P0_6
  * LED_8: P0_7
  * 
  ******************************************************************************
**/
#ifndef MUSIC_LED_GROUP_H
#define MUSIC_LED_GROUP_H

#include <command_receiver.h>

#define  LED_1  P0_0
#define  LED_2  P0_1
#define  LED_3  P0_2
#define  LED_4  P0_3
#define  LED_5  P0_4
#define  LED_6  P0_5
#define  LED_7  P0_6
#define  LED_8  P0_7

extern const struct module_command_receiver led_group;

#endif