#include "Taskmanage.h"

// void Task(void *p)
// {   
//     while(1)
//     {

//     }
// }
/*******************************************************************************
* Function Name  : vTaskCreateFunction(void)
* Description    : 系统所有任务创建函数
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void vTaskCreateFunction(void)
{   
     xTaskCreate( vSystemHardwareWorkTask, "SystemHardwareWorkTask",  310, 0, 1,0);//系统硬件工作任务 优先级1
    //  xTaskCreate( Task, "Task",  310, 0, 2,0);//测试
    //xTaskCreate( vFrameDataHandlerTask,   "vFrameDataHandlerTask",   240, 0, 2,0);//串口帧数据处理任务 优先级2
}


/*******************************************************************************
* Function Name  : vSystemHardwareWorkTask(void)
* Description    : 系统硬件任务函数
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void vSystemHardwareWorkTask(void *p)
{   
    while(1)
    {
       vTIMEncoderCheckOperation(); //按键应用
//        vLedStateDisplay();      //LED应用
//        vUsart1Interactive();// 串口1发送处理函数
//        vUsart2Interactive();// 串口2发送和接受处理函数
        UI_Test();
        vTaskDelay(10);
    }
}
