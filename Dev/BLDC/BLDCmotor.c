#include "BLDCMotor.h"

/*
	ֱ����ˢ������ƺ�����
	ռ�ձ�ѡ��-1000~1000
	������Ϊ���߼������0ʱ�ٶ����1000ʱͣת
*/
void BLDControl(BLDCMotorClass * motor,float target)
{
//	target=1000-target;
	target/=1000;
	if(target<0.05&&target>-0.05)
	{
		BLDCMotor_Stop(motor);//����ʱ��̫��ֱ�Ӻ���
		return;
	}
	BLDCMotor_Start(motor);
	if(target<0)
	{
		target=1+target;//-1~0
		Bsp_GPIO_WritePin(motor->Motor_DIR,GPIO_PIN_SET);
		motor->direction=CCW;
	}
	else
	{
		target=1-target;//0~1
		Bsp_GPIO_WritePin(motor->Motor_DIR,GPIO_PIN_RESET);
		motor->direction=CW;

	}
	Bsp_PWM_SetCompare(motor->BSP_PWM_SERVO_x,target);

}

void BLDCMotor_Start(BLDCMotorClass * motor)
{
	
	Bsp_GPIO_WritePin(motor->Motor_EN,GPIO_PIN_SET);
	Bsp_PWM_Start(motor->BSP_PWM_SERVO_x);
	motor->state=START;
	
}
void BLDCMotor_Stop(BLDCMotorClass * motor)
{

	Bsp_GPIO_WritePin(motor->Motor_EN,GPIO_PIN_RESET);
	Bsp_PWM_Stop(motor->BSP_PWM_SERVO_x);
	motor->state=STOP;
	
}
void BLDC_GetEncoder(BLDCMotorClass * motor)
{
	if(motor->state==STOP)
		return;
	if(!Bsp_GPIO_ReadPin(motor->Motor_Trig))
	{
		if(motor->direction==CW)
			motor->enc++;
		else
			motor->enc--;
	}
} 

void BLDC_TrigCtrl(BLDCMotorClass * motor, int16_t trig)
{
	float set;
	if(trig==motor->enc)
	{
		set=0;
		BLDControl(motor,set);
		return;
	}

	if(motor->enc-trig<0)
		set=100;
	else
		set=-100;
	BLDControl(motor,set);
}
