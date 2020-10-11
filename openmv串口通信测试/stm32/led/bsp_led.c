#include "./led/bsp_led.h"

void LED_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(LED_R_CLK|LED_G_CLK|LED_B_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Medium_Speed;
	
	GPIO_InitStruct.GPIO_Pin = LED_R_PIN;
	GPIO_Init(LED_R_PORT , &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED_G_PIN;
	GPIO_Init(LED_G_PORT , &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = LED_B_PIN;
	GPIO_Init(LED_B_PORT , &GPIO_InitStruct);
	
	LED_OFF;
}
