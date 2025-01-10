#ifndef __DESKBOARD_H
#define __DESKBOARD_H
#include "main.h"
#include "mpu6050.h"
#include "delay.h"
#include "pwm.h"
#include "DCmotor.h"
#include "enc.h"
#include "pid.h"
#include "gpio.h"

typedef enum{

	BOARD_RETRACT,
	BOARD_RESET,
	BOARD_CONTROL,
	BOARD_HORIZON,
	BOARD_PARALLEL
}Mode;

typedef struct{
	float Roll;
	float Pitch;
	float Yaw;
}EulrData;

extern ADC_HandleTypeDef hadc1;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

void SysInit(void);
void DevInit(void);
void ParamInit(void);
void Control(void);
void GetData(void);


#endif
