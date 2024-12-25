#include "enc.h"

void Bsp_EncInit(void)
{
}

uint16_t Bsp_GetEncoder(TIM_HandleTypeDef* htimx)
{
	return __HAL_TIM_GetCounter(htimx);
}

