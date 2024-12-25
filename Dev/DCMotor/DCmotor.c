#include "DCMotor.h"

/*
	直流有刷电机控制函数：
	占空比选择0~1000
*/
void DControl(DCMotorClass * motor,float target)
{
	target/=1000;
	if(target<0)
			{
				target=-target;
				DevGPIO_WritePin(motor->GPIOx,motor->GPIO_PIN_INT1x,GPIO_PIN_RESET);
				DevGPIO_WritePin(motor->GPIOx,motor->GPIO_PIN_INT2x,  GPIO_PIN_SET);
			}
			else       
			{
				DevGPIO_WritePin(motor->GPIOx,motor->GPIO_PIN_INT1x,  GPIO_PIN_SET);
				DevGPIO_WritePin(motor->GPIOx,motor->GPIO_PIN_INT2x,GPIO_PIN_RESET);
			}
	Bsp_PWM_SetCompare(motor->BSP_PWM_SERVO_x,target);

}

void DCMotor_Start(DCMotorClass * motor)
{
	
	Bsp_PWM_Start(motor->BSP_PWM_SERVO_x);
	
}
void DCMotor_Stop(DCMotorClass * motor)
{

	Bsp_PWM_Stop(motor->BSP_PWM_SERVO_x);

	
}
uint16_t GetEncoder(DCMotorClass * motor)
{
	
	return Bsp_GetEncoder(&motor->htimx);

} 

