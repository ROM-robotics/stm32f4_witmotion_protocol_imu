#ifndef __DELAY_H
#define __DELAY_H 			   
#include "stm32f4xx.h"
//#include "stm32f4xx_hal.h"

void SysTick_Init(void);
void delay_ms(uint16_t ms);

#endif

//------------------End of File----------------------------
