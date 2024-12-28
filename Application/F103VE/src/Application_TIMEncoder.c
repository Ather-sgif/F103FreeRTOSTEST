/*
 * @Author: ZJP
 * @Date: 2024-12-26 14:15:42
 * @LastEditTime: 2024-12-27 18:59:26
 * @LastEditors: ZJP
 * @Description: ��������Ӧ�ú���
 * @FilePath: \stm32f103VE-free\Application\F103VE\src\Application_TIMEncoder.c
 * 
 */
#include "Application_TIMEncoder.h"
static eTIMEncoderState TIMEncoderState = TIMEncoderUp;

/*******************************************************************************
* Function Name  : vTIMEncoderCheckOperation
* Description    : ��ⰴ����״̬ ������Ӧ�Ķ��� ������20ms�����ڵ���һ��
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
* Description    : �ⲿ���÷��صİ���ֵ
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
* Description    : ���ذ�����ֵ
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
eTIMEncoderState eTIMEncoder1State(void)
{
		static uint8_t Button_PC = 0; //״ָ̬ʾ
		static OS_TimeStruct KeyDownTime = {0};//������ʱ��ṹ��

   switch( Button_PC )
   {
       case 0 :             
           if( KEY_1_PIN != ( uint8_t )Bit_RESET)
           {                
               return TIMEncoderUp; //����û�а���       
           }
           KeyDownTime = GetOSRunTimeNow(  );//�������º� ��¼��ǰʱ��
           Button_PC = 1;              
       case 1:  
           if( KEY_1_PIN == ( uint8_t )Bit_RESET) //�ȴ������ͷ�
           {             
               return TIMEncoderUp;//����һֱû���ͷ�        
           }
           /*�����Ѿ��ͷ�*/
           if( SingleTimeoutCheck( KeyDownTime, 0, 0, 20 ) == NotTimeOut )   //����
           {
               Button_PC = 0;//����ʱ��С��20ms  ��Ϊ�Ƕ��� ʶ��Ϊû�а�������
               return TIMEncoderUp;  
           } 
           else if( SingleTimeoutCheck( KeyDownTime, 0, 2, 0 ) == NotTimeOut )   //����С��2s            
           {
               KeyDownTime = GetOSRunTimeNow(  );//���»�ȡ��ǰʱ��
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
      case 3://˫����� ����666
           if( KEY_1_PIN != ( uint8_t )Bit_RESET)//û�м�⵽����
           {                
               if(SingleTimeoutCheck( KeyDownTime, 0, 0, 300 ) == TimeOut)//300ms�� ��Ȼû�еȴ����ڶ��ΰ�������.
               {
                   Button_PC = 0;
                   return TIMEncoderSingleDown;//���ذ�������2S
               }
               return TIMEncoderUp;        
           }
           else //300ms�ڼ�⵽�ڶ��ΰ�������
           {
               KeyDownTime = GetOSRunTimeNow(  );//���»�ȡ��ǰʱ��
               Button_PC = 4;                  
           }
          break;
      case 4://���˫��ʱ��
           if( KEY_1_PIN == ( uint8_t )Bit_RESET) //������û�ɿ�
           {             
               return TIMEncoderUp;        
           }
           /*�����Ѿ��ͷ�*/
           if( SingleTimeoutCheck( KeyDownTime, 0, 2, 0 ) == NotTimeOut ) 
           {
               Button_PC = 0;
               return TIMEncoderDoubleDown;//�ڶ��ΰ���ʱ����2����  ���˫�������� ����
           }
           else//����2��  ˫��ʧ�� ŷ����
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
* Description    : ������ת�ķ���,�Լ��������ٴ���һ��
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
eTIMEncoderState eTIMEncoderTurnState(void)
{
	
	static int  TIMEncoderRotate = 0; 
	if(TIMEncoderRotate == 0)
	   TIMEncoderRotate = TIM_GetCounter(TIM3);//��ȡ������������
       TIM_SetCounter(TIM3, 0);//��ȡ��������������


	/*����֮��Ĵ���*/ 
	if(TIMEncoderRotate > 0) //��������������
	{
      TIMEncoderRotate -= TIMEncoderEnterTimes;//���ٱ���������ֵ
	  if(TIMEncoderRotate >= -(TIMEncoderEnterTimes-1) && TIMEncoderRotate <= (TIMEncoderEnterTimes-1)) //С�����õĴ���������������
	  {
		TIMEncoderRotate = 0;
		return TIMEncoderUp;
	  }
	  return TIMEncoderTurnRight;
	}
	else if(TIMEncoderRotate < 0)//��������������
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