#include "Taskmanage.h"

// void Task(void *p)
// {   
//     while(1)
//     {

//     }
// }
/*******************************************************************************
* Function Name  : vTaskCreateFunction(void)
* Description    : ϵͳ�������񴴽�����
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void vTaskCreateFunction(void)
{   
     xTaskCreate( vSystemHardwareWorkTask, "SystemHardwareWorkTask",  310, 0, 1,0);//ϵͳӲ���������� ���ȼ�1
    //  xTaskCreate( Task, "Task",  310, 0, 2,0);//����
    //xTaskCreate( vFrameDataHandlerTask,   "vFrameDataHandlerTask",   240, 0, 2,0);//����֡���ݴ������� ���ȼ�2
}


/*******************************************************************************
* Function Name  : vSystemHardwareWorkTask(void)
* Description    : ϵͳӲ��������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void vSystemHardwareWorkTask(void *p)
{   
    while(1)
    {
       vTIMEncoderCheckOperation(); //����Ӧ��
//        vLedStateDisplay();      //LEDӦ��
//        vUsart1Interactive();// ����1���ʹ�����
//        vUsart2Interactive();// ����2���ͺͽ��ܴ�����
        UI_Test();
        vTaskDelay(10);
    }
}
