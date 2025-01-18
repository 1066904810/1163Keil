#include "BLDCMotor.h"

/*
	直流无刷电机控制函数：
	占空比选择-1000~1000
	驱动板为反逻辑输出，0时速度最大，1000时停转
*/
void BLDControl(BLDCMotorClass * motor,float target)
{
//	target=1000-target;
	target/=1000;
	BLDCMotor_Start(motor);

	if(target<0.05&&target>-0.05)
	{
		BLDCMotor_Stop(motor);//低速时振动太大，直接忽略
		return;
	}

	if(target<0)
	{
		target=1+target;//-1~0
		Bsp_GPIO_WritePin(motor->Motor_DIR,GPIO_PIN_SET);
	}
	else       
	{
		target=1-target;//0~1
		Bsp_GPIO_WritePin(motor->Motor_DIR,GPIO_PIN_RESET);
	}
	Bsp_PWM_SetCompare(motor->BSP_PWM_SERVO_x,target);

}

void BLDCMotor_Start(BLDCMotorClass * motor)
{
	
	Bsp_GPIO_WritePin(motor->Motor_EN,GPIO_PIN_SET);
	Bsp_PWM_Start(motor->BSP_PWM_SERVO_x);

	
}
void BLDCMotor_Stop(BLDCMotorClass * motor)
{

	Bsp_GPIO_WritePin(motor->Motor_EN,GPIO_PIN_RESET);
	Bsp_PWM_Stop(motor->BSP_PWM_SERVO_x);


	
}
//uint16_t GetEncoder(DCMotorClass * motor)
//{
//	
//	return Bsp_GetEncoder(&motor->htimx);

//} 

