#include "pwm.h"

void Bsp_PWM_Start(bsp_pwm_channel_t ch)
{
	  HAL_TIM_PWM_Start(bsp_pwm_map[ch].tim, bsp_pwm_map[ch].channel);
}
void Bsp_PWM_Stop(bsp_pwm_channel_t ch)
{
	  HAL_TIM_PWM_Stop(bsp_pwm_map[ch].tim, bsp_pwm_map[ch].channel);

}
void Bsp_PWM_SetCompare(bsp_pwm_channel_t ch, float duty_cycle)
{
	if (duty_cycle > 1.0f) {
		duty_cycle = 1.0f;
  }

  if (duty_cycle < 0.0f) {
    duty_cycle = 0.f;
  }

  /* ͨ��PWMͨ����Ӧ��ʱ������ֵ�͸���ռ�ձȣ�����PWM����ֵ */
  uint16_t pulse = (uint16_t)(duty_cycle * (float)__HAL_TIM_GET_AUTORELOAD(
                                               bsp_pwm_map[ch].tim));

  __HAL_TIM_SET_COMPARE(bsp_pwm_map[ch].tim, bsp_pwm_map[ch].channel, pulse);

}
