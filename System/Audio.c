#include "Audio.h"
BLDCMotorClass AdjMoto,BottoMoto;
Mode mode_select,mode_last;
KeyMode key;
uint16_t ADC_Value[4];

void SysInit(void)
{
	HAL_TIM_PWM_Init(&htim1);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);	
//	HAL_ADCEx_Calibration_Start(&hadc1);

}
void ParamInit(void)
{	
	AdjMoto.Motor_DIR=BSP_GPIO_B12;
	AdjMoto.Motor_EN=BSP_GPIO_B13;
	AdjMoto.BSP_PWM_SERVO_x = BSP_PWM_SERVO_A;
	BLDCMotor_Start(&AdjMoto); //������ų�ʼ��������PWM���
	
	BLDControl(&AdjMoto,0);
}
void DevInit(void)
{
	Bsp_PWM_Start(BSP_PWM_SERVO_C);
	Bsp_PWM_Start(BSP_PWM_SERVO_D);
	Bsp_UsartInit(&huart2);

}
float set=800;
extern uint8_t angle;
void Control(void)
{
	switch(mode_select)
	{
		case 	AUDIO_RESET://��λ״̬
			set=0;
		break;
		case AUDIO_PAUSE://��̬ͣ
			set=0; 
		break;
		case 	AUDIO_UP:
			set=800;
			if(!Bsp_GPIO_ReadPin(BSP_GPIO_B8))
			{
				mode_last=mode_select;
				mode_select=AUDIO_RESET;
			}
		break;
		case 	AUDIO_DOWN:
			set=-800;
			if(!Bsp_GPIO_ReadPin(BSP_GPIO_B9))
			{
				mode_last=mode_select;
				mode_select=AUDIO_RESET;
			}
		break;

	}
	BLDControl(&AdjMoto,set);
}

void GetData(void)
{
	Key_Process();
}
void Key_Process(void)
{
	switch(key)
	{
		case Key_Detect:
			if(!Bsp_GPIO_ReadPin(BSP_GPIO_A12))//��̧����ͣ
			{
				if(mode_select!=AUDIO_PAUSE)//��������ͣ
				{
					mode_last=mode_select;//�����ϴ�����״̬
					mode_select=AUDIO_PAUSE;//��ͣ
					break;
				}else{//������̬ͣ
					mode_select=mode_last;//ȡ���ϴ�����״̬
					break;
				}
			}
			if(!Bsp_GPIO_ReadPin(BSP_GPIO_A15))//��̧����
			{
				if(mode_select==AUDIO_RESET)//������λ̬
				{
					if(mode_last==AUDIO_DOWN)//�ж���һ�η���+ �����
					{
						mode_last=AUDIO_DOWN; 
						mode_select=AUDIO_UP;
						break;
					}
					if(mode_last==AUDIO_UP)
					{
						mode_last=AUDIO_UP;
						mode_select=AUDIO_DOWN;
						break;
					}
				}else{
					if(mode_select==AUDIO_DOWN)
					{
						mode_last=AUDIO_DOWN;
						mode_select=AUDIO_UP;
						break;
					}
					if(mode_select==AUDIO_UP)
					{
						mode_last=AUDIO_UP;
						mode_select=AUDIO_DOWN;
						break;
					}
				}
				key=Key_Pressed;
			}	
		break;
		case Key_Pressed:
			if(Bsp_GPIO_ReadPin(BSP_GPIO_A12)&&Bsp_GPIO_ReadPin(BSP_GPIO_A15))
				key=Key_Detect;
		break;
	}
}
