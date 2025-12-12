/*
 * SOFTWARE_TIMER.h
 * Created on: Oct 30, 2025
 * Author: NAM
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

// Định nghĩa số lượng Timer tối đa
#define TIMER_LIMIT 10

// Khai báo mảng cờ (flag)
extern int timer_flag[TIMER_LIMIT];

// Nguyên mẫu hàm
void setTimer(int index, int duration);
void timer_run();
int getTimerFlag(int index);

#endif /* INC_SOFTWARE_TIMER_H_ */
