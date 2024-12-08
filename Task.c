#include "Task.h"

uint8_t Tsk_1ms=0;
uint8_t Tsk_10ms=0;
uint8_t Tsk_50ms=0;
uint8_t Tsk_100ms=0;
uint8_t Tsk_1000ms=0;

uint16_t enc1,enc2;

void SysInit(void)
{
	HAL_TIM_PWM_Init(&htim1);
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
	
	DCMotor_Start(MOTOR_A);
	Bsp_PWM_Start(BSP_PWM_SERVO_C);
	Bsp_PWM_Start(BSP_PWM_SERVO_D);
	
	MPU6050_initialize();			//MPU6050初始化
  DMP_Init();		//dmp初始化

}
	

void TaskSchedule(void)
{
	if(Tsk_1ms)
		Task_1ms();
	if(Tsk_10ms)
		Task_10ms();
	if(Tsk_50ms)
		Task_50ms();
	if(Tsk_100ms)
		Task_100ms();
	if(Tsk_1000ms)
		Task_1000ms();
}

void Task_1ms(void)
{
	enc1=GetEncoder(MOTOR_A);
	enc2=GetEncoder(MOTOR_B);

	Read_DMP();
	
	Tsk_1ms=0;
}
void Task_10ms(void)
{
	DControl(MOTOR_A,-800);
	

	Tsk_10ms=0;
}
void Task_50ms(void)
{

	Tsk_50ms=0;
}
void Task_100ms(void)
{

	Tsk_100ms=0;
}
void Task_1000ms(void)
{
	HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
	Tsk_1000ms=0;
}
