#include "FSM_AUTO.h"
#include "GLOBAL.h"
#include "STATUS_LIGHT.h"
#include "BUTTON.h"

void FSM_AUTO_RUN() {
    switch (fsm_auto_state) {
        case STATE_RED1_GREEN2:
            setTrafficLight(STATE_RED1_GREEN2);
            if (getTimerFlag(TIMER_FSM_AUTO) == 1) {
                fsm_auto_state = STATE_RED1_YELLOW2;
                setTimer(TIMER_FSM_AUTO, time_yellow * 1000);
                remaining_time_road2 = time_yellow;
            }
            break;

        case STATE_RED1_YELLOW2:
            setTrafficLight(STATE_RED1_YELLOW2);
            if (getTimerFlag(TIMER_FSM_AUTO) == 1) {
                fsm_auto_state = STATE_GREEN1_RED2;
                setTimer(TIMER_FSM_AUTO, time_green * 1000);
                remaining_time_road1 = time_green;
                remaining_time_road2 = time_red;
            }
            break;

        case STATE_GREEN1_RED2:
            setTrafficLight(STATE_GREEN1_RED2);
            if (getTimerFlag(TIMER_FSM_AUTO) == 1) {
                fsm_auto_state = STATE_YELLOW1_RED2;
                setTimer(TIMER_FSM_AUTO, time_yellow * 1000);
                remaining_time_road1 = time_yellow;
            }
            break;

        case STATE_YELLOW1_RED2:
            setTrafficLight(STATE_YELLOW1_RED2);
            if (getTimerFlag(TIMER_FSM_AUTO) == 1) {
                fsm_auto_state = STATE_RED1_GREEN2;
                setTimer(TIMER_FSM_AUTO, time_green * 1000);
                remaining_time_road1 = time_red;
                remaining_time_road2 = time_green;
            }
            break;

        default:
            fsm_auto_state = STATE_RED1_GREEN2;
            break;
    }

    // Đếm ngược thời gian hiển thị
    if (getTimerFlag(TIMER_1SEC_DISPLAY) == 1) {
        setTimer(TIMER_1SEC_DISPLAY, 1000);
        remaining_time_road1--;
        remaining_time_road2--;
        if(remaining_time_road1 <= 0) remaining_time_road1 = 0;
        if(remaining_time_road2 <= 0) remaining_time_road2 = 0;
    }

    // --- XỬ LÝ CHUYỂN MODE ---
    // Giữ BTN0 1s -> MANUAL
    if(button_is_hold_1s(0)) {
    	mode_manual_phase = 0;
        STATUS = MANUAL;
        setTrafficLight(STATE_ALL_OFF);
    }
    // Giữ BTN3 1s -> ERROR
    if(button_is_hold_1s(3)) {
        STATUS = ERROR;
        setTrafficLight(STATE_ALL_OFF);
    }
}
