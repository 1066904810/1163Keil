#include "gpio.h"

void Bsp_GPIO_WritePin(bsp_gpio_t gpio,bsp_gpio_state state)
{
	HAL_GPIO_WritePin(bsp_gpio_map[gpio].GPIOx, bsp_gpio_map[gpio].BSP_GPIO_Pin, state);
}

bsp_gpio_state Bsp_GPIO_ReadPin(bsp_gpio_t gpio)
{
	return HAL_GPIO_ReadPin(bsp_gpio_map[gpio].GPIOx, bsp_gpio_map[gpio].BSP_GPIO_Pin);
}
