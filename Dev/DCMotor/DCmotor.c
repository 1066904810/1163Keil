#include "DCMotor.h"

/*
	直流有刷电机控制函数：
	占空比选择-1000~1000
*/
void DControl(DCMotorClass * motor,float target)
{
	target/=1000;
	if(target<0)
			{
				target=-target;
				Bsp_GPIO_WritePin(motor->Motor_INT1,GPIO_PIN_RESET);
				Bsp_GPIO_WritePin(motor->Motor_INT2,  GPIO_PIN_SET);
			}
			else       
			{
				Bsp_GPIO_WritePin(motor->Motor_INT1,  GPIO_PIN_SET);
				Bsp_GPIO_WritePin(motor->Motor_INT2,GPIO_PIN_RESET);
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

