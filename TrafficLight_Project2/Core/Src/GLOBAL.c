/*
 * GLOBAL.c
 *
 *  Created on: Oct 30, 2025
 *      Author: NAM
 */

#include "GLOBAL.h"

int STATUS = INIT;
int blink_state = 0;
int time_red = 5;
int time_green = 3;
int time_yellow = 2;
int remaining_time_road1 = 0;
int remaining_time_road2 = 0;
int fsm_auto_state = INIT;

