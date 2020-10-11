#ifndef __BSP_LCD_H
#define __BSP_LCD_H

#include "stm32f4xx.h"
#include "./spi/bsp_spi.h"

#define VERTICAL 0

/*����Һ���ź��ߵ����Ÿ��ñ����AF9*/
#define GPIO_AF_LTDC_AF9 GPIO_AF9_LTDC
//��ɫ������
#define LTDC_R0_GPIO_PORT GPIOH
#define LTDC_R0_GPIO_CLK RCC_AHB1Periph_GPIOH
#define LTDC_R0_GPIO_PIN GPIO_Pin_2
#define LTDC_R0_PINSOURCE GPIO_PinSource2
#define LTDC_R0_AF GPIO_AF_LTDC

#define LTDC_R1_GPIO_PORT GPIOH
#define LTDC_R1_GPIO_CLK RCC_AHB1Periph_GPIOH
#define LTDC_R1_GPIO_PIN GPIO_Pin_3
#define LTDC_R1_PINSOURCE GPIO_PinSource3
#define LTDC_R1_AF GPIO_AF_LTDC

#define LTDC_R2_GPIO_PORT GPIOH
#define LTDC_R2_GPIO_CLK RCC_AHB1Periph_GPIOH
#define LTDC_R2_GPIO_PIN GPIO_Pin_8
#define LTDC_R2_PINSOURCE GPIO_PinSource8
#define LTDC_R2_AF GPIO_AF_LTDC

#define LTDC_R3_GPIO_PORT GPIOB
#define LTDC_R3_GPIO_CLK RCC_AHB1Periph_GPIOB
#define LTDC_R3_GPIO_PIN GPIO_Pin_0
#define LTDC_R3_PINSOURCE GPIO_PinSource0
#define LTDC_R3_AF GPIO_AF_LTDC_AF9

#define LTDC_R4_GPIO_PORT GPIOA
#define LTDC_R4_GPIO_CLK RCC_AHB1Periph_GPIOA
#define LTDC_R4_GPIO_PIN GPIO_Pin_11
#define LTDC_R4_PINSOURCE GPIO_PinSource11
#define LTDC_R4_AF GPIO_AF_LTDC

#define LTDC_R5_GPIO_PORT GPIOA
#define LTDC_R5_GPIO_CLK RCC_AHB1Periph_GPIOA
#define LTDC_R5_GPIO_PIN GPIO_Pin_12
#define LTDC_R5_PINSOURCE GPIO_PinSource12
#define LTDC_R5_AF GPIO_AF_LTDC

#define LTDC_R6_GPIO_PORT GPIOB
#define LTDC_R6_GPIO_CLK RCC_AHB1Periph_GPIOB
#define LTDC_R6_GPIO_PIN GPIO_Pin_1
#define LTDC_R6_PINSOURCE GPIO_PinSource1
#define LTDC_R6_AF GPIO_AF_LTDC_AF9

#define LTDC_R7_GPIO_PORT GPIOG
#define LTDC_R7_GPIO_CLK RCC_AHB1Periph_GPIOG
#define LTDC_R7_GPIO_PIN GPIO_Pin_6
#define LTDC_R7_PINSOURCE GPIO_PinSource6
#define LTDC_R7_AF GPIO_AF_LTDC
//��ɫ������
#define LTDC_G0_GPIO_PORT GPIOE
#define LTDC_G0_GPIO_CLK RCC_AHB1Periph_GPIOE
#define LTDC_G0_GPIO_PIN GPIO_Pin_5
#define LTDC_G0_PINSOURCE GPIO_PinSource5
#define LTDC_G0_AF GPIO_AF_LTDC

#define LTDC_G1_GPIO_PORT GPIOE
#define LTDC_G1_GPIO_CLK RCC_AHB1Periph_GPIOE
#define LTDC_G1_GPIO_PIN GPIO_Pin_6
#define LTDC_G1_PINSOURCE GPIO_PinSource6
#define LTDC_G1_AF GPIO_AF_LTDC

#define LTDC_G2_GPIO_PORT GPIOH
#define LTDC_G2_GPIO_CLK RCC_AHB1Periph_GPIOH
#define LTDC_G2_GPIO_PIN GPIO_Pin_13
#define LTDC_G2_PINSOURCE GPIO_PinSource13
#define LTDC_G2_AF GPIO_AF_LTDC

#define LTDC_G3_GPIO_PORT GPIOG
#define LTDC_G3_GPIO_CLK RCC_AHB1Periph_GPIOG
#define LTDC_G3_GPIO_PIN GPIO_Pin_10
#define LTDC_G3_PINSOURCE GPIO_PinSource10
#define LTDC_G3_AF GPIO_AF_LTDC_AF9

