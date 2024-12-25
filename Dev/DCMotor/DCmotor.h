#ifndef __DCMOTOR_H
#define __DCMOTOR_H
#include "main.h"
#include "enc.h"
#include "pwm.h"

#define DevGPIO_WritePin HAL_GPIO_WritePin
#define DevGetSpeed GetEncoder

typedef   GPIO_TypeDef       DevGPIOx;
typedef   uint16_t           DevGPIO_Pin;
typedef   GPIO_PinState      DevGPIOState;
typedef		TIM_HandleTypeDef  DevEncx;  


typedef struct
{
		
		DevGPIOx* GPIOx;
		DevGPIO_Pin GPIO_PIN_INT1x;
		DevGPIO_Pin GPIO_PIN_INT2x;
		
		DevEncx htimx;
		bsp_pwm_channel_t BSP_PWM_SERVO_x;
	
}DCMotorClass;

void 		 DControl				(DCMotorClass * motor, float);
void 		 DCMotor_Start	(DCMotorClass * motor);
void 		 DCMotor_Stop		(DCMotorClass * motor);
uint16_t GetEncoder			(DCMotorClass * motor);


#endif
