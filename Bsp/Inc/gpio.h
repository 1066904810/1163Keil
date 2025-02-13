#ifndef __GPIO_H
#define __GPIO_H

#include "main.h"

typedef struct {
  GPIO_TypeDef *GPIOx;
  uint16_t BSP_GPIO_Pin;
} bsp_gpio_config_t;
typedef GPIO_PinState bsp_gpio_state;
typedef enum {
	BSP_GPIO_A12,
	BSP_GPIO_A15,
	
	BSP_GPIO_B6,//占用一个编码器
  BSP_GPIO_B8,
  BSP_GPIO_B9,
  BSP_GPIO_B12,
  BSP_GPIO_B13,
	BSP_GPIO_B14,
  BSP_GPIO_B15,
			
	BSP_GPIO_NUMBER,
} bsp_gpio_t;

static bsp_gpio_config_t bsp_gpio_map[BSP_GPIO_NUMBER] = {
		[BSP_GPIO_A12] = 	{GPIOA, GPIO_PIN_12},
    [BSP_GPIO_A15] = 	{GPIOA, GPIO_PIN_15},	
		[BSP_GPIO_B6]  = 	{GPIOB, GPIO_PIN_6},
    [BSP_GPIO_B8]  = 	{GPIOB, GPIO_PIN_8},
    [BSP_GPIO_B9]	 = 	{GPIOB, GPIO_PIN_9},
    [BSP_GPIO_B12] = 	{GPIOB, GPIO_PIN_12},
    [BSP_GPIO_B13] = 	{GPIOB, GPIO_PIN_13},
		[BSP_GPIO_B14] = 	{GPIOB, GPIO_PIN_14},
		[BSP_GPIO_B15] = 	{GPIOB, GPIO_PIN_15},
};

void	Bsp_GPIO_WritePin(bsp_gpio_t gpio,bsp_gpio_state state);
bsp_gpio_state Bsp_GPIO_ReadPin(bsp_gpio_t gpio);

#endif
