#ifndef __DEBUG_USART_H
#define	__DEBUG_USART_H

#include "stm32f4xx.h"
#include <stdio.h>

/* �궨�� */
/***********************************************************************************************/
#define DEBUG_USART                             USART1
#define DEBUG_USART_CLK                         RCC_APB2Periph_USART1
#define DEBUG_USART_BAUDRATE                    115200  //���ڲ�����

#define DEBUG_USART_RX_GPIO_PORT                GPIOA
#define DEBUG_USART_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_RX_PIN                      GPIO_Pin_10
#define DEBUG_USART_RX_AF                       GPIO_AF_USART1
#define DEBUG_USART_RX_SOURCE                   GPIO_PinSource10

#define DEBUG_USART_TX_GPIO_PORT                GPIOA
#define DEBUG_USART_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOA
#define DEBUG_USART_TX_PIN                      GPIO_Pin_9
#define DEBUG_USART_TX_AF                       GPIO_AF_USART1
#define DEBUG_USART_TX_SOURCE                   GPIO_PinSource9

#define DEBUG_USART_IRQHandler                  USART1_IRQHandler
#define DEBUG_USART_IRQ                 		USART1_IRQn
/***********************************************************************************************/

/* �������� */
void Debug_Uart_Config(void); // USART1���ú���

void Debug_SendByte(USART_TypeDef * pUSARTx, uint8_t ch); // �ַ����ͺ���
void Debug_SendString(USART_TypeDef * pUSARTx, char * str); // �ַ������ͺ���


#endif

