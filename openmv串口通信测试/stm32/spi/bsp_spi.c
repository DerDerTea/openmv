#include "./spi/bsp_spi.h"

void SPIx_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  SPI_InitTypeDef SPI_InitStruct;

  RCC_AHB1PeriphClockCmd(SPI_FLASH_CE_GPIO_CLK | SPI_FLASH_SCK_GPIO_CLK |
                             SPI_FLASH_MISO_GPIO_CLK | SPI_FLASH_MOSI_GPIO_CLK,
                         ENABLE);
  RCC_APB2PeriphClockCmd(SPIx_FLASH_CLK, ENABLE);

  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;

  GPIO_InitStruct.GPIO_Pin = SPI_FLASH_CE_GPIO_PIN;
  GPIO_Init(SPI_FLASH_CE_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;

  GPIO_PinAFConfig(SPI_FLASH_SCK_GPIO_PORT, SPI_FLASH_SCK_GPIO_PINSOURCE, SPI_FLASH_SCK_GPIO_AF);
  GPIO_InitStruct.GPIO_Pin = SPI_FLASH_SCK_GPIO_PIN;
  GPIO_Init(SPI_FLASH_SCK_GPIO_PORT, &GPIO_InitStruct);

  GPIO_PinAFConfig(SPI_FLASH_MISO_GPIO_PORT, SPI_FLASH_MISO_GPIO_PINSOURCE, SPI_FLASH_MISO_GPIO_AF);
  GPIO_InitStruct.GPIO_Pin = SPI_FLASH_MISO_GPIO_PIN;
  GPIO_Init(SPI_FLASH_MISO_GPIO_PORT, &GPIO_InitStruct);

  GPIO_PinAFConfig(SPI_FLASH_MOSI_GPIO_PORT, SPI_FLASH_MOSI_GPIO_PINSOURCE, SPI_FLASH_MOSI_GPIO_AF);
  GPIO_InitStruct.GPIO_Pin = SPI_FLASH_MOSI_GPIO_PIN;
  GPIO_Init(SPI_FLASH_MOSI_GPIO_PORT, &GPIO_InitStruct);

  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge; //�ڶ�������
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;  //���иߵ�ƽ
  SPI_InitStruct.SPI_CRCPolynomial = 0;     //����У��
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;

  SPI_Init(SPIx_FLASH, &SPI_InitStruct);
  SPI_Cmd(SPIx_FLASH, ENABLE);

  SPI_FLASH_Mode();
}

static uint8_t SPI_Read_Write(uint8_t Date)
{
  while (!SPI_I2S_GetFlagStatus(SPIx_FLASH, SPI_I2S_FLAG_TXE))
    ;

  SPI_I2S_SendData(SPIx_FLASH, Date);

  while (!SPI_I2S_GetFlagStatus(SPIx_FLASH, SPI_I2S_FLAG_RXNE))
    ;

  return SPI_I2S_ReceiveData(SPIx_FLASH);
}

static void Wait_For_Ready(void)
{
  uint8_t Temp = 0;
  SPI_FLASH_CE_ENABLE;

  SPI_Read_Write(READ_STATUS);
  do
  {
    Temp = SPI_Read_Write(DUMMY);
  } while ((Temp & 0x01) == 0x01);
  SPI_FLASH_CE_DISBALE;
}

void SPI_FLASH_Mode(void)
{
  uint8_t Temp = 0;
  SPI_FLASH_CE_ENABLE;

  SPI_Read_Write(ReadStatusRegister3);
  Temp = SPI_Read_Write(DUMMY);
  SPI_FLASH_CE_DISBALE;

  if ((Temp & 0x01) == 0)
  {
    SPI_FLASH_CE_ENABLE;
    SPI_Read_Write(Enter4ByteMode);
    SPI_FLASH_CE_DISBALE;
  }
}

static void Write_Enable(void)
{
  Wait_For_Ready();
  SPI_FLASH_CE_ENABLE;
  SPI_Read_Write(WRITE_ENABLE);
  SPI_FLASH_CE_DISBALE;
  Wait_For_Ready();
}

void SectorErase(uint32_t Addr)
{
  Wait_For_Ready();
  Write_Enable();
  SPI_FLASH_CE_ENABLE;

  SPI_Read_Write(SECTOR_ERASE);

  SPI_Read_Write((Addr & 0xFF000000) >> 24);
  SPI_Read_Write((Addr & 0x00FF0000) >> 16);
  SPI_Read_Write((Addr & 0x0000FF00) >> 8);
  SPI_Read_Write((Addr & 0x000000FF) >> 0);

  SPI_FLASH_CE_DISBALE;
  Wait_For_Ready();
}

