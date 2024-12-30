#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "HardwareManage.h"
#include "TaskManage.h"

 int  main(void)
{

	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//设置系统中断优先级分组4	 

    vSystemHardwareDriverInit();//硬件初始化

	vTaskCreateFunction();//创建任务
    vTaskStartScheduler();//开启任务调度   

}
