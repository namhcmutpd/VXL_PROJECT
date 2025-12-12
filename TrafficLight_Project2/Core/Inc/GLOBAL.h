/*
 * GLOBAL.h
 * Created on: Oct 30, 2025
 * Author: NAM
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "BUTTON.h"
#include "FSM_INIT.h"
#include "FSM_AUTO.h"
#include "FSM_MANUAL.h"
#include "FSM_ERROR.h"
#include "SOFTWARE_TIMER.h"
#include "STATUS_LIGHT.h"
#include "LCD.h"
#include "main.h"
#include <stdio.h>
#include <stdint.h>

#define TICK 10

// --- System Status ---
#define INIT        0
#define AUTO        1
#define MANUAL      2
#define ERROR       3

// --- Traffic Light States ---
#define STATE_RED1_GREEN2   10
#define STATE_RED1_YELLOW2  11
#define STATE_GREEN1_RED2   12
#define STATE_YELLOW1_RED2  13
#define STATE_ALL_OFF       14
#define STATE_ALL_YELLOW    15
#define STATE_ALL_RED       16
#define STATE_ALL_GREEN     17

// --- Timer Indices ---
#define TIMER_1SEC_DISPLAY 0
#define TIMER_FSM_AUTO     1
#define TIMER_BLINK        2
#define TIMER_INIT         3

// --- Global Variables ---
extern int STATUS;
extern int fsm_auto_state;
extern int mode_manual_phase;
extern int time_red;
extern int time_green;
extern int time_yellow;
extern int remaining_time_road1;
extern int remaining_time_road2;
extern int blink_state;

#endif /* INC_GLOBAL_H_ */
