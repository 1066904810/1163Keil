#ifndef __AUDIO_H
#define __AUDIO_H
#include "main.h"
#include "sys.h"
#include "data.h"

#include "delay.h"
#include "pwm.h"
#include "enc.h"
#include "pid.h"
#include "gpio.h"
#include "usart.h"

#include "mpu6050.h"
#include "DCmotor.h"
#include "BLDCMotor.h"
#include "usart_screen.h"

typedef enum{
	AUDIO_UP,
	AUDIO_DOWN,
	AUDIO_RESET,
	AUDIO_PAUSE,
}Mode;

typedef enum{
	Key_Detect,
	Key_Pressed,

}KeyMode;

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
void Key_Process(void);


#endif
