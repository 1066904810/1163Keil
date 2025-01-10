#ifndef __USART_SCREEN
#define __USART_SCREEN

#include "usart.h"
#include "main.h"
extern uint8_t rxbuf[];

typedef enum{

	MODE_1,
	MODE_2,
	MODE_START,
	MODE_STOP,
	MODE_RESERVE,
}screen_mode_t;

screen_mode_t Screen_ModeProcess(void);
//void Screen_DataProcess(void);


#endif
