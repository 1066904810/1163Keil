#include "DeskBoard.h"

typedef struct{
	float Roll;
	float Pitch;
	float Yaw;
}EulrData;

DCMotorClass LinearMotor;
EulrData eulr;
PIDClass pid;
void SysInit(void)
{
	HAL_TIM_PWM_Init(&htim1);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
}

void DevInit(void)
{	
	Bsp_PWM_Start(BSP_PWM_SERVO_C);
	Bsp_PWM_Start(BSP_PWM_SERVO_D);
	 
	MPU6050_initialize();			//MPU6050初始化
  DMP_Init();		//dmp初始化

}

void ParamInit(void)
{
	LinearMotor.GPIOx = GPIOB;
	LinearMotor.GPIO_PIN_INT1x = GPIO_PIN_12;
	LinearMotor.GPIO_PIN_INT2x = GPIO_PIN_13;
	LinearMotor.BSP_PWM_SERVO_x = BSP_PWM_SERVO_A;
	DCMotor_Start(&LinearMotor); //电机引脚初始化，开启PWM输出
	
	pid.Config.Kp=50;
	pid.Config.Ki=0.0;
	pid.Config.Kd=0.0;
	pid.Config.Improve=PID_IMPROVE_NONE;
	pid.Config.MaxOut=1000;
}

void Control(void)
{

	float set=PIDCalculate(&pid,eulr.Roll,0);
	DControl(&LinearMotor,set);
}

void GetData(void)
{

	Read_DMP();
	eulr.Roll=Roll;

}
