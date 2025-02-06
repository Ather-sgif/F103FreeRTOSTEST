/*
 * @Author: ZJP
 * @Date: 2024-12-28 10:04:40
 * @LastEditTime: 2025-02-06 16:48:36
 * @LastEditors: ZJP
 * @Description: ui显示函数
 * @FilePath: \stm32f103VE-free\Application\F103VE\src\Applocation_UI.c
 * 
 */
#include "I2C.h"
#include "u8g2.h"
#include "Delay.h"
#include "mui_u8g2.h"
#include "TIMEncoder.h"
#include "Application_TIMEncoder.h"
#include "Applocation_UI.h"
#include "MG90S_Servo.h"
#include <stdlib.h>
#include <stdio.h>
u8g2_t u8g2;
// 全局变量
MenuItem* current = NULL;   // 当前选中的菜单项
uint8_t edit_mode = 0;      // 参数编辑模式标志
int value_translate []= {0};  // 设置的参数显示到其它页面上
/**
 * @description: 在界面显示文本参数
 * @param {u8g2_t*} u8g2
 * @param {MenuItem*} p
 * @return {*}
 */
void current_show_text(u8g2_t* u8g2, MenuItem* p){

    if(p->name == "Main Menu"){
     u8g2_DrawStr(u8g2, 10, 15, "Angle:");
     u8g2_DrawStr(u8g2, 10, 25, "Angle:");
    }
    else if (p->name == "Set Time")
    {
        
    }
    else if (p->name == "Set Date")
    {
        
    }
}
void value_translate_write(int i,MenuItem* p)
{
    value_translate[i] = p->value;
}
// 示例回调函数
void set_brightness(int value) {
    // 这里实现实际的亮度设置代码
    // 例如：HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    //       __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, value);
    Servo_SetAngle(value);
}
// 创建新菜单项
MenuItem* create_menu_item(const char* name, MenuItem* parent, void (*action)(int)) {
    MenuItem* item = (MenuItem*)malloc(sizeof(MenuItem));
    strncpy(item->name, name, sizeof(item->name));
    item->value = 0;
    item->parent = parent;
    item->prev = NULL;
    item->next = NULL;
    item->child = NULL;
    item->action = action;
    return item;
}
void menu_init() {
    // 创建主菜单
    MenuItem* main_menu = create_menu_item("Main Menu", NULL, NULL);
    
    // 创建子菜单项
    MenuItem* time_set = create_menu_item("Set Time", main_menu, NULL);
    MenuItem* date_set = create_menu_item("Set Date", main_menu, NULL);
    MenuItem* brightness = create_menu_item("Brightness", main_menu, NULL);
    
    // 链接主菜单项
    main_menu->child = time_set;
    time_set->next = date_set;
    date_set->prev = time_set;
    date_set->next = brightness;
    brightness->prev = date_set;
    
    // 创建亮度子菜单
    brightness->child = create_menu_item("Level", brightness, set_brightness);
    brightness->child->value = 50;  // 默认亮度值
    value_translate_write(0,brightness->child);
    

    current = main_menu;  // 初始化当前菜单
}
// 处理按键输入
void handle_input(uint8_t key) {

    if(edit_mode) {
        // 参数编辑模式
        switch(key) {
            case 'L': current->value--; break;
            case 'R': current->value++; break;
            case 'E': 
                edit_mode = 0;
                if(current->action) current->action(current->value);
                current = current->parent;
                break;
        }
    } else {
        // 菜单导航模式
        switch(key) {
            case 'L': if(current->prev) current = current->prev; break;
            case 'R': if(current->next) current = current->next; break;
            case 'E': 
                if(current->child) {
                    current = current->child;
                } else if(current->parent) {
                    edit_mode = 1;
                }
                break;
        }
    }
}
// 显示菜单
void draw_menu(u8g2_t* u8g2) {
    u8g2_ClearBuffer(u8g2);
    
    if(edit_mode) {
        // 显示参数编辑界面
        u8g2_SetFont(u8g2, u8g2_font_ncenB14_tr);
        u8g2_DrawStr(u8g2, 10, 30, current->name);
        char val_str[16];
        sprintf(val_str, "%d", current->value);
        u8g2_DrawStr(u8g2, 90, 30, val_str);
    } else {
        // 显示常规菜单
        u8g2_SetFont(u8g2, u8g2_font_helvB10_tr);
        MenuItem* p = current->parent ? current->parent->child : current;
        // 显示同级菜单项
        uint8_t y = 12;
        while(p) {
            if(p == current) {
                u8g2_DrawBox(u8g2, 0, y-10, 128, 12);
                u8g2_SetDrawColor(u8g2, 0);
            }
            u8g2_DrawStr(u8g2, 5, y, p->name);
            if(p == current) {
                u8g2_SetDrawColor(u8g2, 1);
            }
            y += 13;
            p = p->next;
        }
    }
    
    u8g2_SendBuffer(u8g2);
}
/**
 * @description: u8g2的I2C传输函数
 * @param {u8x8_t} *u8x8
 * @param {uint8_t} msg
 * @param {uint8_t} arg_int
 * @param {void} *arg_ptr
 * @return {*}
 */
uint8_t u8g2_gpio_and_delay_stm32(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr)
{
	switch(msg){

		//Function which implements a delay, arg_int contains the amount of ms
		case U8X8_MSG_DELAY_MILLI:
		Delay_ms(arg_int);

		break;
		//Function which delays 10us
		case U8X8_MSG_DELAY_10MICRO:
    Delay_us(10);

		break;
		//Function which delays 100ns
		case U8X8_MSG_DELAY_100NANO:
		__NOP();

		break;
		
		case U8X8_MSG_GPIO_I2C_CLOCK:
			if (arg_int) OLED_I2C_SCL_High();
			else OLED_I2C_SCL_Low();

		break;

		case U8X8_MSG_GPIO_I2C_DATA:
			if (arg_int) OLED_I2C_SDA_High();
			else OLED_I2C_SDA_Low();

		break;

		default:
			return 0; //A message was received which is not implemented, return 0 to indicate an error
	}

	return 1; // command processed successfully.
}
/**
 * @description: u8g2初始化
 * @param {u8g2_t} *u8g2
 * @return {*}
 */
void u8g2Init(u8g2_t *u8g2)
{
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_sw_i2c, u8g2_gpio_and_delay_stm32);  // 初始化 u8g2 结构体
	u8g2_InitDisplay(u8g2); // 根据所选的芯片进行初始化工作，初始化完成后，显示器处于关闭状态
	u8g2_SetPowerSave(u8g2, 0); // 打开显示器
	u8g2_ClearBuffer(u8g2);
}

/**
 * @description: UI显示
 * @return {*}
 */
void UI_Display(void)
{
  if(eTIMEncoderExternState() == TIMEncoderTurnRight)
  {
    handle_input('R');
  }
  else if(eTIMEncoderExternState() == TIMEncoderTurnLeft)
  {
    handle_input('L'); 
  }
  else if(eTIMEncoderExternState() == TIMEncoderSingleDown)
  {
    handle_input('E');
  }
  draw_menu(&u8g2);
 }
/**
 * @description: UI初始化
 * @return {*}
 */
void OLED_UI_Init(void)
{
     menu_init();
	u8g2Init(&u8g2);
}


