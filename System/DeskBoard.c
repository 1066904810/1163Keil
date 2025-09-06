#include "DeskBoard.h"

DCMotorClass LinearMotor;
BLDCMotorClass AdjMoto,BottoMoto;

MPUClass MPU_Low, MPU_High;
EulrData eulr;
PIDClass pid;
Mode mode_select,last_mode;
screen_mode_t ctrl_mode;
uint16_t ADC_Value[4];

void SysInit(void)
{
	HAL_TIM_PWM_Init(&htim1);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
//	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
	
	HAL_ADCEx_Calibration_Start(&hadc1);

}
void ParamInit(void)
{
//	LinearMotor.Motor_INT1=BSP_GPIO_B12;
//	LinearMotor.Motor_INT2=BSP_GPIO_B13;
//	LinearMotor.BSP_PWM_SERVO_x = BSP_PWM_SERVO_A;
//	DCMotor_Start(&LinearMotor); //电机引脚初始化，开启PWM输出
	MPU_Low.addr=0x68;
//	MPU_High.addr=0x69;
	
	AdjMoto.Motor_DIR=BSP_GPIO_B12;
	AdjMoto.Motor_EN=BSP_GPIO_B13;
	AdjMoto.BSP_PWM_SERVO_x = BSP_PWM_SERVO_A;
	BLDCMotor_Start(&AdjMoto); //电机引脚初始化，开启PWM输出
	
	
	BottoMoto.Motor_DIR=BSP_GPIO_B14;
	BottoMoto.Motor_EN=BSP_GPIO_B15;
	BottoMoto.Motor_Trig=BSP_GPIO_B6;
	BottoMoto.BSP_PWM_SERVO_x = BSP_PWM_SERVO_B;
	BLDCMotor_Start(&BottoMoto); //电机引脚初始化，开启PWM输出
	
	
	pid.Config.Kp=60;
	pid.Config.Ki=0.0;
	pid.Config.Kd=0.0;
	pid.Config.Improve=PID_IMPROVE_NONE;
	pid.Config.MaxOut=1000;
	
	BLDControl(&AdjMoto,0);
	BLDControl(&BottoMoto,0);
}
void DevInit(void)
{	
  DMP_Init(MPU_Low.addr);		//dmp初始化
//	DMP_Init(MPU_High.addr);		//dmp初始化
	
	Bsp_PWM_Start(BSP_PWM_SERVO_C);
	Bsp_PWM_Start(BSP_PWM_SERVO_D);
	Bsp_UsartInit(&huart2);

}
float set=0,paral_set=0,bset=0;
extern uint8_t angle,kp;
void Control(void)
{
	pid.Config.Kp=kp;
	if(mode_select==BOARD_RESET)
		set=0;
	set=PIDCalculate(&pid,MPU_Low.eulr.Roll,3);
	paral_set=PIDCalculate(&pid,MPU_Low.eulr.Roll-MPU_Low.eulr.Roll,0);//平行控制
	switch(mode_select)
	{
		case 	BOARD_RETRACT:
			set=800;
			if(ADC_Value[0]<2000)
			{
				last_mode=mode_select;
				mode_select=BOARD_PAUSE;
				return;
			}
			if(!Bsp_GPIO_ReadPin(BSP_GPIO_B8))
				mode_select=BOARD_RESET;
			break;
		case 	BOARD_RESET:
			set=0;
			if(	ctrl_mode==MODE_START)
				mode_select=BOARD_CONTROL;
			break;
		case 	BOARD_CONTROL:
			set=0;
			if(	ctrl_mode==MODE_1)
				mode_select=BOARD_HORIZON;
			if(	ctrl_mode==MODE_2)
				mode_select=BOARD_PARALLEL;
			break;
		case 	BOARD_HORIZON:
			if(ADC_Value[0]<2000)
			{
				last_mode=mode_select;
				mode_select=BOARD_PAUSE;
				return;
			}
			if(!Bsp_GPIO_ReadPin(BSP_GPIO_B9))
			{
				last_mode=mode_select;
				mode_select=BOARD_UPLIMIT;
			}
			if(	ctrl_mode==MODE_2)
				mode_select=BOARD_PARALLEL;
			if(	ctrl_mode==MODE_STOP)
				mode_select=BOARD_RETRACT;
			break;
		case 	BOARD_PARALLEL:
			set=paral_set;
			if(!Bsp_GPIO_ReadPin(BSP_GPIO_B9))
			{
				last_mode=mode_select;
				mode_select=BOARD_UPLIMIT;
			}
				
			if(	ctrl_mode==MODE_1)
				mode_select=BOARD_HORIZON;
			if(	ctrl_mode==MODE_STOP)
				mode_select=BOARD_RETRACT;
			break;
		case BOARD_UPLIMIT:
			if(set<0)
			{
				set=0;
				if(	ctrl_mode==MODE_STOP)
				{
					mode_select=BOARD_RETRACT;
					break;
				}
			}
			else
			{
				if(MPU_High.eulr.Roll<0)
					mode_select=last_mode;
			}
			break;
		case BOARD_PAUSE:
			set=0;
			if(ADC_Value[0]>=2000)
			{
				mode_select=last_mode;
			}
		default:
				set=0;
			break;
	
	}
//	DControl(&LinearMotor,set);
	BLDControl(&AdjMoto,-set);
//	delay_ms(1);
	if(angle>=70)
		bset=-100;
	if(angle<=30)
		bset=100;
	if(angle<70&&angle>30)
		bset=0;
		
	BLDControl(&BottoMoto,bset);

	printf("d: %f\n",MPU_High.eulr.Roll);


}

void GetData(void)
{
	Read_DMP(&MPU_Low);
//	Read_DMP(&MPU_High);
	BLDC_GetEncoder(&BottoMoto);
	Screen_DataProcess();
	ctrl_mode=Screen_ModeProcess();
	HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADC_Value,sizeof(ADC_Value)/sizeof(ADC_Value[0]));

}

