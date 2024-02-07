/**
 * @file	bsp_debug_uart.c
 * @brief	USART1 驱动配置
 * @author	Clement
 * @date	2023.11.25 
*/


#include "stm32f4xx.h"
#include "bsp_debug_uart.h"

/**
 * @brief	USART1 NVIC配置
 * @param	none
 * @return	none
*/
void NVIC_Configuration(void)
{
	/* NVIC初始化结构体 */
	NVIC_InitTypeDef NVIC_USART1_InitStruc;

	/* 参数配置 */
	NVIC_USART1_InitStruc.NVIC_IRQChannel = DEBUG_USART_IRQ;
	NVIC_USART1_InitStruc.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_USART1_InitStruc.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级
	NVIC_USART1_InitStruc.NVIC_IRQChannelSubPriority = 1; // 子优先级
	NVIC_Init(&NVIC_USART1_InitStruc);
}


/**
 * @brief	USART1 初始化
 * @param	none
 * @return	none
*/
void Debug_Uart_Config(void)
{
	/* 初始化结构体 */
	GPIO_InitTypeDef GPIO_USART1_InitStruct;
	USART_InitTypeDef USART1_InitStruct;

	/* 使能时钟 */
	RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);

	/* 引脚复用 */
	GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_SOURCE, DEBUG_USART_RX_AF);
	GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_SOURCE, DEBUG_USART_TX_AF);


	/* GPIO基本参数配置 */
	GPIO_USART1_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_USART1_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_USART1_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	/* Rx引脚配置 */
	GPIO_USART1_InitStruct.GPIO_Pin = DEBUG_USART_RX_PIN;
	GPIO_USART1_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_USART1_InitStruct);

	/* Tx引脚配置 */
	GPIO_USART1_InitStruct.GPIO_Pin = DEBUG_USART_TX_PIN;
	GPIO_USART1_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_USART1_InitStruct);

	/* USART1C参数配置*/
	USART1_InitStruct.USART_BaudRate = DEBUG_USART_BAUDRATE; // 波特率 115200
	USART1_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // 发送使能 接收使能
	USART1_InitStruct.USART_Parity = USART_Parity_No; // 无奇偶校验
	USART1_InitStruct.USART_StopBits = USART_StopBits_1; // 1位停止位
	USART1_InitStruct.USART_WordLength = USART_WordLength_8b; // 字长8bit
	USART1_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 不使用硬件流
	USART_Init(USART1, &USART1_InitStruct);

	/* NVIC初始化 */
	NVIC_Configuration();

	/* 使能串口接收中断 */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	/* 使能USART1 */ 
	USART_Cmd(DEBUG_USART, ENABLE);

}

/**
 * @brief	发送单字节数据
 * @param	pUSARTx -- 指定USART
 * 			ch -- 待发送字符
 * @return	None
*/
void Debug_SendByte(USART_TypeDef * pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx, ch);

	/* 等待发送数据寄存器为空 */
	// while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}


/**
 * @brief	发送字符串
 * @param	pUSARTx -- 指定USART
 * 			str -- 待发送字符串
 * @return	None
*/
void Debug_SendString(USART_TypeDef * pUSARTx, char * str)
{
	unsigned int k = 0; // 指针递增

	/* 循环调用Debug_SendingByte函数发送单个字符，直至遇到空字符 */
	do {
		Debug_SendByte(DEBUG_USART, *(str + k));
		k++;
	} while (*(str + k) != '\0');

	/* 等待发送完成 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) != SET);
}








///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USART, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USART);
}
