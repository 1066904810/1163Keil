#ifndef __BLDCMOTOR_H
#define __BLDCMOTOR_H
#include "main.h"
#include "enc.h"
#include "pwm.h"
#include "gpio.h"
#include "data.h"

#define DevGetSpeed GetEncoder

typedef   GPIO_PinState      DevGPIOState;
typedef enum{
	STOP,
	START
}Motor_State;
typedef struct
{
		bsp_gpio_t Motor_DIR;
		bsp_gpio_t Motor_EN;
		bsp_gpio_t Motor_Trig;
		
		Dir direction;
		Motor_State state;
		int16_t enc;
		
		bsp_pwm_channel_t BSP_PWM_SERVO_x;
	
}BLDCMotorClass;

void 		 BLDControl				(BLDCMotorClass * motor, float);
void 		 BLDCMotor_Start	(BLDCMotorClass * motor);
void 		 BLDCMotor_Stop		(BLDCMotorClass * motor);
void 		 BLDC_GetEncoder	(BLDCMotorClass * motor);
void 		 BLDC_TrigCtrl		(BLDCMotorClass * motor, int16_t trig);


#endif
