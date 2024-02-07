/**
  * @file    	main.c
  * @author  	Clement
  * @version  	V1.0
  * @date    	2023.11.25
  * @brief   	用1.8.0版本库建的工程模板
  */

#include "stm32f4xx.h"
#include "bsp_debug_uart.h"
#include "bsp_led.h"

// 延时函数声明
void Delay(__IO u32 nCount); 

int main(void)
{
	/* 程序来到main函数之前，启动文件：statup_stm32f4xx.s已经调用
	* SystemInit()函数把系统时钟初始化成168MHZ
	* SystemInit()在system_stm32f4xx.c中定义
	* 如果用户想修改系统时钟，可自行编写程序修改
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
		// 红灯闪烁3下
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

		// 绿灯闪烁3下
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

		// 红绿灯同时闪烁3下
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
		//printf("闪烁结束\r\n");

		for (size_t i = 0; i < 3; i++)
		{
			printf("try\r\n");
		}
		
		printf("迭代完成\r\n");
		
	}
	
	

}

// 函数定义
void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
