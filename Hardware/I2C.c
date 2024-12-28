#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "I2C.h"
/**
  * 函    数：I2C初始化
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数需要用户实现内容，实现SCL和SDA引脚的初始化
  */
void OLED_I2C_Init(void)
{
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(OLED_I2C_SCL_GPIO_CLK, ENABLE);	//开启GPIOB的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = OLED_I2C_SCL_Pin ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_I2C_SCL_GPIO, &GPIO_InitStructure);					//将PB10和PB11引脚初始化为开漏输出
	
	/*开启时钟*/
	RCC_APB2PeriphClockCmd(OLED_I2C_SDA_GPIO_CLK, ENABLE);	//开启GPIOB的时钟
	/*GPIO初始化*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = OLED_I2C_SDA_Pin ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(OLED_I2C_SDA_GPIO, &GPIO_InitStructure);					//将PB10和PB11引脚初始化为开漏输出
	
	/*设置默认电平*/
	GPIO_SetBits(OLED_I2C_SDA_GPIO,OLED_I2C_SDA_Pin);		//设置PB10和PB11引脚初始化后默认为高电平（释放总线状态）
	GPIO_SetBits(OLED_I2C_SCL_GPIO,OLED_I2C_SCL_Pin);
}
/**
* 函    数：SDA设置为高电平
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
void OLED_I2C_SDA_High(void)
{
	GPIO_SetBits(OLED_I2C_SDA_GPIO,OLED_I2C_SDA_Pin);
}
/**
  * 函    数：SDA设置为低电平
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
void OLED_I2C_SDA_Low(void)
{
	GPIO_ResetBits(OLED_I2C_SDA_GPIO,OLED_I2C_SDA_Pin);
}
/**
* 函    数：SCL设置为高电平
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
void OLED_I2C_SCL_High(void)
{
	GPIO_SetBits(OLED_I2C_SCL_GPIO,OLED_I2C_SCL_Pin);
}
/**
  * 函    数：SCL设置为低电平
  * 参    数：无
  * 返 回 值：无
  * 注意事项：无
  */
void OLED_I2C_SCL_Low(void)
{
	GPIO_ResetBits(OLED_I2C_SCL_GPIO,OLED_I2C_SCL_Pin);
}
