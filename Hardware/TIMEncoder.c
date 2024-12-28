#include "stm32f10x.h"                  // Device header
#include "TIMEncoder.h"

/**
  * 函    数：编码器初始化
  * 参    数：无
  * 返 回 值：无
  */
void TIM_Encoder_Init(void)
{
	/*开启时钟*/
	RCC_APB1PeriphClockCmd(TIMEncoder_TIM_CLK, ENABLE);			//开启TIM3的时钟
	RCC_APB2PeriphClockCmd(TIMEncoder_GPIO_CLK_A|TIMEncoder_GPIO_CLK_B|TIMEncoder_GPIO_CLK_Dwon, ENABLE);			//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = TIMEncoder_GPIO_PIN_A ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TIMEncoder_GPIO_PORT_A, &GPIO_InitStructure);							//将PA6和PA7引脚初始化为上拉输入
	
		/*GPIO初始化*/
	GPIO_InitStructure.GPIO_Pin =  TIMEncoder_GPIO_PIN_B;
	GPIO_Init(TIMEncoder_GPIO_PORT_B, &GPIO_InitStructure);							//将PA6和PA7引脚初始化为上拉输入
	
			/*GPIO初始化*/
	GPIO_InitStructure.GPIO_Pin =  TIMEncoder_GPIO_PIN_Dwon;
	GPIO_Init(TIMEncoder_GPIO_PORT_Dwon, &GPIO_InitStructure);							//将PA6和PA7引脚初始化为上拉输入
	

	/*时基单元初始化*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//定义结构体变量
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频，选择不分频，此参数用于配置滤波器时钟，不影响时基单元功能
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式，选择向上计数（无作用，也是被编码器托管）
	TIM_TimeBaseInitStructure.TIM_Period = TIMEncoder_TIM_Period;               //计数周期，即ARR的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = TIMEncoder_TIM_Prescaler;                //预分频器，即PSC的值
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            //重复计数器，高级定时器才会用到
	TIM_TimeBaseInit(TIMEncoder_TIM, &TIM_TimeBaseInitStructure);             //将结构体变量交给TIM_TimeBaseInit，配置TIM3的时基单元
	
	/*输入捕获初始化*/
	TIM_ICInitTypeDef TIM_ICInitStructure;							//定义结构体变量
	TIM_ICStructInit(&TIM_ICInitStructure);							//结构体初始化，若结构体没有完整赋值
																	//则最好执行此函数，给结构体所有成员都赋一个默认值
																	//避免结构体初值不确定的问题
	TIM_ICInitStructure.TIM_Channel = TIMEncoder_TIM_Channel_A;				//选择配置定时器通道1
	TIM_ICInitStructure.TIM_ICFilter = TIMEncoder_TIM_ICFilter_A;							//输入滤波器参数，可以过滤信号抖动
	TIM_ICInit(TIM3, &TIM_ICInitStructure);							//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
	
	TIM_ICInitStructure.TIM_Channel = TIMEncoder_TIM_Channel_B;				//选择配置定时器通道2
	TIM_ICInitStructure.TIM_ICFilter = TIMEncoder_TIM_ICFilter_B;							//输入滤波器参数，可以过滤信号抖动
	TIM_ICInit(TIM3, &TIM_ICInitStructure);							//将结构体变量交给TIM_ICInit，配置TIM3的输入捕获通道
	
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;		//后面也会配置，这里写不写都无所谓，极性，此时参数的Rising和Falling已经不代表上升沿和下降沿了，而是代表是否反相
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;			//与编码器无关，捕获预分频，选择不分频，每次信号都触发捕获
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;	//与编码器无关，输入信号交叉，选择直通，不交叉
	/*编码器接口配置*/
	TIM_EncoderInterfaceConfig(TIMEncoder_TIM, TIMEncoder_TIM_EncoderMode, TIMEncoder_ICPolarity_A, TIMEncoder_ICPolarity_B);
																	//配置编码器模式以及两个输入通道是否反相
																	//注意此时参数的Rising和Falling已经不代表上升沿和下降沿了，而是代表是否反相
																	//此函数必须在输入捕获初始化之后进行，否则输入捕获的配置会覆盖此函数的部分配置
	
	/*TIM使能*/
	TIM_Cmd(TIMEncoder_TIM, ENABLE);			//使能TIM3，定时器开始运行
}

