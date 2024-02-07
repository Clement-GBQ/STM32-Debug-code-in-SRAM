/**
 * @file	bsp_debug_uart.c
 * @brief	USART1 ��������
 * @author	Clement
 * @date	2023.11.25 
*/


#include "stm32f4xx.h"
#include "bsp_debug_uart.h"

/**
 * @brief	USART1 NVIC����
 * @param	none
 * @return	none
*/
void NVIC_Configuration(void)
{
	/* NVIC��ʼ���ṹ�� */
	NVIC_InitTypeDef NVIC_USART1_InitStruc;

	/* �������� */
	NVIC_USART1_InitStruc.NVIC_IRQChannel = DEBUG_USART_IRQ;
	NVIC_USART1_InitStruc.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_USART1_InitStruc.NVIC_IRQChannelPreemptionPriority = 1; // ��ռ���ȼ�
	NVIC_USART1_InitStruc.NVIC_IRQChannelSubPriority = 1; // �����ȼ�
	NVIC_Init(&NVIC_USART1_InitStruc);
}


/**
 * @brief	USART1 ��ʼ��
 * @param	none
 * @return	none
*/
void Debug_Uart_Config(void)
{
	/* ��ʼ���ṹ�� */
	GPIO_InitTypeDef GPIO_USART1_InitStruct;
	USART_InitTypeDef USART1_InitStruct;

	/* ʹ��ʱ�� */
	RCC_AHB1PeriphClockCmd(DEBUG_USART_RX_GPIO_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(DEBUG_USART_CLK, ENABLE);

	/* ���Ÿ��� */
	GPIO_PinAFConfig(DEBUG_USART_RX_GPIO_PORT, DEBUG_USART_RX_SOURCE, DEBUG_USART_RX_AF);
	GPIO_PinAFConfig(DEBUG_USART_TX_GPIO_PORT, DEBUG_USART_TX_SOURCE, DEBUG_USART_TX_AF);


	/* GPIO������������ */
	GPIO_USART1_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_USART1_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_USART1_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	/* Rx�������� */
	GPIO_USART1_InitStruct.GPIO_Pin = DEBUG_USART_RX_PIN;
	GPIO_USART1_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_USART1_InitStruct);

	/* Tx�������� */
	GPIO_USART1_InitStruct.GPIO_Pin = DEBUG_USART_TX_PIN;
	GPIO_USART1_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_USART1_InitStruct);

	/* USART1C��������*/
	USART1_InitStruct.USART_BaudRate = DEBUG_USART_BAUDRATE; // ������ 115200
	USART1_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // ����ʹ�� ����ʹ��
	USART1_InitStruct.USART_Parity = USART_Parity_No; // ����żУ��
	USART1_InitStruct.USART_StopBits = USART_StopBits_1; // 1λֹͣλ
	USART1_InitStruct.USART_WordLength = USART_WordLength_8b; // �ֳ�8bit
	USART1_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // ��ʹ��Ӳ����
	USART_Init(USART1, &USART1_InitStruct);

	/* NVIC��ʼ�� */
	NVIC_Configuration();

	/* ʹ�ܴ��ڽ����ж� */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	/* ʹ��USART1 */ 
	USART_Cmd(DEBUG_USART, ENABLE);

}

/**
 * @brief	���͵��ֽ�����
 * @param	pUSARTx -- ָ��USART
 * 			ch -- �������ַ�
 * @return	None
*/
void Debug_SendByte(USART_TypeDef * pUSARTx, uint8_t ch)
{
	USART_SendData(pUSARTx, ch);

	/* �ȴ��������ݼĴ���Ϊ�� */
	// while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}


/**
 * @brief	�����ַ���
 * @param	pUSARTx -- ָ��USART
 * 			str -- �������ַ���
 * @return	None
*/
void Debug_SendString(USART_TypeDef * pUSARTx, char * str)
{
	unsigned int k = 0; // ָ�����

	/* ѭ������Debug_SendingByte�������͵����ַ���ֱ���������ַ� */
	do {
		Debug_SendByte(DEBUG_USART, *(str + k));
		k++;
	} while (*(str + k) != '\0');

	/* �ȴ�������� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) != SET);
}








///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USART, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USART, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USART);
}
