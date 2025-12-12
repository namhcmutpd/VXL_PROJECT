/*
 * STATUS_LIGHT.c
 * Created on: Oct 30, 2025
 * Author: NAM
 */

#include "STATUS_LIGHT.h"
#include "GLOBAL.h"
#include "main.h"

// Hàm gửi tín hiệu 2 bit
void writeTrafficLight1(int color_code) {
    HAL_GPIO_WritePin(LIGHT1_PIN_A_GPIO_Port, LIGHT1_PIN_A_Pin, (color_code & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LIGHT1_PIN_B_GPIO_Port, LIGHT1_PIN_B_Pin, (color_code & 0x02) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

void writeTrafficLight2(int color_code) {
    HAL_GPIO_WritePin(LIGHT2_PIN_A_GPIO_Port, LIGHT2_PIN_A_Pin, (color_code & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LIGHT2_PIN_B_GPIO_Port, LIGHT2_PIN_B_Pin, (color_code & 0x02) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

// Bảng mã màu (Thử nghiệm thực tế nếu sai màu thì đảo lại ở đây)
#define CODE_OFF    3
#define CODE_YELLOW 1
#define CODE_GREEN 	2
#define CODE_RED  	0

void setTrafficLight(int state) {
    switch (state) {
        case STATE_RED1_GREEN2:
            writeTrafficLight1(CODE_RED);
            writeTrafficLight2(CODE_GREEN);
            break;

        case STATE_RED1_YELLOW2:
            writeTrafficLight1(CODE_RED);
            writeTrafficLight2(CODE_YELLOW);
            break;

        case STATE_GREEN1_RED2:
            writeTrafficLight1(CODE_GREEN);
            writeTrafficLight2(CODE_RED);
            break;

        case STATE_YELLOW1_RED2:
            writeTrafficLight1(CODE_YELLOW);
            writeTrafficLight2(CODE_RED);
            break;

        case STATE_ALL_OFF:
            writeTrafficLight1(CODE_OFF);
            writeTrafficLight2(CODE_OFF);
            break;
        case STATE_ALL_YELLOW:
			writeTrafficLight1(CODE_YELLOW);
			writeTrafficLight2(CODE_YELLOW);
			break;
        case STATE_ALL_RED:
			writeTrafficLight1(CODE_RED);
			writeTrafficLight2(CODE_RED);
			break;
        case STATE_ALL_GREEN:
			writeTrafficLight1(CODE_GREEN);
			writeTrafficLight2(CODE_GREEN);
			break;
        default:
            break;
    }
}
