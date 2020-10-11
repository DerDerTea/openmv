#include "./usart/bsp_usart.h"
#include <string.h>
#include <stdlib.h>

void USART1_init(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;

    RCC_AHB1PeriphClockCmd(USART1_GPIO_CLK,ENABLE);
    RCC_APB2PeriphClockCmd(USART1_CLK,ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQN;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;

    GPIO_InitStruct.GPIO_Pin = USART1_GPIO_RX_PIN;
    GPIO_PinAFConfig(USART1_GPIO_RX_PORT,USART1_GPIO_RX_SOURCE,USART1_GPIO_RX_AF);
    GPIO_Init(USART1_GPIO_RX_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = USART1_GPIO_TX_PIN;
    GPIO_PinAFConfig(USART1_GPIO_TX_PORT,USART1_GPIO_TX_SOURCE,USART1_GPIO_TX_AF);
    GPIO_Init(USART1_GPIO_TX_PORT,&GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate = USART1_BAUDRATE;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART_1,&USART_InitStruct);

    USART_ITConfig(USART_1,USART_IT_RXNE,ENABLE);
    USART_ClearFlag(USART_1,USART_IT_RXNE);

    USART_Cmd(USART_1,ENABLE);
}

void USART2_init(void)
{
    NVIC_InitTypeDef NVIC_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;

    RCC_AHB1PeriphClockCmd(USART2_GPIO_CLK,ENABLE);
    RCC_APB1PeriphClockCmd(USART2_CLK,ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQN;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;

    GPIO_InitStruct.GPIO_Pin = USART2_GPIO_RX_PIN;
    GPIO_PinAFConfig(USART2_GPIO_RX_PORT,USART2_GPIO_RX_SOURCE,USART2_GPIO_RX_AF);
    GPIO_Init(USART2_GPIO_RX_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = USART2_GPIO_TX_PIN;
    GPIO_PinAFConfig(USART2_GPIO_TX_PORT,USART2_GPIO_TX_SOURCE,USART2_GPIO_TX_AF);
    GPIO_Init(USART2_GPIO_TX_PORT,&GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate = USART2_BAUDRATE;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART_2,&USART_InitStruct);

    USART_ITConfig(USART_2,USART_IT_RXNE,ENABLE);
    USART_ClearFlag(USART_2,USART_IT_RXNE);

    USART_Cmd(USART_2,ENABLE);
}

void USART1_SendByte(char ch)
{
    USART_SendData(USART_1,ch);
    while (USART_GetFlagStatus(USART_1,USART_FLAG_TXE) == RESET);   
}

void USART1_SendString(char* str)
{
    uint16_t i = 0;
    do
    {
        USART_SendData(USART_1,*(str + i));
		while (USART_GetFlagStatus(USART_1,USART_FLAG_TXE) == RESET);
        i++;

    } while (*(str + i) != '\0');

    while (USART_GetFlagStatus(USART_1,USART_FLAG_TXE) == RESET);    
}

void USART2_SendByte(char ch)
{
    USART_SendData(USART_2,ch);
    while (USART_GetFlagStatus(USART_2,USART_FLAG_TXE) == RESET);   
}

void USART2_SendString(char* str)
{
    uint16_t i = 0;
    do
    {
        USART_SendData(USART_2,*(str + i));
		while (USART_GetFlagStatus(USART_2,USART_FLAG_TXE) == RESET);
        i++;

    } while (*(str + i) != '\0');

    while (USART_GetFlagStatus(USART_2,USART_FLAG_TXE) == RESET);    
}

int fputc(int ch, FILE *f)
{
    USART_SendData(USART_1,(uint8_t)ch);
    while (USART_GetFlagStatus(USART_1,USART_FLAG_TXE) == RESET);
    return ch;
}

int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USART_1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART_1);
}

void OpenMV_Date(char *pBuff, char *left, char *right, int *Value)
{
		char pbuff[4] = {0};
    char *pcBegin = NULL;
    char *pcEnd = NULL;
		char *pcRes = pbuff;
    pcBegin = strstr(pBuff, left);
    pcEnd = strstr(pcBegin + strlen(left), right);
    if(pcEnd == NULL || pcBegin == NULL || pcBegin > pcEnd)
    {
        return;
    }
    else
    {
        pcBegin += strlen(left);
        memcpy(pcRes, pcBegin,pcEnd - pcBegin);
				*Value = atoi(pcRes);
        return;
    } 
}

