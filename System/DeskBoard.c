#include "DeskBoard.h"

DCMotorClass LinearMotor;
BLDCMotorClass AdjMoto,BottoMoto;

MPUClass MPU_Low, MPU_High;
EulrData eulr;
PIDClass pid;
Mode mode_select;

uint16_t ADC_Value[4];

void SysInit(void)
{
	HAL_TIM_PWM_Init(&htim1);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
	
	HAL_ADCEx_Calibration_Start(&hadc1);

}
void ParamInit(void)
{
//	LinearMotor.Motor_INT1=BSP_GPIO_B12;
//	LinearMotor.Motor_INT2=BSP_GPIO_B13;
//	LinearMotor.BSP_PWM_SERVO_x = BSP_PWM_SERVO_A;
//	DCMotor_Start(&LinearMotor); //电机引脚初始化，开启PWM输出
	MPU_Low.addr=0x68;
	MPU_High.addr=0x69;
	
	AdjMoto.Motor_DIR=BSP_GPIO_B12;
	AdjMoto.Motor_EN=BSP_GPIO_B13;
	AdjMoto.BSP_PWM_SERVO_x = BSP_PWM_SERVO_A;
	BLDCMotor_Start(&AdjMoto); //电机引脚初始化，开启PWM输出
	
	BottoMoto.Motor_DIR=BSP_GPIO_B14;
	BottoMoto.Motor_EN=BSP_GPIO_B15;
	BottoMoto.BSP_PWM_SERVO_x = BSP_PWM_SERVO_B;
	BLDCMotor_Start(&BottoMoto); //电机引脚初始化，开启PWM输出
	
	pid.Config.Kp=50;
	pid.Config.Ki=0.0;
	pid.Config.Kd=0.0;
	pid.Config.Improve=PID_IMPROVE_NONE;
	pid.Config.MaxOut=1000;
}
void DevInit(void)
{	
  DMP_Init(MPU_Low.addr);		//dmp初始化
	DMP_Init(MPU_High.addr);		//dmp初始化

	Bsp_PWM_Start(BSP_PWM_SERVO_C);
	Bsp_PWM_Start(BSP_PWM_SERVO_D);
	Bsp_UsartInit(&huart2);

}

void Control(void)
{
	float set=0;
	
	if(mode_select==BOARD_RESET)
		BLDCMotor_Stop(&AdjMoto);
	else
		BLDCMotor_Start(&AdjMoto);
	
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
			set=PIDCalculate(&pid,MPU_High.eulr.Roll,0);
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
//	DControl(&LinearMotor,set);
	BLDControl(&AdjMoto,set);

}
int i=0;
void GetData(void)
{
	Read_DMP(&MPU_Low);
	Read_DMP(&MPU_High);

//	MPU_High.eulr.Roll=Roll;
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADC_Value,sizeof(ADC_Value)/sizeof(ADC_Value[0]));

}

