/*
 * SOFTWARE_TIMER.c
 *
 *  Created on: Oct 30, 2025
 *      Author: NAM
 */

#include "SOFTWARE_TIMER.h"
#include "GLOBAL.h" // Để lấy giá trị TICK

// Khai báo mảng đếm và cờ
int timer_counter[TIMER_LIMIT];
int timer_flag[TIMER_LIMIT];

// Hàm cài đặt timer
void setTimer(int index, int duration) {
    // duration là thời gian (ms), TICK là chu kỳ ngắt (ms)
    timer_counter[index] = duration / TICK;
    timer_flag[index] = 0;
}

// Hàm chạy trong ngắt timer (System Tick)
void timer_run() {
    for (int i = 0; i < TIMER_LIMIT; i++) {
        if (timer_counter[i] > 0) {
            timer_counter[i]--;
            if (timer_counter[i] <= 0) {
                timer_flag[i] = 1;
            }
        }
    }
}

// Hàm kiểm tra cờ timer (trả về int để khớp với header)
int getTimerFlag(int index) {
    if (timer_flag[index] == 1) {
        timer_flag[index] = 0;
        return 1;
    }
    return 0;
}
