#ifndef __TASH_H
#define __TASH_H

#include "main.h"
#include "mpu6050.h"
#include "delay.h"
#include "pwm.h"
#include "DCmotor.h"
extern ADC_HandleTypeDef hadc1;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;


void SysInit(void);
void TaskSchedule(void);

void Task_1ms		(void);
void Task_10ms	(void);
void Task_50ms	(void);
void Task_100ms	(void);
void Task_1000ms(void);

#endif
