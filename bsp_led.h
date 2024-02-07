#ifndef __LED_H
#define	__LED_H

#include "stm32f4xx.h"

/* ����ԭ�ӿ�����LED���ź궨��*/
// DS0 -- PF9
#define DS0_PIN                  GPIO_Pin_9                 
#define DS0_GPIO_PORT            GPIOF                      
#define DS0_GPIO_CLK             RCC_AHB1Periph_GPIOF

// DS1 -- PF10
#define DS1_PIN                  GPIO_Pin_10                 
#define DS1_GPIO_PORT            GPIOF                      
#define DS1_GPIO_CLK             RCC_AHB1Periph_GPIOF



/** ����LED������ĺ꣬
	* LED�͵�ƽ��������ON=0��OFF=1
	* ��LED�ߵ�ƽ�����Ѻ����ó�ON=1 ��OFF=0 ����
	*/
#define ON  0
#define OFF 1

/* ���κ꣬��������������һ��ʹ�� */
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


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define	digitalHi(p,i)			 {p->BSRRL=i;}		//����Ϊ�ߵ�ƽ
#define digitalLo(p,i)			 {p->BSRRH=i;}		//����͵�ƽ
#define digitalToggle(p,i)	 {p->ODR ^=i;}		//�����ת״̬

/* �������IO�ĺ� */
#define DS0_TOGGLE		digitalToggle(DS0_GPIO_PORT,DS0_PIN)
#define DS0_OFF			digitalHi(DS0_GPIO_PORT,DS0_PIN)
#define DS0_ON				digitalLo(DS0_GPIO_PORT,DS0_PIN)

#define DS1_TOGGLE		digitalToggle(DS1_GPIO_PORT,DS1_PIN)
#define DS1_OFF			digitalHi(DS1_GPIO_PORT,DS1_PIN)
#define DS1_ON				digitalLo(DS1_GPIO_PORT,DS1_PIN)


// /* ������ɫ������߼��÷�ʹ��PWM�ɻ��ȫ����ɫ,��Ч������ */

// //��
// #define LED_RED  \
// 					LED1_ON;\
// 					LED2_OFF;\
// 					LED3_OFF

// //��
// #define LED_GREEN		\
// 					LED1_OFF;\
// 					LED2_ON;\
// 					LED3_OFF

// //��
// #define LED_BLUE	\
// 					LED1_OFF;\
// 					LED2_OFF;\
// 					LED3_ON

					
// //��(��+��)					
// #define LED_YELLOW	\
// 					LED1_ON;\
// 					LED2_ON;\
// 					LED3_OFF
// //��(��+��)
// #define LED_PURPLE	\
// 					LED1_ON;\
// 					LED2_OFF;\
// 					LED3_ON

// //��(��+��)
// #define LED_CYAN \
// 					LED1_OFF;\
// 					LED2_ON;\
// 					LED3_ON
					
// //��(��+��+��)
// #define LED_WHITE	\
// 					LED1_ON;\
// 					LED2_ON;\
// 					LED3_ON
					
// //��(ȫ���ر�)
// #define LED_RGBOFF	\
// 					LED1_OFF;\
// 					LED2_OFF;\
// 					LED3_OFF		




void LED_GPIO_Config(void);

#endif /* __LED_H */
