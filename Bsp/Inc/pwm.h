#ifndef __PWM_H
#define __PWM_H

#include "main.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

typedef struct {
  TIM_HandleTypeDef *tim;
  uint16_t channel;
} bsp_pwm_config_t;

typedef enum {
  BSP_PWM_SERVO_A,
  BSP_PWM_SERVO_B,
  BSP_PWM_SERVO_C,
  BSP_PWM_SERVO_D,
	
	BSP_PWM_NUMBER,
} bsp_pwm_channel_t;

static bsp_pwm_config_t bsp_pwm_map[BSP_PWM_NUMBER] = {
    [BSP_PWM_SERVO_A] = {&htim1, TIM_CHANNEL_1},
    [BSP_PWM_SERVO_B] = {&htim1, TIM_CHANNEL_2},
    [BSP_PWM_SERVO_C] = {&htim1, TIM_CHANNEL_3},
    [BSP_PWM_SERVO_D] = {&htim1, TIM_CHANNEL_4},
		
};

void Bsp_PWM_Start(bsp_pwm_channel_t ch);
void Bsp_PWM_Stop(bsp_pwm_channel_t ch);
void Bsp_PWM_SetCompare(bsp_pwm_channel_t ch, float duty_cycle);

#endif
