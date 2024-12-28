/*
 * @Author: ZJP
 * @Date: 2024-12-26 14:15:42
 * @LastEditTime: 2024-12-27 18:59:26
 * @LastEditors: ZJP
 * @Description: 按键处理应用函数
 * @FilePath: \stm32f103VE-free\Application\F103VE\src\Application_TIMEncoder.c
 * 
 */
#include "Application_TIMEncoder.h"
static eTIMEncoderState TIMEncoderState = TIMEncoderUp;

/*******************************************************************************
* Function Name  : vTIMEncoderCheckOperation
* Description    : 检测按键的状态 并做相应的动作 至少以20ms的周期调用一次
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

void vTIMEncoderCheckOperation(void)
{
	 eTIMEncoderState TIMEncoderStateKey;
	 eTIMEncoderState TIMEncoderRotateState;
	
	 TIMEncoderStateKey = eTIMEncoder1State();
	 TIMEncoderRotateState = eTIMEncoderTurnState();
	 if(TIMEncoderStateKey != TIMEncoderUp)
	 {
		 		 
	   TIMEncoderState = TIMEncoderStateKey;
		 
	 }
	if(TIMEncoderRotateState != TIMEncoderUp)
	{
       TIMEncoderState =  TIMEncoderRotateState;       
	}
	else 
	{
		TIMEncoderState = TIMEncoderUp;
	}
	
}
/*******************************************************************************
* Function Name  : eTIMEncoderExternState
* Description    : 外部调用返回的按键值
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
eTIMEncoderState eTIMEncoderExternState(void)
{
    return TIMEncoderState;
}
/*******************************************************************************
* Function Name  : eTIMEncoder1State
* Description    : 返回按键键值
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
eTIMEncoderState eTIMEncoder1State(void)
{
		static uint8_t Button_PC = 0; //状态指示
		static OS_TimeStruct KeyDownTime = {0};//非阻塞时间结构体

   switch( Button_PC )
   {
       case 0 :             
           if( KEY_1_PIN != ( uint8_t )Bit_RESET)
           {                
               return TIMEncoderUp; //按键没有按下       
           }
           KeyDownTime = GetOSRunTimeNow(  );//按键按下后 记录当前时间
           Button_PC = 1;              
       case 1:  
           if( KEY_1_PIN == ( uint8_t )Bit_RESET) //等待按键释放
           {             
               return TIMEncoderUp;//按键一直没有释放        
           }
           /*按键已经释放*/
           if( SingleTimeoutCheck( KeyDownTime, 0, 0, 20 ) == NotTimeOut )   //消抖
           {
               Button_PC = 0;//按下时间小于20ms  认为是抖动 识别为没有按键按下
               return TIMEncoderUp;  
           } 
           else if( SingleTimeoutCheck( KeyDownTime, 0, 2, 0 ) == NotTimeOut )   //按下小于2s            
           {
               KeyDownTime = GetOSRunTimeNow(  );//重新获取当前时间
               Button_PC = 3;
               return TIMEncoderUp;
           }
           else if( SingleTimeoutCheck( KeyDownTime, 0, 1, 0 ) == NotTimeOut ) 
           {
               KeyDownTime = GetOSRunTimeNow(  );
               Button_PC = 3;
               return TIMEncoderUp;
           }
           Button_PC = 0;
      case 3://双击检测 老铁666
           if( KEY_1_PIN != ( uint8_t )Bit_RESET)//没有检测到按下
           {                
               if(SingleTimeoutCheck( KeyDownTime, 0, 0, 300 ) == TimeOut)//300ms内 依然没有等待到第二次按键按下.
               {
                   Button_PC = 0;
                   return TIMEncoderSingleDown;//返回按键单击2S
               }
               return TIMEncoderUp;        
           }
           else //300ms内检测到第二次按键按下
           {
               KeyDownTime = GetOSRunTimeNow(  );//重新获取当前时间
               Button_PC = 4;                  
           }
          break;
      case 4://检测双击时间
           if( KEY_1_PIN == ( uint8_t )Bit_RESET) //按键还没松开
           {             
               return TIMEncoderUp;        
           }
           /*按键已经释放*/
           if( SingleTimeoutCheck( KeyDownTime, 0, 2, 0 ) == NotTimeOut ) 
           {
               Button_PC = 0;
               return TIMEncoderDoubleDown;//第二次按键时间在2秒内  完成双击！给劲 老铁
           }
           else//超过2秒  双击失败 欧力给
           {
               Button_PC = 0;
               return TIMEncoderUp;
           }
      default:  
          break;   
   }
   return TIMEncoderUp;
}
/*******************************************************************************
* Function Name  : eTIMEncoderTurnState
* Description    : 返回旋转的方向,以及触发多少次算一次
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
eTIMEncoderState eTIMEncoderTurnState(void)
{
	
	static int  TIMEncoderRotate = 0; 
	if(TIMEncoderRotate == 0)
	   TIMEncoderRotate = TIM_GetCounter(TIM3);//获取编码器计数量
       TIM_SetCounter(TIM3, 0);//获取编码器计数清零


	/*计数之后的处理*/ 
	if(TIMEncoderRotate > 0) //编码器正数计算
	{
      TIMEncoderRotate -= TIMEncoderEnterTimes;//减少编码器计数值
	  if(TIMEncoderRotate >= -(TIMEncoderEnterTimes-1) && TIMEncoderRotate <= (TIMEncoderEnterTimes-1)) //小于设置的触发次数，则清零
	  {
		TIMEncoderRotate = 0;
		return TIMEncoderUp;
	  }
	  return TIMEncoderTurnRight;
	}
	else if(TIMEncoderRotate < 0)//编码器负数计算
	{
      TIMEncoderRotate += TIMEncoderEnterTimes;
	  if(TIMEncoderRotate >= -(TIMEncoderEnterTimes-1) && TIMEncoderRotate <= (TIMEncoderEnterTimes-1)) 
	  {
		TIMEncoderRotate = 0;
		return TIMEncoderUp;
	  }
	  return TIMEncoderTurnLeft;
	}
	return TIMEncoderUp;
 
}