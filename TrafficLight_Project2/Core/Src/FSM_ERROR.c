#include "FSM_ERROR.h"
#include "GLOBAL.h"
#include "STATUS_LIGHT.h"
#include "BUTTON.h"


void FSM_ERROR_RUN() {
    // Nhấp nháy đèn vàng
    if (getTimerFlag(TIMER_BLINK) == 1) {
        setTimer(TIMER_BLINK, 500);

        if (blink_state == 0) {
            setTrafficLight(STATE_ALL_YELLOW);
            blink_state = 1;
        } else {
            setTrafficLight(STATE_ALL_OFF);
            blink_state = 0;
        }
    }

    // Giữ BTN0 1s -> AUTO
    if(button_is_hold_1s(0)) {
        STATUS = AUTO;
        // Reset trạng thái Auto
        fsm_auto_state = STATE_RED1_GREEN2;
        remaining_time_road1 = time_red;
        remaining_time_road2 = time_green;
        setTimer(TIMER_FSM_AUTO, time_green * 1000);
    }

    // Giữ BTN1 1s -> MANUAL
    if(button_is_hold_1s(1)) {
    	mode_manual_phase = 0;
        STATUS = MANUAL;
    }
}
