#ifndef __USART_H
#define __USART_H

#include "main.h"
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

void Bsp_UsartInit(UART_HandleTypeDef *huartx);


#endif
