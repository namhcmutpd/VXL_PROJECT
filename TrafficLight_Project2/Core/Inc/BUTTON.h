/*
 * BUTTON.h
 *
 *  Created on: Oct 30, 2025
 *      Author: NAM
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
#define NUM_BUTTONS 4
#define BTN_MODE    0
#define BTN_UP      1
#define BTN_DOWN    2
#define BTN_ER		3
#define HOLD_TIME 1000

void GetKeyInput(void);
uint8_t button_is_pressed(uint8_t index);
uint8_t button_is_hold_1s(uint8_t index);
uint8_t button_is_hold_fast_tick(uint8_t index);
uint8_t button_is_combo_hold_1s(void);
#endif /* INC_BUTTON_H_ */
