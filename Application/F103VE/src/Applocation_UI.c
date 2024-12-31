/*
 * @Author: ZJP
 * @Date: 2024-12-28 10:04:40
 * @LastEditTime: 2024-12-31 16:56:58
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

u8g2_t u8g2;

// 当前菜单指针和当前选中项指针
MenuItem* currentMenu = NULL;
MenuItem* currentSelected = NULL;

//外部查看选择的那个函数
static u16 eMenu = 0;

/**
 * @description: 返回当前菜单选择项
 * @return {*}
 */
u16 checkMenu(void)
{
	return eMenu;
}
/**
 * @description: 菜单初始化函数
 * @return {*}
 */
MenuItem* createMenuItem(const char* label, int isLeaf) {
    MenuItem* item = (MenuItem*)malloc(sizeof(MenuItem));
    strcpy(item->label, label);
    item->parent = NULL;
    item->subItems = NULL;
    item->next = NULL;
    item->prev = NULL;
    item->isLeaf = isLeaf;
    return item;
}
/**
 * @description: 添加子菜单函数
 * @return {*}
 */
void addSubItem(MenuItem* parent, MenuItem* subItem) {
    subItem->parent = parent;
    if (parent->subItems == NULL) {
        parent->subItems = subItem;
    } else {
        MenuItem* current = parent->subItems;
        while (current->next!= NULL) {
            current = current->next;
        }
        current->next = subItem;
        subItem->prev = current;
    }
}
/**
 * @description: 菜单绘制函数
 * @return {*}
 */
void drawMenu(void) {
    u8g2_ClearBuffer(&u8g2);
    u8g2_SetFont(&u8g2, u8g2_font_ncenB08_tr);

    MenuItem* item = currentMenu->subItems;
    int y = 10;
    while (item!= NULL) {
        if (item == currentSelected) {
            u8g2_SetDrawColor(&u8g2, 2);
        } else {
            u8g2_SetDrawColor(&u8g2, 1);
        }
        u8g2_DrawStr(&u8g2, 10, y, item->label);
        item = item->next;
        y += 10;
    }

    u8g2_SendBuffer(&u8g2);
}
/**
 * @description: 按键处理函数
 * @return {*}
 */
void handleButtonPress(void) {
    if (eTIMEncoderExternState() == TIMEncoderTurnLeft) {    //左转，向左移动

            if (currentSelected->prev!= NULL) {
                currentSelected = currentSelected->prev;
            }
        
    }

    if (eTIMEncoderExternState() == TIMEncoderTurnRight) {   //右转，向右移动

            if (currentSelected->next!= NULL) {
                currentSelected = currentSelected->next;
			}
            
    }

    if (eTIMEncoderExternState() == TIMEncoderSingleDown) {  //按下选择键   

            if (currentSelected->isLeaf) {
                   eMenu = currentSelected->isLeaf;
            } else {
                currentMenu = currentSelected;
                currentSelected = currentMenu->subItems;
            }
    }

    if (eTIMEncoderExternState() == TIMEncoderDoubleDown) {  //双击返回上一级菜单

            if (currentMenu->parent!= NULL) {
                currentMenu = currentMenu->parent;
                MenuItem* temp = currentMenu->subItems;
				eMenu = currentSelected->isLeaf;
                while (temp!= NULL && temp!= currentSelected) {
                    temp = temp->next;
                }
                if (temp == NULL) {
                    currentSelected = currentMenu->subItems;
                }
        }
    }
}
/**
 * @description: 菜单初始化函数
 * @return {*}
 */
void Menu_Init(void)
{
	// 创建菜单
    MenuItem* root = createMenuItem("Main Menu", 0);
    MenuItem* subMenu1 = createMenuItem("Sub - Menu 1", 0);
    MenuItem* subMenu2 = createMenuItem("Sub - Menu 2", 0);
    MenuItem* leaf1 = createMenuItem("Leaf 1", 1);
    MenuItem* leaf2 = createMenuItem("Leaf 2", 1);
    MenuItem* leaf3 = createMenuItem("Leaf 3", 1);
	MenuItem* leaf4 = createMenuItem("Leaf 4", 1);

    addSubItem(root, subMenu1);
    addSubItem(root, subMenu2);
    addSubItem(subMenu1, leaf1);
    addSubItem(subMenu1, leaf2);
    addSubItem(subMenu2, leaf3);
	addSubItem(subMenu2, leaf4);

    currentMenu = root;
    currentSelected = root->subItems;
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

void UI_Display(void)
{
  handleButtonPress();
  drawMenu();
}
/**
 * @description: UI初始化
 * @return {*}
 */
void OLED_UI_Init(void)
{
	Menu_Init();
	u8g2Init(&u8g2);
}