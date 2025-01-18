#include "usart_screen.h"
uint8_t *screendata=rxbuf;
#define DEFAULT_ANGLE 45
screen_mode_t Screen_ModeProcess(void)
{
	
	if(rxbuf[0]==0x01&&rxbuf[1]==0x00)
	{
		if(rxbuf[2]==0x01)
			return MODE_1;
		if(rxbuf[2]==0x02)
			return MODE_2;
	}
	if(rxbuf[0]==0x01&&rxbuf[1]==0x01)
	{
		if(rxbuf[2]==0x00)
			return MODE_START;
		if(rxbuf[2]==0x01)
			return MODE_STOP;
	}
	return MODE_RESERVE;
}
uint8_t angle;
void Screen_DataProcess(void)
{

	if(rxbuf[0]==0x02&&rxbuf[1]==0x00)
		angle = rxbuf[2];

//	return DEFAULT_ANGLE;
}
