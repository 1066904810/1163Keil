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
	BLDCMotor_Start(&AdjMoto); //µÁª˙“˝Ω≈≥ı ºªØ£¨ø™∆ÙPWM ‰≥ˆ
	
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
		case 	AUDIO_RESET://œﬁŒª◊¥Ã¨
			set=0;
		break;
		case AUDIO_PAUSE://‘›Õ£Ã¨
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
			if(!Bsp_GPIO_ReadPin(BSP_GPIO_A12))//»ÙÃß∆‘›Õ£
			{
				if(mode_select!=AUDIO_PAUSE)//»Ù≤ª «‘›Õ£
				{
					mode_last=mode_select;//±£¥Ê…œ¥Œ‘À––◊¥Ã¨
					mode_select=AUDIO_PAUSE;//‘›Õ£
					break;
				}else{//»Ù «‘›Õ£Ã¨
					mode_select=mode_last;//»°ªÿ…œ¥Œ‘À––◊¥Ã¨
					break;
				}
			}
			if(!Bsp_GPIO_ReadPin(BSP_GPIO_A15))//»ÙÃß∆∑¥œÚ
			{
				if(mode_select==AUDIO_RESET)//»Ù «œﬁŒªÃ¨
				{
					if(mode_last==AUDIO_DOWN)//≈–∂œ…œ“ª¥Œ∑ΩœÚµ+ ƒ’˝∑¥
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
