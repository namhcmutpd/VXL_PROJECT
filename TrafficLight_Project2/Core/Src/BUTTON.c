/*
 * BUTTON.c
 *
 *  Created on: Oct 30, 2025
 *      Author: NAM
 */
#include "BUTTON.h"
#include "GLOBAL.h"

#define BUTTON_IS_PRESSED   GPIO_PIN_RESET
#define BUTTON_IS_RELEASED  GPIO_PIN_SET
#define TICKS_FOR_1S_HOLD   (HOLD_TIME / TICK)
#define TICKS_FOR_FAST_TICK 20 // 200ms cho mỗi lần tăng nhanh

static int button_state[NUM_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static int key_reg0[NUM_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static int key_reg1[NUM_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static int key_reg2[NUM_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};

static int counter_for_hold[NUM_BUTTONS] = {0};
static uint8_t flag_btn_press[NUM_BUTTONS] = {0};
static uint8_t flag_btn_hold_1s[NUM_BUTTONS] = {0};
static uint8_t flag_btn_hold_fast_tick[NUM_BUTTONS] = {0};

static GPIO_TypeDef* BTN_PORT[NUM_BUTTONS] = {BTN_MODE_Port, BTN_UP_Port, BTN_DOWN_Port, BTN_ER_Port};
static uint16_t BTN_PIN[NUM_BUTTONS] = {BTN_MODE_Pin, BTN_UP_Pin, BTN_DOWN_Pin, BTN_ER_Pin};

static int read_button_pin(int index) {
    return HAL_GPIO_ReadPin(BTN_PORT[index], BTN_PIN[index]);
}

uint8_t button_is_pressed(uint8_t index) {
    if (flag_btn_press[index] == 1) {
        flag_btn_press[index] = 0;
        return 1;
    }
    return 0;
}

uint8_t button_is_hold_1s(uint8_t index) {
    if (flag_btn_hold_1s[index] == 1) {
        flag_btn_hold_1s[index] = 0;
        return 1;
    }
    return 0;
}

uint8_t button_is_hold_fast_tick(uint8_t index) {
    if (flag_btn_hold_fast_tick[index] == 1) {
        flag_btn_hold_fast_tick[index] = 0;
        return 1;
    }
    return 0;
}

void GetKeyInput(void) {
    for (int i = 0; i < NUM_BUTTONS; i++) {
        key_reg0[i] = key_reg1[i];
        key_reg1[i] = key_reg2[i];
        key_reg2[i] = read_button_pin(i);

        if ((key_reg0[i] == key_reg1[i]) && (key_reg1[i] == key_reg2[i])) {
            if (button_state[i] != key_reg2[i]) {
                button_state[i] = key_reg2[i];

                if (button_state[i] == BUTTON_IS_PRESSED) {
                    // Bắt đầu nhấn: Reset counter, chưa set cờ Press vội
                    counter_for_hold[i] = 0;
                } else {
                    // Nút được thả ra (Release)
                    // Nếu thời gian giữ < 1s thì đây là nhấn ngắn (Short Press)
                    if (counter_for_hold[i] < TICKS_FOR_1S_HOLD) {
                        flag_btn_press[i] = 1;
                    }
                    // Reset các cờ giữ
                    flag_btn_hold_1s[i] = 0;
                    flag_btn_hold_fast_tick[i] = 0;
                }
            } else {
                // Đang giữ nút
                if (button_state[i] == BUTTON_IS_PRESSED) {
                    counter_for_hold[i]++;
                    if (counter_for_hold[i] == TICKS_FOR_1S_HOLD) {
                        flag_btn_hold_1s[i] = 1; // Đạt mốc 1s
                    } else if (counter_for_hold[i] > TICKS_FOR_1S_HOLD) {
                        // Sau 1s, cứ mỗi khoảng thời gian (FAST_TICK) lại kích hoạt cờ fast
                        if ((counter_for_hold[i] - TICKS_FOR_1S_HOLD) % TICKS_FOR_FAST_TICK == 0) {
                            flag_btn_hold_fast_tick[i] = 1;
                        }
                    }
                }
            }
        }
    }
}
