/***********************************************
��˾����Ȥ�Ƽ�����ݸ�����޹�˾
Ʒ�ƣ�WHEELTEC
������wheeltec.net
�Ա����̣�shop114407458.taobao.com 
����ͨ: https://minibalance.aliexpress.com/store/4455017
�汾��5.7
�޸�ʱ�䣺2021-04-29

Brand: WHEELTEC
Website: wheeltec.net
Taobao shop: shop114407458.taobao.com 
Aliexpress: https://minibalance.aliexpress.com/store/4455017
Version:5.7
Update��2021-04-29

All rights reserved
***********************************************/

#include "delay.h"

static u8  fac_us=0;							//us��ʱ������			   
static u16 fac_ms=0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

void delay_init()
{
	SysTick->CTRL &= ~(1<<2) ;   //����SysTickʹ���ⲿʱ��Դ����AHB����ʱ�ӵ�1/8  �� 72MHz/8 = 9MHz
	fac_us= 9;                   //SysTick����һ������Ҫ 1/9MHz �� �� ����9��������Ҫ 9* 1/9MHz = 1us  ��������ʱ����delay_us�������ֵ�ǡ���Ҫ���ٸ�1us��,delay_msͬ��
	fac_ms=(u16)fac_us*1000;     //1ms = 1000us
}

/**************************************************************************
Function: Delay function��us��
Input   : nus��The number of us to delay
Output  : none
�������ܣ���ʱ������us��
��ڲ�����nus��Ҫ��ʱ��us��	
����  ֵ����
**************************************************************************/			    								   
#define CPU_FREQUENCY_MHZ    72		// STM32ʱ����Ƶ
void delay_us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}


/**************************************************************************
Function: Delay function��ms��
Input   : mus��The number of ms to delay
Output  : none
�������ܣ���ʱ������us��
��ڲ�����mus��Ҫ��ʱ��ms��	
����  ֵ����
**************************************************************************/
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;						//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;												//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));			//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;       								//��ռ�����	  	    
} 
