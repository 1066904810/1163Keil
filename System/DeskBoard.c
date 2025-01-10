#include "DeskBoard.h"
#include "usart.h"
#include "usart_screen.h"
DCMotorClass LinearMotor;
EulrData eulr;
PIDClass pid;
Mode mode_select;
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
	Bsp_UsartInit(&huart2);
	 
	MPU6050_initialize();			//MPU6050初始化
  DMP_Init();		//dmp初始化

}

void ParamInit(void)
{
	LinearMotor.Motor_INT1=BSP_GPIO_B12;
	LinearMotor.Motor_INT2=BSP_GPIO_B13;
	LinearMotor.BSP_PWM_SERVO_x = BSP_PWM_SERVO_A;
	DCMotor_Start(&LinearMotor); //电机引脚初始化，开启PWM输出
	
	pid.Config.Kp=50;
	pid.Config.Ki=0.0;
	pid.Config.Kd=0.0;
	pid.Config.Improve=PID_IMPROVE_NONE;
	pid.Config.MaxOut=1000;
}
extern uint8_t angle;
void Control(void)
{
	float set=0;
	
	switch(mode_select)
	{
		case 	BOARD_RETRACT:
			set=800;
			if(!Bsp_GPIO_ReadPin(BSP_GPIO_B8))
				mode_select=BOARD_RESET;
			break;
		case 	BOARD_RESET:
			if(	Screen_ModeProcess()==MODE_START)
				mode_select=BOARD_CONTROL;
			break;
		case 	BOARD_CONTROL:
			if(	Screen_ModeProcess()==MODE_1)
				mode_select=BOARD_HORIZON;
			if(	Screen_ModeProcess()==MODE_2)
				mode_select=BOARD_PARALLEL;
			break;
		case 	BOARD_HORIZON:
			set=PIDCalculate(&pid,eulr.Roll,40);
			if(	Screen_ModeProcess()==MODE_2)
				mode_select=BOARD_PARALLEL;
			if(	Screen_ModeProcess()==MODE_STOP)
				mode_select=BOARD_RETRACT;
			break;
		case 	BOARD_PARALLEL:
			if(	Screen_ModeProcess()==MODE_1)
				mode_select=BOARD_HORIZON;
			if(	Screen_ModeProcess()==MODE_STOP)
				mode_select=BOARD_RETRACT;
			break;
	
	}
	DControl(&LinearMotor,set);

}
int i=0;
void GetData(void)
{
	Read_DMP();
	eulr.Roll=Roll;

}
