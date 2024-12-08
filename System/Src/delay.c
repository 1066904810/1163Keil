#include "delay.h"

static u8  fac_us=0;							//us延时倍乘数			   
static u16 fac_ms=0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数

void delay_init()
{
	SysTick->CTRL &= ~(1<<2) ;   //配置SysTick使用外部时钟源，是AHB总线时钟的1/8  有 72MHz/8 = 9MHz
	fac_us= 9;                   //SysTick计算一个数需要 1/9MHz 秒 ， 计算9个数则需要 9* 1/9MHz = 1us  ，所以延时函数delay_us传入的数值是“需要多少个1us”,delay_ms同理
	fac_ms=(u16)fac_us*1000;     //1ms = 1000us
}

/**************************************************************************
Function: Delay function（us）
Input   : nus：The number of us to delay
Output  : none
函数功能：延时函数（us）
入口参数：nus：要延时的us数	
返回  值：无
**************************************************************************/			    								   
#define CPU_FREQUENCY_MHZ    72		// STM32时钟主频
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
Function: Delay function（ms）
Input   : mus：The number of ms to delay
Output  : none
函数功能：延时函数（us）
入口参数：mus：要延时的ms数	
返回  值：无
**************************************************************************/
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864
void delay_ms(u16 nms)
{	 		  	  
	 u16 i=0;  
   while(nms--)
   {
      i=12000;  //自己定义
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

