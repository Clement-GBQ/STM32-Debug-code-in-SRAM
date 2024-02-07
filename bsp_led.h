#ifndef __LED_H
#define	__LED_H

#include "stm32f4xx.h"

/* 正点原子开发板LED引脚宏定义*/
// DS0 -- PF9
#define DS0_PIN                  GPIO_Pin_9                 
#define DS0_GPIO_PORT            GPIOF                      
#define DS0_GPIO_CLK             RCC_AHB1Periph_GPIOF

// DS1 -- PF10
#define DS1_PIN                  GPIO_Pin_10                 
#define DS1_GPIO_PORT            GPIOF                      
#define DS1_GPIO_CLK             RCC_AHB1Periph_GPIOF



/** 控制LED灯亮灭的宏，
	* LED低电平亮，设置ON=0，OFF=1
	* 若LED高电平亮，把宏设置成ON=1 ，OFF=0 即可
	*/
#define ON  0
#define OFF 1

/* 带参宏，可以像内联函数一样使用 */
#define LED1(a)	if (a)	\
					GPIO_SetBits(LED1_GPIO_PORT,LED1_PIN);\
					else		\
					GPIO_ResetBits(LED1_GPIO_PORT,LED1_PIN)

#define LED2(a)	if (a)	\
					GPIO_SetBits(LED2_GPIO_PORT,LED2_PIN);\
					else		\
					GPIO_ResetBits(LED2_GPIO_PORT,LED2_PIN)

#define LED3(a)	if (a)	\
					GPIO_SetBits(LED3_GPIO_PORT,LED3_PIN);\
					else		\
					GPIO_ResetBits(LED3_GPIO_PORT,LED3_PIN)


/* 直接操作寄存器的方法控制IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//设置为高电平
#define digitalLo(p,i)			 {p->BSRRH=i;}		//输出低电平
#define digitalToggle(p,i)	 {p->ODR ^=i;}		//输出反转状态

/* 定义控制IO的宏 */
#define DS0_TOGGLE		digitalToggle(DS0_GPIO_PORT,DS0_PIN)
#define DS0_OFF			digitalHi(DS0_GPIO_PORT,DS0_PIN)
#define DS0_ON				digitalLo(DS0_GPIO_PORT,DS0_PIN)

#define DS1_TOGGLE		digitalToggle(DS1_GPIO_PORT,DS1_PIN)
#define DS1_OFF			digitalHi(DS1_GPIO_PORT,DS1_PIN)
#define DS1_ON				digitalLo(DS1_GPIO_PORT,DS1_PIN)


// /* 基本混色，后面高级用法使用PWM可混出全彩颜色,且效果更好 */

// //红
// #define LED_RED  \
// 					LED1_ON;\
// 					LED2_OFF;\
// 					LED3_OFF

// //绿
// #define LED_GREEN		\
// 					LED1_OFF;\
// 					LED2_ON;\
// 					LED3_OFF

// //蓝
// #define LED_BLUE	\
// 					LED1_OFF;\
// 					LED2_OFF;\
// 					LED3_ON

					
// //黄(红+绿)					
// #define LED_YELLOW	\
// 					LED1_ON;\
// 					LED2_ON;\
// 					LED3_OFF
// //紫(红+蓝)
// #define LED_PURPLE	\
// 					LED1_ON;\
// 					LED2_OFF;\
// 					LED3_ON

// //青(绿+蓝)
// #define LED_CYAN \
// 					LED1_OFF;\
// 					LED2_ON;\
// 					LED3_ON
					
// //白(红+绿+蓝)
// #define LED_WHITE	\
// 					LED1_ON;\
// 					LED2_ON;\
// 					LED3_ON
					
// //黑(全部关闭)
// #define LED_RGBOFF	\
// 					LED1_OFF;\
// 					LED2_OFF;\
// 					LED3_OFF		




void LED_GPIO_Config(void);

#endif /* __LED_H */
