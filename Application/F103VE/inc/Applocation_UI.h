#ifndef __APP_UI_H
#define __APP_UI_H
#include "stm32f10x.h"

// 菜单项结构体
typedef struct MenuItem {
    char name[16];          // 菜单显示名称
    int value;              // 参数值
    struct MenuItem* parent;// 父菜单
    struct MenuItem* prev;  // 前一个兄弟菜单
    struct MenuItem* next;  // 下一个兄弟菜单
    struct MenuItem* child; // 子菜单
    void (*action)(int);    // 参数修改回调函数
} MenuItem;

void OLED_UI_Init(void);
void UI_Display(void);
#endif