#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

// --- 1. BUTTONS (GROVE PORTS A0 & A2) ---
// Module 1 cắm cổng A0 -> Chân A0 (PA0) và A1 (PA1)
#define BTN_MODE_Pin GPIO_PIN_0
#define BTN_MODE_Port GPIOA
#define BTN_UP_Pin GPIO_PIN_1
#define BTN_UP_Port GPIOA

// Module 2 cắm cổng A2 -> Chân A2 (PA4) và A3 (PB0)
#define BTN_DOWN_Pin GPIO_PIN_4
#define BTN_DOWN_Port GPIOA
#define BTN_ER_Pin GPIO_PIN_0
#define BTN_ER_Port GPIOB

// --- 2. STATUS LED ---
#define BLINKY_Pin GPIO_PIN_5
#define BLINKY_GPIO_Port GPIOA

// --- 3. TRAFFIC LIGHTS (2-BIT MODE - GROVE PORTS D3 & D5) ---
// Đèn 1 nối cổng D7 -> Chân PA8 và PA9
#define LIGHT1_PIN_A_Pin GPIO_PIN_8
#define LIGHT1_PIN_A_GPIO_Port GPIOA
#define LIGHT1_PIN_B_Pin GPIO_PIN_9
#define LIGHT1_PIN_B_GPIO_Port GPIOA

// Đèn 2 nối cổng D5 -> Chân D5 (PB4) và D6 (PB10)
#define LIGHT2_PIN_A_Pin GPIO_PIN_4
#define LIGHT2_PIN_A_GPIO_Port GPIOB
#define LIGHT2_PIN_B_Pin GPIO_PIN_10
#define LIGHT2_PIN_B_GPIO_Port GPIOB

// UART
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
