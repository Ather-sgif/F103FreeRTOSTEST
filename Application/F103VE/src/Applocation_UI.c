#include "I2C.h"
#include "u8g2.h"
#include "stm32f10x.h"
#include "Delay.h"
#include "mui_u8g2.h"
#include "TIMEncoder.h"
#include "Application_TIMEncoder.h"
u8g2_t u8g2;
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

void u8g2Init(u8g2_t *u8g2)
{
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_sw_i2c, u8g2_gpio_and_delay_stm32);  // 初始化 u8g2 结构体
	u8g2_InitDisplay(u8g2); // 根据所选的芯片进行初始化工作，初始化完成后，显示器处于关闭状态
	u8g2_SetPowerSave(u8g2, 0); // 打开显示器
	u8g2_ClearBuffer(u8g2);
}
int i = 0;
void UI_Test(void)
{
  
u8g2_FirstPage(&u8g2);
do
{
	u8g2_DrawCircle(&u8g2,63,31,i,U8G2_DRAW_ALL );  
}while (u8g2_NextPage(&u8g2));

if(eTIMEncoderExternState() == TIMEncoderSingleDown)
	  i++;
if(eTIMEncoderExternState() == TIMEncoderSingleDown)
      i--;
if(eTIMEncoderExternState() == TIMEncoderTurnRight)
	  i++;
if(eTIMEncoderExternState() ==TIMEncoderTurnLeft)
      i--;
if(i>=64||i<=0)
	 i = 0;
u8g2_SendBuffer(&u8g2);
}
void OLED_UI_Init(void)
{
	TIM_Encoder_Init();
	OLED_I2C_Init();
	u8g2Init(&u8g2);
}