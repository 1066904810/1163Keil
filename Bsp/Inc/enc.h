#ifndef __ENC_H
#define __ENC_H
#include "main.h"


void Bsp_EncInit(void);
uint16_t Bsp_GetEncoder(TIM_HandleTypeDef* htimx);


#endif
