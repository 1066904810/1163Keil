#include "usart.h"
#include "stdio.h"
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
int fputc(int ch, FILE *f)
 
{
 
  HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xffff);
 
  return ch;
 
}