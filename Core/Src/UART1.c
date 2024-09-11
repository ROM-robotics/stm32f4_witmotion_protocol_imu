#include <stdio.h>
/*
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_rcc.h"
#include "misc.h"*/
#include "stm32f4xx_hal.h"
#include "main.h"
#include "stm32f4xx_hal_uart.h"

#include "UART1.h"
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

void Usart1Init(unsigned int uiBaud)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	UART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	  
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
	
	USART_InitStructure.BaudRate = uiBaud;
	USART_InitStructure.WordLength = UART_WORDLENGTH_8B;
	USART_InitStructure.StopBits = UART_PARITY_NONE;
	USART_InitStructure.Parity = UART_PARITY_NONE;
	USART_InitStructure.HwFlowCtl = UART_HWCONTROL_NONE;
	USART_InitStructure.Mode = UART_MODE_TX_RX;
	//USART_Init(USART1, &USART_InitStructure); 
	//USART_ITConfig(USART1, USART_IT_TXE, DISABLE); 
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//USART_ClearFlag(USART1,USART_FLAG_TC);
	//USART_Cmd(USART1, ENABLE);	
	 huart1.Instance = USART_InitStructure;
	if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

int fputc(int ch, FILE *file)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, ch);
	return ch;
}

void CopeCmdData(unsigned char ucData);
void USART1_IRQHandler(void)
{
	unsigned char ucTemp;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		ucTemp = USART_ReceiveData(USART1);
		CopeCmdData(ucTemp);
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
	USART_ClearITPendingBit(USART2,USART_IT_ORE);
}