#define LTDC_G4_GPIO_PORT GPIOH
#define LTDC_G4_GPIO_CLK RCC_AHB1Periph_GPIOH
#define LTDC_G4_GPIO_PIN GPIO_Pin_15
#define LTDC_G4_PINSOURCE GPIO_PinSource15
#define LTDC_G4_AF GPIO_AF_LTDC

#define LTDC_G5_GPIO_PORT GPIOI
#define LTDC_G5_GPIO_CLK RCC_AHB1Periph_GPIOI
#define LTDC_G5_GPIO_PIN GPIO_Pin_0
#define LTDC_G5_PINSOURCE GPIO_PinSource0
#define LTDC_G5_AF GPIO_AF_LTDC

#define LTDC_G6_GPIO_PORT GPIOC
#define LTDC_G6_GPIO_CLK RCC_AHB1Periph_GPIOC
#define LTDC_G6_GPIO_PIN GPIO_Pin_7
#define LTDC_G6_PINSOURCE GPIO_PinSource7
#define LTDC_G6_AF GPIO_AF_LTDC

#define LTDC_G7_GPIO_PORT GPIOI
#define LTDC_G7_GPIO_CLK RCC_AHB1Periph_GPIOI
#define LTDC_G7_GPIO_PIN GPIO_Pin_2
#define LTDC_G7_PINSOURCE GPIO_PinSource2
#define LTDC_G7_AF GPIO_AF_LTDC

//��ɫ������
#define LTDC_B0_GPIO_PORT GPIOE
#define LTDC_B0_GPIO_CLK RCC_AHB1Periph_GPIOE
#define LTDC_B0_GPIO_PIN GPIO_Pin_4
#define LTDC_B0_PINSOURCE GPIO_PinSource4
#define LTDC_B0_AF GPIO_AF_LTDC

#define LTDC_B1_GPIO_PORT GPIOG
#define LTDC_B1_GPIO_CLK RCC_AHB1Periph_GPIOG
#define LTDC_B1_GPIO_PIN GPIO_Pin_12
#define LTDC_B1_PINSOURCE GPIO_PinSource12
#define LTDC_B1_AF GPIO_AF_LTDC

#define LTDC_B2_GPIO_PORT GPIOD
#define LTDC_B2_GPIO_CLK RCC_AHB1Periph_GPIOD
#define LTDC_B2_GPIO_PIN GPIO_Pin_6
#define LTDC_B2_PINSOURCE GPIO_PinSource6
#define LTDC_B2_AF GPIO_AF_LTDC

#define LTDC_B3_GPIO_PORT GPIOG
#define LTDC_B3_GPIO_CLK RCC_AHB1Periph_GPIOG
#define LTDC_B3_GPIO_PIN GPIO_Pin_11
#define LTDC_B3_PINSOURCE GPIO_PinSource11
#define LTDC_B3_AF GPIO_AF_LTDC

#define LTDC_B4_GPIO_PORT GPIOI
#define LTDC_B4_GPIO_CLK RCC_AHB1Periph_GPIOI
#define LTDC_B4_GPIO_PIN GPIO_Pin_4
#define LTDC_B4_PINSOURCE GPIO_PinSource4
#define LTDC_B4_AF GPIO_AF_LTDC

#define LTDC_B5_GPIO_PORT GPIOA
#define LTDC_B5_GPIO_CLK RCC_AHB1Periph_GPIOA
#define LTDC_B5_GPIO_PIN GPIO_Pin_3
#define LTDC_B5_PINSOURCE GPIO_PinSource3
#define LTDC_B5_AF GPIO_AF_LTDC

#define LTDC_B6_GPIO_PORT GPIOB
#define LTDC_B6_GPIO_CLK RCC_AHB1Periph_GPIOB
#define LTDC_B6_GPIO_PIN GPIO_Pin_8
#define LTDC_B6_PINSOURCE GPIO_PinSource8
#define LTDC_B6_AF GPIO_AF_LTDC

#define LTDC_B7_GPIO_PORT GPIOB
#define LTDC_B7_GPIO_CLK RCC_AHB1Periph_GPIOB
#define LTDC_B7_GPIO_PIN GPIO_Pin_9
#define LTDC_B7_PINSOURCE GPIO_PinSource9
#define LTDC_B7_AF GPIO_AF_LTDC

//�����ź���
/*����ʱ��CLK*/
#define LTDC_CLK_GPIO_PORT GPIOG
#define LTDC_CLK_GPIO_CLK RCC_AHB1Periph_GPIOG
#define LTDC_CLK_GPIO_PIN GPIO_Pin_7
#define LTDC_CLK_PINSOURCE GPIO_PinSource7
#define LTDC_CLK_AF GPIO_AF_LTDC

/*ˮƽͬ���ź�HSYNC*/
#define LTDC_HSYNC_GPIO_PORT GPIOI
#define LTDC_HSYNC_GPIO_CLK RCC_AHB1Periph_GPIOI
#define LTDC_HSYNC_GPIO_PIN GPIO_Pin_10
#define LTDC_HSYNC_PINSOURCE GPIO_PinSource10
#define LTDC_HSYNC_AF GPIO_AF_LTDC

