#include "delay.h"
//#include "misc.h"

//static uint16_t  fac_us=0;
//static uint16_t fac_ms=0;

static volatile uint32_t sv_uiDelay = 0;
/*void SysTick_Init(void)
{	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	fac_us=SystemCoreClock/8000000;
	fac_ms=(uint16_t)fac_us*1000;
}*/
void SysTick_Init(void) 
{
    // Configure SysTick to interrupt every 1ms
    SysTick->LOAD = (SystemCoreClock / 1000) - 1;  // Set reload register for 1ms ticks
    SysTick->VAL = 0;                              // Reset current SysTick counter value
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |   // Use processor clock
                    SysTick_CTRL_TICKINT_Msk |     // Enable SysTick interrupt
                    SysTick_CTRL_ENABLE_Msk;       // Enable SysTick
}
//void delay_ms(uint16_t nms)
/*{	 		  	  
	uint32_t temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
	SysTick->VAL =0X00;	    
} */

