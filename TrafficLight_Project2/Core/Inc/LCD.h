/*
 * LCD.h
 *
 *  Created on: Dec 10, 2025
 *      Author: NAM
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f1xx_hal.h"

#define LCD_ADDR (0x21 << 1)
// Các hàm điều khiển
void lcd_init(void);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void lcd_put_cur(int row, int col);
void lcd_clear(void);
void updateLCD(void);
#endif /* INC_LCD_H_ */