/*��ֱͬ���ź�VSYNC*/
#define LTDC_VSYNC_GPIO_PORT GPIOI
#define LTDC_VSYNC_GPIO_CLK RCC_AHB1Periph_GPIOI
#define LTDC_VSYNC_GPIO_PIN GPIO_Pin_9
#define LTDC_VSYNC_PINSOURCE GPIO_PinSource9
#define LTDC_VSYNC_AF GPIO_AF_LTDC

/*����ʹ���ź�DE*/
#define LTDC_DE_GPIO_PORT GPIOF
#define LTDC_DE_GPIO_CLK RCC_AHB1Periph_GPIOF
#define LTDC_DE_GPIO_PIN GPIO_Pin_10
#define LTDC_DE_PINSOURCE GPIO_PinSource10
#define LTDC_DE_AF GPIO_AF_LTDC

/*Һ����ʹ���ź�DISP���ߵ�ƽʹ��*/
#define LTDC_DISP_GPIO_PORT GPIOD
#define LTDC_DISP_GPIO_CLK RCC_AHB1Periph_GPIOD
#define LTDC_DISP_GPIO_PIN GPIO_Pin_4

/*Һ���������źţ��ߵ�ƽʹ��*/
#define LTDC_BL_GPIO_PORT GPIOD
#define LTDC_BL_GPIO_CLK RCC_AHB1Periph_GPIOD
#define LTDC_BL_GPIO_PIN GPIO_Pin_7

/*ʵ�ʲ��Կ��õĽϿ������(5��)*/
#define HSW 1 //HSYNC���
#define VSW 1 //VSYNC���

#define HBP 46 //HSYNC�����Ч����
#define VBP 23 //VSYNC�����Ч����

#define HFP 22 //HSYNCǰ����Ч����
#define VFP 22 //VSYNCǰ����Ч����

#define LCD_PIXEL_WIDTH ((uint16_t)800)  //��Ч���
#define LCD_PIXEL_HEIGHT ((uint16_t)480) //��Ч�߶�

/* ���ײ㣩��һ���׵�ַ */
#define LCD_GROUND_START_ADDR ((uint32_t)0xD0000000)
/* һ��Һ���������� */
#define BUFFER_OFFSET ((uint32_t)LCD_PIXEL_WIDTH * LCD_PIXEL_HEIGHT * 4)
/* �����㣩�ڶ����׵�ַ */
#define LCD_TOP_START_ADDR (LCD_GROUND_START_ADDR + BUFFER_OFFSET)

/* Һ���ķ��� */
#define LCD_DIR_HORIZONTAL 0x0000
#define LCD_DIR_VERTICAL 0x0001
#define ABS(X) ((X) > 0 ? (X) : -(X))

/* NORFlash�ֿ��ַ */
#define STANDARD_ADDRESS 1360 * 4096
#define VERTICAL_ADDRESS 3812 * 4096

void LCD_Init(void);

/*******************************���ܺ���BEGIN************************************/
void PutPixel(int16_t x, int16_t y, uint32_t Current_Addr, uint32_t Current_ARGB);
void LCD_DrawLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length, uint8_t Direction, uint32_t Current_Addr, uint32_t Current_ARGB);
void LCD_DrawUniLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t Current_Addr, uint32_t Current_ARGB);
void LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint32_t Current_Addr, uint32_t Current_ARGB);
void LCD_DrawFullRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint32_t Current_Addr, uint32_t Current_ARGB);
void LCD_FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3, uint32_t Current_Addr, uint32_t Current_ARGB);
void LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint32_t Current_Addr, uint32_t Current_ARGB);
void LCD_DrawFullCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint32_t Current_Addr, uint32_t Current_ARGB);
void LCD_DrawEllipse(int Xpos, int Ypos, int Radius, int Radius2, uint32_t Current_Addr, uint32_t Current_ARGB);
void LCD_DrawFullEllipse(int Xpos, int Ypos, int Radius, int Radius2, uint32_t Current_Addr, uint32_t Current_ARGB);
/*******************************���ܺ���END**************************************/

/*******************************��ģ����BEGIN************************************/
void LCD_DispString_EN(uint16_t Xpos, uint16_t Ypos, uint32_t Current_Addr, uint32_t Font_Color, uint32_t Groung_Color, char *ptr);
void LCD_DispString_CH(uint16_t Xpos, uint16_t Ypos, uint32_t Current_Addr, uint32_t Font_Color, uint32_t Groung_Color, char *pString);
void LCD_DispString_EN_CH(uint16_t Xpos, uint16_t Ypos, uint32_t Current_Addr, uint32_t Font_Color, uint32_t Groung_Color, char *pString);
/*******************************��ģ����END**************************************/

#endif /* __BSP_LCD_H */
