#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f4xx.h"

#define LED_R_CLK            RCC_AHB1Periph_GPIOH
#define LED_R_PIN            GPIO_Pin_10
#define LED_R_PORT      		 GPIOH

#define LED_G_CLK            RCC_AHB1Periph_GPIOH
#define LED_G_PIN            GPIO_Pin_11
#define LED_G_PORT      		 GPIOH

#define LED_B_CLK            RCC_AHB1Periph_GPIOH
#define LED_B_PIN            GPIO_Pin_12
#define LED_B_PORT      		 GPIOH

#define LED_RED_ON           GPIO_ResetBits( LED_R_PORT, LED_R_PIN )
#define LED_GREEN_ON         GPIO_ResetBits( LED_G_PORT, LED_G_PIN )
#define LED_BLUE_ON          GPIO_ResetBits( LED_B_PORT, LED_B_PIN )

#define LED_RED_OFF          GPIO_SetBits( LED_R_PORT, LED_R_PIN )
#define LED_GREEN_OFF        GPIO_SetBits( LED_G_PORT, LED_G_PIN )
#define LED_BLUE_OFF         GPIO_SetBits( LED_B_PORT, LED_B_PIN )

//ºì
#define LED_RED              LED_RED_ON;LED_GREEN_OFF;LED_BLUE_OFF

//ÂÌ
#define LED_GREEN            LED_RED_OFF;LED_GREEN_ON;LED_BLUE_OFF

//À¶
#define LED_BLUE             LED_RED_OFF;LED_GREEN_OFF;LED_BLUE_ON

//»Æ(ºì+ÂÌ)
#define LED_YELLOW    			 LED_RED_ON;LED_GREEN_ON;LED_BLUE_OFF

//×Ï(ºì+À¶)
#define LED_PURPLE    			 LED_RED_ON;LED_GREEN_OFF;LED_BLUE_ON

//Çà(ÂÌ+À¶)
#define LED_CYAN      			 LED_RED_OFF;LED_GREEN_ON;LED_BLUE_ON

//°×(ºì+ÂÌ+À¶)
#define LED_WHITE     			 LED_RED_ON;LED_GREEN_ON;LED_BLUE_ON

//¹Ø
#define LED_OFF       			 LED_RED_OFF;LED_GREEN_OFF;LED_BLUE_OFF

#define digitalToggle(p,i)	 {p->ODR ^=i;}		//Êä³ö·´×ª×´Ì¬

//ºìµÆ·´×ª
#define LED_RED_TOGGLE		   digitalToggle(LED_R_PORT,LED_R_PIN)

//ÂÌµÆ·´×ª
#define LED_GREEN_TOGGLE		 digitalToggle(LED_G_PORT,LED_G_PIN)

//À¶µÆ·´×ª
#define LED_BLUE_TOGGLE		   digitalToggle(LED_B_PORT,LED_B_PIN)


void LED_Config(void);


#endif  /*__BSP_LED_H*/

