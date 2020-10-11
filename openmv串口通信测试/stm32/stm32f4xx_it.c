/**
  ******************************************************************************
  * @file    ADC/ADC_DMA/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdlib.h>
#include "stm32f4xx_it.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h"
#include "./lcd/bsp_touch.h"

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup ADC_DMA
  * @{
  */  

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s).  */
/******************************************************************************/

/* EXTI中断服务函数 */
void GTP_IRQHandler(void)
{
	if(EXTI_GetITStatus(GTP_INT_EXTI_LINE) != RESET) //确保是否产生了EXTI Line中断
	{
		EXTI_ClearITPendingBit(GTP_INT_EXTI_LINE);     //清除中断标志位
		GT91x_Touch_Get();
	}
}

char string[16] = "[50,50]";
uint8_t cnt = 0;
void USART1_IRQHANDLER(void)
{
	char temp = 0;
  if (USART_GetFlagStatus(USART_1,USART_FLAG_RXNE) != RESET)
  {
		temp = USART_ReceiveData(USART_1);
		if(temp != '\n')
		{
			string[cnt++] = temp;
		}
		else
		{
			cnt = 0;
		}
		if(cnt > 16)
		{
			cnt = 0;
		}
  }
	USART_ClearFlag(USART_1,USART_IT_RXNE);
}

void USART2_IRQHANDLER(void)
{
	char Temp;
  if (USART_GetFlagStatus(USART_2,USART_FLAG_RXNE) != RESET)
  {
		USART_ClearFlag(USART_2,USART_IT_RXNE);
		Temp = USART_ReceiveData(USART_2);
		switch(Temp)
		{
			/* 方向 */
			case '6' :
				LED_RED;
			break;
			case '7' :
				LED_GREEN;
			break;
			case '8' :
				LED_BLUE;
			break;
			case '9' :
				LED_YELLOW;
			break;
			case 'a' :
				LED_PURPLE;
			break;
			case 'b' :
				LED_CYAN;
			break;
			
			/* test2 */
			case 'c' :
				LED_WHITE;
			break;	
			case '0' :
				LED_OFF;
			break;
			
			/* test3 */
			case 'd' :
				printf("d");
			break;	
			case 'e' :
				printf("e");
			break;

			
		}
  }
}



/**
  * @}
  */ 
  
/**
  * @}
  */   


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
