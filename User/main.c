#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "HardwareManage.h"
#include "TaskManage.h"

 int  main(void)
{

	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4	 

    vSystemHardwareDriverInit();//Ӳ����ʼ��
	OLED_UI_Init();
	vTaskCreateFunction();//��������
    vTaskStartScheduler();//�����������   

}
