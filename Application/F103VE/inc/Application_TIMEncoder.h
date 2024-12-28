#ifndef __APP_TIMENCODER_H
#define __APP_TIMENCODER_H

#include "stm32f10x.h"                  // Device header
#include "TIMEncoder.h"
#include "SystemTime.h"
#include "stdlib.h"

#define  KEY_1_PIN                    GPIO_ReadInputDataBit(TIMEncoder_GPIO_PORT_Dwon,TIMEncoder_GPIO_PIN_Dwon)
#define  TIMEncoderEnterTimes          2
typedef enum
{
    TIMEncoderUp = 0,
    TIMEncoderSingleDown,
    TIMEncoderDoubleDown,
    TIMEncoderTurnRight,
    TIMEncoderTurnLeft,
}eTIMEncoderState;

void vTIMEncoderCheckOperation(void);
eTIMEncoderState eTIMEncoder1State(void);
eTIMEncoderState eTIMEncoderTurnState(void);

eTIMEncoderState eTIMEncoderExternState(void);





#endif