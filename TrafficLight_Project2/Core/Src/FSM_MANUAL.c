#include "FSM_MANUAL.h"
#include "GLOBAL.h"
#include "STATUS_LIGHT.h"
#include "BUTTON.h"

// 0: Red, 1: Yellow, 2: Green
int mode_manual_phase = 0;
int temp_value = 0;
int is_initialized = 0;

void FSM_MANUAL_RUN() {
// --- 1. Initialization (Run Once) ---
	if (is_initialized == 0) {
		switch (mode_manual_phase) {
			case 0: temp_value = time_red; break;
			case 1: temp_value = time_yellow; break;
			case 2: temp_value = time_green; break;
		}
		is_initialized = 1;
	}

	// --- 2. Blink Logic ---
	if (getTimerFlag(TIMER_BLINK) == 1) {
		setTimer(TIMER_BLINK, 500);
		static int blink = 0;
		blink = !blink;

		if (blink) {
			switch (mode_manual_phase) {
				case 0: setTrafficLight(STATE_ALL_RED); break;
				case 1: setTrafficLight(STATE_ALL_YELLOW); break;
				case 2: setTrafficLight(STATE_ALL_GREEN); break;
			}
		} else {
			setTrafficLight(STATE_ALL_OFF);
		}
	}

	// --- 3. LCD Variables Update ---
	remaining_time_road1 = temp_value;
	remaining_time_road2 = mode_manual_phase;

	// --- 4. Button Logic (Switch-Case) ---

	// Nút chuyển chế độ (Luôn hoạt động)
	if (button_is_pressed(0)) {
		mode_manual_phase++;
		if (mode_manual_phase > 2) mode_manual_phase = 0;
		is_initialized = 0; // Trigger reload
		return;
	}

	// Nút thoát (Giữ 1s)
	if (button_is_hold_1s(0)) {
		STATUS = AUTO;
		fsm_auto_state = STATE_RED1_GREEN2;
		remaining_time_road1 = time_red;
		remaining_time_road2 = time_green;
		setTimer(TIMER_FSM_AUTO, time_green * 1000);
		is_initialized = 0;
		return;
	}
    if(button_is_hold_1s(3)) {
        STATUS = ERROR;
        setTrafficLight(STATE_ALL_OFF);
    }

	// Nút chỉnh sửa (Tùy thuộc vào Phase)
	switch (mode_manual_phase) {
		case 0: // --- EDIT RED ---
			if (button_is_pressed(1) || button_is_hold_fast_tick(1)) {
				if (++temp_value > 99) temp_value = 5;
			}
			if (button_is_pressed(2) || button_is_hold_fast_tick(2)) {
				if (--temp_value < 5) temp_value = 99;
			}
			if (button_is_pressed(3)) { // SET
				time_red = temp_value;
				time_green = time_red - 2; // Auto calc Green
				// time_yellow = 2; // Fixed
			}
			break;

		case 1: // --- VIEW YELLOW ---
			// Read-only: No action for BTN1, BTN2, BTN3
			break;

		case 2: // --- EDIT GREEN ---
			if (button_is_pressed(1) || button_is_hold_fast_tick(1)) {
				if (++temp_value > 97) temp_value = 3;
			}
			if (button_is_pressed(2) || button_is_hold_fast_tick(2)) {
				if (--temp_value < 3) temp_value = 97;
			}
			if (button_is_pressed(3)) { // SET
				time_green = temp_value;
				time_red = time_green + 2; // Auto calc Red
			}
			break;
	}
}
