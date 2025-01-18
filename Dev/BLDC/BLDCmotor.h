#ifndef __BLDCMOTOR_H
#define __BLDCMOTOR_H
#include "main.h"
#include "enc.h"
#include "pwm.h"
#include "gpio.h"

#define DevGetSpeed GetEncoder

typedef   GPIO_PinState      DevGPIOState;
typedef		TIM_HandleTypeDef  DevEncx;  


typedef struct
{
		bsp_gpio_t Motor_DIR;
		bsp_gpio_t Motor_EN;
		
		DevEncx htimx;
		bsp_pwm_channel_t BSP_PWM_SERVO_x;
	
}BLDCMotorClass;

void 		 BLDControl				(BLDCMotorClass * motor, float);
void 		 BLDCMotor_Start	(BLDCMotorClass * motor);
void 		 BLDCMotor_Stop		(BLDCMotorClass * motor);
//uint16_t GetEncoder			(BLDCMotorClass * motor);


#endif
