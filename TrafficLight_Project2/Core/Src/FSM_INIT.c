/*
 * FSM_INIT.c
 *
 *  Created on: Dec 12, 2025
 *      Author: NAM
 */

#include "GLOBAL.h"


void FSM_INIT_RUN(void) {
    setTrafficLight(STATE_ALL_OFF);

    // Kiểm tra timer khởi động (ví dụ chờ 1s để ổn định hệ thống)
    if (getTimerFlag(TIMER_INIT) == 1) {
        STATUS = AUTO;
        fsm_auto_state = STATE_RED1_GREEN2;

        // Cập nhật trạng thái đèn ban đầu
        setTrafficLight(STATE_RED1_GREEN2);

        // Cập nhật thời gian đếm ngược ban đầu
        remaining_time_road1 = time_red;
        remaining_time_road2 = time_green;

        // Set timer cho trạng thái AUTO đầu tiên
        setTimer(TIMER_FSM_AUTO, time_green * 1000);
        setTimer(TIMER_1SEC_DISPLAY, 1000);
    }
}
