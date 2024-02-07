/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ledӦ�ú����ӿ�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./led/bsp_led.h"   

 /**
  * @brief  ��ʼ������LED��IO
  * @param  ��
  * @retval ��
  */
void LED_GPIO_Config(void)
{		
	/* ����һ��GPIO_InitTypeDef���͵Ľṹ�� */
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ʹ��GPIOʱ�� */
	RCC_AHB1PeriphClockCmd(DS1_GPIO_CLK | DS0_GPIO_CLK, ENABLE);

	/* DS0���� */
	GPIO_InitStructure.GPIO_Pin = DS0_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // �������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // ��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(DS0_GPIO_PORT, &GPIO_InitStructure);

	/* DS1���� */
	GPIO_InitStructure.GPIO_Pin = DS1_PIN;
	GPIO_Init(DS1_GPIO_PORT, &GPIO_InitStructure);

	
	DS0_OFF; // �ر�DS0
	DS1_OFF; // �ر�DS1
}
/*********************************************END OF FILE**********************/
