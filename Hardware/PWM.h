#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"                  // Device header
//GPIO配置
#define PWM_Pin         GPIO_Pin_2
#define PWM_GPIO        GPIOA
#define PWM_CLK         RCC_APB2Periph_GPIOA

//TIM时钟源配置
#define PWM_TIM_CLK    	    RCC_APB1Periph_TIM2			 /* PWM使用的定时器时钟 */
#define PWM_TIM    	        TIM2			               /* PWM使用的定时器 */
#define PWM_TIM_Period    	 (20000 - 1)			         /* PWM使用的定时器的定时周期ARR */
#define PWM_TIM_Prescaler    (72 - 1)			             /* PWM使用的定时器的预分频器psc*/

//TIM时钟源配置
#define PWM_TIM_OCMode    	     TIM_OCMode_PWM1			             /* PWM输出模式 */
#define PWM_TIM_OCPolarity    	 TIM_OCPolarity_High			         /* PWM输出的极性 */
#define PWM_TIM_CRR    	         0			             /* PWM初始的CRR值 */

void PWM_Init(void);
void PWM_SetCompare3(uint16_t Compare);

















#endif