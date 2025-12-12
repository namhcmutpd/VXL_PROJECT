/*
 * LCD.c
 *
 *  Created on: Dec 10, 2025
 *      Author: NAM
 */

#include "GLOBAL.h"

// Sử dụng biến handle I2C được khai báo bên main.c
extern I2C_HandleTypeDef hi2c1;
extern int temp_value;

typedef struct {
    int status;
    int road1_time;
    int road2_time;
    int auto_state;
    int manual_mode_idx;
    int manual_temp_val;
    int error_blink_state;
} LCD_Cache_t;

static LCD_Cache_t lcd_cache = {-1, -1, -1, -1, -1, -1, -1};
static char lcd_buffer[20];

static void LCD_Draw_Auto(void);
static void LCD_Draw_Manual(void);
static void LCD_Draw_Error(void);
static void LCD_Reset_Cache(void);

void lcd_send_cmd(char cmd)
{
  char data_u, data_l;
  uint8_t data_t[4];
  data_u = (cmd & 0xf0);
  data_l = ((cmd << 4) & 0xf0);
  data_t[0] = data_u | 0x0C;  //en=1, rs=0
  data_t[1] = data_u | 0x08;  //en=0, rs=0
  data_t[2] = data_l | 0x0C;  //en=1, rs=0
  data_t[3] = data_l | 0x08;  //en=0, rs=0
  HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, (uint8_t *)data_t, 4, 100);
}

void lcd_send_data(char data)
{
  char data_u, data_l;
  uint8_t data_t[4];
  data_u = (data & 0xf0);
  data_l = ((data << 4) & 0xf0);
  data_t[0] = data_u | 0x0D;  //en=1, rs=1
  data_t[1] = data_u | 0x09;  //en=0, rs=1
  data_t[2] = data_l | 0x0D;  //en=1, rs=1
  data_t[3] = data_l | 0x09;  //en=0, rs=1
  HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, (uint8_t *)data_t, 4, 100);
}

void lcd_clear(void)
{
    lcd_send_cmd(0x80);
    for (int i = 0; i < 16 * 2; i++) lcd_send_data(' ');
    lcd_send_cmd(0x80);
}

void lcd_put_cur(int row, int col)
{
    switch (row) {
        case 0: col |= 0x80; break;
        case 1: col |= 0xC0; break;
    }
    lcd_send_cmd(col);
}

void lcd_init(void)
{
	// 4 bit initialisation
	HAL_Delay(50);
	lcd_send_cmd(0x30); HAL_Delay(5);
	lcd_send_cmd(0x30); HAL_Delay(1);
	lcd_send_cmd(0x30); HAL_Delay(10);
	lcd_send_cmd(0x20); HAL_Delay(10); // 4 bit mode

    // Display initialisation
	lcd_send_cmd(0x28); HAL_Delay(1); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	lcd_send_cmd(0x08); HAL_Delay(1); // Display on/off control --> D=0,C=0, B=0  ---> display off
	lcd_send_cmd(0x01); HAL_Delay(1); // Clear display
	lcd_send_cmd(0x06); HAL_Delay(1); // Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	lcd_send_cmd(0x0C); //Display on/off control --> D = 1, C = 0, B = 0
}

void lcd_send_string(char *str)
{
	while (*str) lcd_send_data(*str++);
}

static const char* get_color_str(int fsm_state, int road_idx)
{
    if (road_idx == 1) {
        if (fsm_state == STATE_RED1_GREEN2 || fsm_state == STATE_RED1_YELLOW2) return "RED  ";
        if (fsm_state == STATE_GREEN1_RED2) return "GREEN";
        return "AMBER";
    } else {
        if (fsm_state == STATE_GREEN1_RED2 || fsm_state == STATE_YELLOW1_RED2) return "RED  ";
        if (fsm_state == STATE_RED1_GREEN2) return "GREEN";
        return "AMBER";
    }
}

static void LCD_Draw_Auto(void)
{
    if (lcd_cache.road1_time == remaining_time_road1 &&
        lcd_cache.road2_time == remaining_time_road2 &&
        lcd_cache.auto_state == fsm_auto_state) {
        return;
    }

    lcd_put_cur(0, 0);
    sprintf(lcd_buffer, "R1: %s %02d   ", get_color_str(fsm_auto_state, 1), remaining_time_road1);
    lcd_send_string(lcd_buffer);

    lcd_put_cur(1, 0);
    sprintf(lcd_buffer, "R2: %s %02d   ", get_color_str(fsm_auto_state, 2), remaining_time_road2);
    lcd_send_string(lcd_buffer);

    lcd_cache.road1_time = remaining_time_road1;
    lcd_cache.road2_time = remaining_time_road2;
    lcd_cache.auto_state = fsm_auto_state;
}

static void LCD_Draw_Manual(void)
{
    if (lcd_cache.manual_mode_idx == mode_manual_phase &&
        lcd_cache.manual_temp_val == temp_value) {
        return;
    }

    lcd_put_cur(0, 0);
    lcd_send_string("MODE: MANUAL    ");

    lcd_put_cur(1, 0);
    char ptr_r = (mode_manual_phase == 0) ? '*' : ' ';
    char ptr_y = (mode_manual_phase == 1) ? '*' : ' ';
    char ptr_g = (mode_manual_phase == 2) ? '*' : ' ';

    int disp_r = (mode_manual_phase == 0) ? temp_value : time_red;
    int disp_y = (mode_manual_phase == 1) ? temp_value : time_yellow;
    int disp_g = (mode_manual_phase == 2) ? temp_value : time_green;

    sprintf(lcd_buffer, "R:%c%02d Y:%c%02d G:%c%02d", ptr_r, disp_r, ptr_y, disp_y, ptr_g, disp_g);
    lcd_send_string(lcd_buffer);

    lcd_cache.manual_mode_idx = mode_manual_phase;
    lcd_cache.manual_temp_val = temp_value;
}

static void LCD_Draw_Error(void)
{
    if (lcd_cache.error_blink_state == blink_state) return;
    if (blink_state == 1) {
        lcd_put_cur(0, 0); lcd_send_string("!!!ERROR MODE!!!");
        lcd_put_cur(1, 0); lcd_send_string("!!CALL SUPPORT!!");
    } else lcd_clear();

    lcd_cache.error_blink_state = blink_state;
}

static void LCD_Reset_Cache(void)
{
    lcd_cache.status = -1;
    lcd_cache.road1_time = -1;
    lcd_cache.auto_state = -1;
    lcd_cache.manual_mode_idx = -1;
    lcd_cache.error_blink_state = -1;
    lcd_clear();
}

void updateLCD(void)
{
    if (lcd_cache.status != STATUS) {
        LCD_Reset_Cache();
        lcd_cache.status = STATUS;
    }

    switch (STATUS) {
        case AUTO:
            LCD_Draw_Auto();
            break;
        case MANUAL:
            LCD_Draw_Manual();
            break;
        case ERROR:
            LCD_Draw_Error();
            break;
        default:
            break;
    }
}


