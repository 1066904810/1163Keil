#ifndef __DCMOTOR_H
#define __DCMOTOR_H
#include "main.h"
#include "pwm.h"

#define MOTOR_A_GPIOx             GPIOB
#define MOTOR_A_DIR_INT1    GPIO_PIN_12
#define MOTOR_A_DIR_INT2    GPIO_PIN_13
#define MOTOR_A_PWM     BSP_PWM_SERVO_A

#define MOTOR_B_GPIOx             GPIOB
#define MOTOR_B_DIR_INT1    GPIO_PIN_14
#define MOTOR_B_DIR_INT2    GPIO_PIN_15
#define MOTOR_B_PWM     BSP_PWM_SERVO_B

typedef enum {
	MOTOR_A,
	MOTOR_B,
}MotoSelect;

void DControl(MotoSelect motor, float target);
void DCMotor_Start(MotoSelect motor);
void DCMotor_Stop(MotoSelect motor);
uint16_t GetEncoder(MotoSelect motor);

#endif
