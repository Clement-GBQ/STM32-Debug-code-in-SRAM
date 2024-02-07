/**
  ******************************************************************************
  * @file    bsp_led.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   led应用函数接口
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板  
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "./led/bsp_led.h"   

 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
	/* 定义一个GPIO_InitTypeDef类型的结构体 */
	GPIO_InitTypeDef GPIO_InitStructure;

	/* 使能GPIO时钟 */
	RCC_AHB1PeriphClockCmd(DS1_GPIO_CLK | DS0_GPIO_CLK, ENABLE);

	/* DS0配置 */
	GPIO_InitStructure.GPIO_Pin = DS0_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // 输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; // 上拉电阻
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(DS0_GPIO_PORT, &GPIO_InitStructure);

	/* DS1配置 */
	GPIO_InitStructure.GPIO_Pin = DS1_PIN;
	GPIO_Init(DS1_GPIO_PORT, &GPIO_InitStructure);

	
	DS0_OFF; // 关闭DS0
	DS1_OFF; // 关闭DS1
}
/*********************************************END OF FILE**********************/
