#ifndef __APP_UI_H
#define __APP_UI_H
#include "stm32f10x.h"
typedef struct UIElement {
    char text[20];
    uint8_t image; // 图像数据
    struct UIElement *prev;
    struct UIElement *next;
} UIElement;

void OLED_UI_Init(void);
void UI_Test(void);
#endif