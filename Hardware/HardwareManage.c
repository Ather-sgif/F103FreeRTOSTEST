#include "HardwareManage.h"


void vSystemHardwareDriverInit(void)
{
	OLED_I2C_Init();
	TIM_Encoder_Init();
		
}