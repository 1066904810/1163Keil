#include "DCmotor.h"

void DControl(MotoSelect motor, float target)
{
	target/=1000;
	switch(motor){
		case MOTOR_A:
			if(target<0)
			{
				target=-target;
				HAL_GPIO_WritePin(MOTOR_A_GPIOx,MOTOR_A_DIR_INT1,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MOTOR_A_GPIOx,MOTOR_A_DIR_INT2,GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(MOTOR_A_GPIOx,MOTOR_A_DIR_INT1,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MOTOR_A_GPIOx,MOTOR_A_DIR_INT2,GPIO_PIN_RESET);
			}
			Bsp_PWM_SetCompare(MOTOR_A_PWM,target);
			break;
		case MOTOR_B:
			if(target<0)
			{
				target=-target;
				HAL_GPIO_WritePin(MOTOR_B_GPIOx,MOTOR_B_DIR_INT1,GPIO_PIN_RESET);
				HAL_GPIO_WritePin(MOTOR_B_GPIOx,MOTOR_B_DIR_INT2,GPIO_PIN_SET);
			}
			else
			{
				HAL_GPIO_WritePin(MOTOR_B_GPIOx,MOTOR_B_DIR_INT1,GPIO_PIN_SET);
				HAL_GPIO_WritePin(MOTOR_B_GPIOx,MOTOR_B_DIR_INT2,GPIO_PIN_RESET);
			}
			Bsp_PWM_SetCompare(MOTOR_B_PWM,target);
			break;
		default:
			break;
	};

}
void DCMotor_Start(MotoSelect motor)
{
	switch(motor){
		case MOTOR_A:
			Bsp_PWM_Start(MOTOR_A_PWM);
			break;
		case MOTOR_B:
			Bsp_PWM_Start(MOTOR_B_PWM);
			break;
		default:
			break;
	};
}
void DCMotor_Stop(MotoSelect motor)
{
	switch(motor){
		case MOTOR_A:
			Bsp_PWM_Stop(MOTOR_A_PWM);
			break;
		case MOTOR_B:
			Bsp_PWM_Stop(MOTOR_B_PWM);
			break;
		default:
			break;
	}
}
uint16_t GetEncoder(MotoSelect motor)
{
	uint16_t enc;
	switch(motor){
		case MOTOR_A:
			enc = __HAL_TIM_GetCounter(&htim3);
			break;
		case MOTOR_B:
			enc = __HAL_TIM_GetCounter(&htim4);
			break;
		default:
			enc = 0;
			break;
	}
	return enc;

}

