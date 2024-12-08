#include "Init.h"
#include "freertos.h"
#include "semphr.h"

uint16_t enc1,enc2;
SemaphoreHandle_t xMutex;


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
	
	xMutex = xSemaphoreCreateMutex();

}

void DataTask(void *argument)
{
  for(;;)
  {
		if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
			Read_DMP();
			enc1=GetEncoder(MOTOR_A);
			enc2=GetEncoder(MOTOR_B);
			
			delay_1us(1);
			delay_2us(1);
			delay_3us(1);
			delay_4us(1);
			delay_5 us(1);

			xSemaphoreGive(xMutex); // 释放互斥锁
		}
		osDelay(1);
  }
}

void ControlTask(void *argument)
{
  for(;;)
  {	
	  if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
//			DControl(MOTOR_A,-800);
			xSemaphoreGive(xMutex); // 释放互斥锁
		}
    osDelay(1000);
  }
}

