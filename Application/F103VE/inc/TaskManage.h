#ifndef __TASKMANAGE_H
#define __TASKMANAGE_H

#include "Applocation_UI.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Application_TIMEncoder.h"


void vTaskCreateFunction(void);
void vSystemHardwareWorkTask(void *p);



#endif