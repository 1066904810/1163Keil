#include "usart.h"

#define RX_MAXSIZE 5
uint8_t rxbuf[RX_MAXSIZE];
uint8_t test_string[]="ok!";
void Bsp_UsartInit(UART_HandleTypeDef *huart)
{
	HAL_UART_Receive_IT(huart,(uint8_t*)rxbuf,sizeof(rxbuf));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2)
  {
			HAL_UART_Receive_IT(&huart2, (uint8_t*)rxbuf,sizeof(rxbuf));			
				
  }

}
