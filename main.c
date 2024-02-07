/**
  * @file    	main.c
  * @author  	Clement
  * @version  	V1.0
  * @date    	2023.11.25
  * @brief   	��1.8.0�汾�⽨�Ĺ���ģ��
  */

#include "stm32f4xx.h"
#include "bsp_debug_uart.h"
#include "bsp_led.h"

// ��ʱ��������
void Delay(__IO u32 nCount); 

int main(void)
{
	/* ��������main����֮ǰ�������ļ���statup_stm32f4xx.s�Ѿ�����
	* SystemInit()������ϵͳʱ�ӳ�ʼ����168MHZ
	* SystemInit()��system_stm32f4xx.c�ж���
	* ����û����޸�ϵͳʱ�ӣ������б�д�����޸�
	*/

	/* add your code here ^_^. */
	
	// Initialize LED and UART
	LED_GPIO_Config();
	Debug_Uart_Config();

	for (uint8_t i = 0; i < 3; i++)
	{
		printf("hello \r\n");
	}

	while (1)
	{
		// �����˸3��
		DS0_ON;
		Delay(0xFFFFFF);
		DS0_OFF;
		Delay(0xFFFFFF);
		DS0_ON;
		Delay(0xFFFFFF);
		DS0_OFF;
		Delay(0xFFFFFF);
		DS0_ON;
		Delay(0xFFFFFF);
		DS0_OFF;
		Delay(0xFFFFFF);

		// �̵���˸3��
		DS1_ON;
		Delay(0xFFFFFF);
		DS1_OFF;
		Delay(0xFFFFFF);
		DS1_ON;
		Delay(0xFFFFFF);
		DS1_OFF;
		Delay(0xFFFFFF);
		DS1_ON;
		Delay(0xFFFFFF);
		DS1_OFF;
		Delay(0xFFFFFF);

		// ���̵�ͬʱ��˸3��
		for (uint16_t in = 0; in < 3; in++)
		{
			DS0_ON;
			DS1_ON;
			Delay(0xFFFFFF);
			Delay(0xFFFFFF);
			DS0_OFF;
			DS1_OFF;
			Delay(0xFFFFFF);
			Delay(0xFFFFFF);
			DS0_ON;
			DS1_ON;
			Delay(0xFFFFFF);
			Delay(0xFFFFFF);
			DS0_OFF;
			DS1_OFF;
			Delay(0xFFFFFF);
			Delay(0xFFFFFF);
			DS0_ON;
			DS1_ON;
			Delay(0xFFFFFF);
			Delay(0xFFFFFF);
			DS0_OFF;
			DS1_OFF;
			Delay(0xFFFFFF);
			Delay(0xFFFFFF);
		}
		//printf("��˸����\r\n");

		for (size_t i = 0; i < 3; i++)
		{
			printf("try\r\n");
		}
		
		printf("�������\r\n");
		
	}
	
	

}

// ��������
void Delay(__IO uint32_t nCount)	 //�򵥵���ʱ����
{
	for(; nCount != 0; nCount--);
}
