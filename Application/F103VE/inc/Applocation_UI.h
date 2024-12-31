#ifndef __APP_UI_H
#define __APP_UI_H
#include "stm32f10x.h"

// 双向链表节点结构体，代表菜单项目
typedef struct MenuItem {
    char label[20];
    struct MenuItem* parent;
    struct MenuItem* subItems;
    struct MenuItem* next;
    struct MenuItem* prev;
    int isLeaf;
} MenuItem;

void OLED_UI_Init(void);
void UI_Display(void);
#endif