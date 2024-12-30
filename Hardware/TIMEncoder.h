#ifndef __TIMENCODER_H
#define __TIMENCODER_H
#include "stm32f10x.h"
/* 定义编码器连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的编码器A相和B相的引脚及按下 */

#define TIMEncoder_GPIO_PORT_A    	GPIOA			              /* GPIO端口 */
#define TIMEncoder_GPIO_CLK_A 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define TIMEncoder_GPIO_PIN_A		    GPIO_Pin_6			        /* 连接到编码器A相的GPIO */

#define TIMEncoder_GPIO_PORT_B    	GPIOB			              /* GPIO端口 */
#define TIMEncoder_GPIO_CLK_B 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define TIMEncoder_GPIO_PIN_B		    GPIO_Pin_7			        /* 连接到编码器B相的GPIO */

#define TIMEncoder_GPIO_PORT_Dwon    	GPIOA			              /* GPIO端口 */
#define TIMEncoder_GPIO_CLK_Dwon 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
#define TIMEncoder_GPIO_PIN_Dwon		  GPIO_Pin_5			        /* 连接到编码器按下的GPIO */

#define TIMEncoder_TIM_CLK    	    RCC_APB1Periph_TIM3			 /* 编码器使用的定时器时钟 */
#define TIMEncoder_TIM    	        TIM3			               /* 编码器使用的定时器 */
#define TIMEncoder_TIM_Period    	  (65536 - 1)			         /* 编码器使用的定时器的定时周期ARR */
#define TIMEncoder_TIM_Prescaler    (1 - 1)			             /* 编码器使用的定时器的预分频器psc*/

#define TIMEncoder_TIM_Channel_A     TIM_Channel_1			       /* 编码器使用的A相通道 */
#define TIMEncoder_TIM_Channel_B     TIM_Channel_2			       /* 编码器使用的B相通道 */

#define TIMEncoder_TIM_ICFilter_A    0xf			       /* 编码器使用的A相通道滤波参数 */
#define TIMEncoder_TIM_ICFilter_B    0xf			       /* 编码器使用的B相通道滤波参数 */


#define TIMEncoder_TIM_EncoderMode    TIM_EncoderMode_TI12			       /* 配置编码器模式 */

#define TIMEncoder_ICPolarity_A    TIM_ICPolarity_Rising			       /* 配置编码器是否反相 */
#define TIMEncoder_ICPolarity_B    TIM_ICPolarity_Rising			       /* 配置编码器是否反相 */

void TIM_Encoder_Init(void);

#endif