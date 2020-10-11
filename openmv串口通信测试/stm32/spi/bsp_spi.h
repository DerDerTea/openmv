#ifndef		__BSP_SPI_H
#define		__BSP_SPI_H

#include "stm32f4xx.h"

#define     SPIx_FLASH                      SPI5
#define     SPIx_FLASH_CLK                  RCC_APB2Periph_SPI5

#define     SPI_FLASH_CE_GPIO_CLK           RCC_AHB1Periph_GPIOF
#define     SPI_FLASH_CE_GPIO_PORT          GPIOF
#define     SPI_FLASH_CE_GPIO_PIN           GPIO_Pin_6

#define     SPI_FLASH_SCK_GPIO_CLK          RCC_AHB1Periph_GPIOF
#define     SPI_FLASH_SCK_GPIO_PORT         GPIOF
#define     SPI_FLASH_SCK_GPIO_PIN          GPIO_Pin_7
#define     SPI_FLASH_SCK_GPIO_PINSOURCE    GPIO_PinSource7
#define     SPI_FLASH_SCK_GPIO_AF           GPIO_AF_SPI5

#define     SPI_FLASH_MISO_GPIO_CLK         RCC_AHB1Periph_GPIOF
#define     SPI_FLASH_MISO_GPIO_PORT        GPIOF
#define     SPI_FLASH_MISO_GPIO_PIN         GPIO_Pin_8
#define     SPI_FLASH_MISO_GPIO_PINSOURCE   GPIO_PinSource8
#define     SPI_FLASH_MISO_GPIO_AF          GPIO_AF_SPI5

#define     SPI_FLASH_MOSI_GPIO_CLK         RCC_AHB1Periph_GPIOF
#define     SPI_FLASH_MOSI_GPIO_PORT        GPIOF
#define     SPI_FLASH_MOSI_GPIO_PIN         GPIO_Pin_9
#define     SPI_FLASH_MOSI_GPIO_PINSOURCE   GPIO_PinSource9
#define     SPI_FLASH_MOSI_GPIO_AF          GPIO_AF_SPI5

#define     SPI_FLASH_CE_DISBALE            GPIO_SetBits(SPI_FLASH_CE_GPIO_PORT,SPI_FLASH_CE_GPIO_PIN)
#define     SPI_FLASH_CE_ENABLE             GPIO_ResetBits(SPI_FLASH_CE_GPIO_PORT,SPI_FLASH_CE_GPIO_PIN)

#define     SPI_FLASH_PageSize              256
#define     DUMMY                           0xFF
#define     WRITE_ENABLE                    0x06
#define     Enter4ByteMode                  0xB7
#define     ReadStatusRegister3             0x15
#define     READ_STATUS                     0x05
#define     SECTOR_ERASE                    0x20
#define     JEDEC_ID                        0x9F
#define     READ_DATE                       0x13
#define     PAGE_PROGRAM                    0x12


void SPIx_Init(void);
void SPI_FLASH_Mode(void);
uint32_t SPI_Flash_ReadID(void);
void SectorErase(uint32_t Addr);
void Read_Buffer(uint32_t Addr, uint8_t *pDate, uint16_t Num);
void Write_Buffer(uint32_t Addr, uint8_t *pDate, uint16_t Num);


#endif		/* __BSP_SPI_H */
