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
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
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
	 u16 i=0;  
   while(nms--)
   {
      i=12000;  //�Լ�����
      while(i--) ;    
   }

} 
void delay_1us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_2us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_3us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_4us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_5us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_6us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_7us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_8us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_9us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_0us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_11us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_12us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_13us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_14us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_15us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_16us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_17us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_18us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_19us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_20us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_21us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_22us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_23us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_24us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_25us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_26us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_27us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}
void delay_28us(__IO uint32_t delay)
{
    int last, curr, val;
    int temp;

    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = TIM2->CNT;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = TIM2->CNT;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = TIM2->CNT;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;  
    }
}

