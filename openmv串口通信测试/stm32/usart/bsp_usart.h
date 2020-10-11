#ifndef   __BSP_USART_H
#define   __BSP_USART_H

#include "stm32f4xx.h"
#include <stdio.h>


#define  USART1_GPIO_CLK         RCC_AHB1Periph_GPIOA     
#define  USART1_GPIO_RX_PORT     GPIOA
#define  USART1_GPIO_RX_PIN      GPIO_Pin_10
#define  USART1_GPIO_RX_SOURCE   GPIO_PinSource10
#define  USART1_GPIO_RX_AF       GPIO_AF_USART1
#define  USART1_GPIO_TX_PORT     GPIOA
#define  USART1_GPIO_TX_PIN      GPIO_Pin_9
#define  USART1_GPIO_TX_SOURCE   GPIO_PinSource9
#define  USART1_GPIO_TX_AF       GPIO_AF_USART1
#define  USART_1                 USART1
#define  USART1_CLK              RCC_APB2Periph_USART1
#define  USART1_BAUDRATE         115200
#define  USART1_IRQN             USART1_IRQn
#define  USART1_IRQHANDLER       USART1_IRQHandler

#define  USART2_GPIO_CLK         RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD
#define  USART2_GPIO_RX_PORT     GPIOD
#define  USART2_GPIO_RX_PIN      GPIO_Pin_2
#define  USART2_GPIO_RX_SOURCE   GPIO_PinSource2
#define  USART2_GPIO_RX_AF       GPIO_AF_UART5
#define  USART2_GPIO_TX_PORT     GPIOC
#define  USART2_GPIO_TX_PIN      GPIO_Pin_12
#define  USART2_GPIO_TX_SOURCE   GPIO_PinSource12
#define  USART2_GPIO_TX_AF       GPIO_AF_UART5
#define  USART_2                 UART5
#define  USART2_CLK              RCC_APB1Periph_UART5
#define  USART2_BAUDRATE         115200
#define  USART2_IRQN             UART5_IRQn
#define  USART2_IRQHANDLER       UART5_IRQHandler


void USART1_init(void);
void USART1_SendByte(char ch);
void USART1_SendString(char* str);
void USART2_init(void);
void USART2_SendByte(char ch);
void USART2_SendString(char* str);
void OpenMV_Date(char *pBuff, char *left, char *right, int *Value);

#endif   /* __BSP_USART_H */