uint32_t SPI_Flash_ReadID(void)
{
  uint8_t Temp[3];

  Wait_For_Ready();
  SPI_FLASH_CE_ENABLE;

  SPI_Read_Write(JEDEC_ID);
  Temp[0] = SPI_Read_Write(DUMMY);
  Temp[1] = SPI_Read_Write(DUMMY);
  Temp[2] = SPI_Read_Write(DUMMY);

  SPI_FLASH_CE_DISBALE;
  Wait_For_Ready();

  return Temp[0] << 16 | Temp[1] << 8 | Temp[2];
}

void Read_Buffer(uint32_t Addr, uint8_t *pDate, uint16_t Num)
{
  Wait_For_Ready();
  SPI_FLASH_CE_ENABLE;

  SPI_Read_Write(READ_DATE);
  SPI_Read_Write((Addr & 0xFF000000) >> 24);
  SPI_Read_Write((Addr & 0x00FF0000) >> 16);
  SPI_Read_Write((Addr & 0x0000FF00) >> 8);
  SPI_Read_Write((Addr & 0x000000FF) >> 0);

  while (Num--)
  {
    *(pDate++) = SPI_Read_Write(DUMMY);
  }

  SPI_FLASH_CE_DISBALE;
  Wait_For_Ready();
}

void Write_Page(uint32_t Addr, uint8_t *pDate, uint16_t Num)
{
  Wait_For_Ready();
  Write_Enable();
  SPI_FLASH_CE_ENABLE;

  SPI_Read_Write(PAGE_PROGRAM);
  SPI_Read_Write((Addr & 0xFF000000) >> 24);
  SPI_Read_Write((Addr & 0x00FF0000) >> 16);
  SPI_Read_Write((Addr & 0x0000FF00) >> 8);
  SPI_Read_Write((Addr & 0x000000FF) >> 0);
  while (Num--)
  {
    SPI_Read_Write(*(pDate++));
  }

  SPI_FLASH_CE_DISBALE;
  Wait_For_Ready();
}

void Write_Buffer(uint32_t Addr, uint8_t *pDate, uint16_t Num)
{
  uint8_t Addr_Rem = 0, Num_Page = 0, Num_Single = 0, Align_Left = 0, Align_Right = 0;

  Num_Single = Num % SPI_FLASH_PageSize;      //��ҳд���ʣ�¶��ٸ�
  Num_Page = Num / SPI_FLASH_PageSize;        //������ҳд����ٴ�
  Addr_Rem = Addr % SPI_FLASH_PageSize;       //0 ����ַ���룬��0��û����
  Align_Left = SPI_FLASH_PageSize - Addr_Rem; //��ʼλ�þ�����һ�������ַ�ĸ���
  Align_Right = Num_Single - Align_Left;      //Խ�������ַ��ĸ���

  if (Addr_Rem == 0) //�Ƿ���ҳд��
  {
    if (Num_Page == 0) //�Ƿ���һҳ
    {
      Write_Page(Addr, pDate, Num_Single);
    }
    else
    {
      while (Num_Page--)
      {
        Write_Page(Addr, pDate, SPI_FLASH_PageSize);
        Addr += SPI_FLASH_PageSize;
        pDate += SPI_FLASH_PageSize;
      }
      Write_Page(Addr, pDate, Num_Single);
    }
  }
  else
  {
    if (Num_Page == 0) //�Ƿ���һҳ
    {
      if (Num_Single > Align_Left) //����ʣ�� �Ƿ���� ��ҳʣ��
      {
        Write_Page(Addr, pDate, Align_Left);
        Addr += Align_Left;
        pDate += Align_Left;
        Write_Page(Addr, pDate, Align_Right);
      }
      else
      {
        Write_Page(Addr, pDate, Align_Left);
      }
    }
    else
    {
      Num -= Align_Left;
      Num_Single = Num % SPI_FLASH_PageSize;
      Num_Page = Num / SPI_FLASH_PageSize;

      Write_Page(Addr, pDate, Align_Left);
      Addr += Align_Left;
      pDate += Align_Left;

      while (Num_Page--)
      {
        Write_Page(Addr, pDate, SPI_FLASH_PageSize);
        Addr += SPI_FLASH_PageSize;
        pDate += SPI_FLASH_PageSize;
      }

      if (Num_Single != 0) //����ʣ�࣬����д��
      {
        Write_Page(Addr, pDate, Num_Single);
      }
    }
  }
}
