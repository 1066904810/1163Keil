#ifndef __DCMOTOR_H
#define __DCMOTOR_H
#include "main.h"
#include "enc.h"
#include "pwm.h"
#include "gpio.h"

#define DevGetSpeed GetEncoder

typedef   GPIO_PinState      DevGPIOState;
typedef		TIM_HandleTypeDef  DevEncx;  


typedef struct
{
		bsp_gpio_t Motor_INT1;
		bsp_gpio_t Motor_INT2;
		
		DevEncx htimx;
		bsp_pwm_channel_t BSP_PWM_SERVO_x;
	
}DCMotorClass;

void 		 DControl				(DCMotorClass * motor, float);
void 		 DCMotor_Start	(DCMotorClass * motor);
void 		 DCMotor_Stop		(DCMotorClass * motor);
uint16_t GetEncoder			(DCMotorClass * motor);


#endif
