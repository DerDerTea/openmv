#include "./lcd/bsp_touch.h"
#include "./usart/bsp_usart.h"
#include "./lcd/bsp_lcd.h"

#if TOUCH_HARD_IIC

/* 触控芯片引脚配置 */
static void GT91x_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    I2C_InitTypeDef I2C_InitStruct;

    RCC_AHB1PeriphClockCmd(I2C_TOUCH_GPIO_CLK | GTP_RST_GPIO_CLK | GTP_INT_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(I2C_TOUCH_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;

    GPIO_PinAFConfig(I2C_TOUCH_SCL_GPIO_PORT, I2C_TOUCH_SCL_GPIO_SOURCE, I2C_TOUCH_GPIO_AF);
    GPIO_InitStruct.GPIO_Pin = I2C_TOUCH_SCL_GPIO_PIN;
    GPIO_Init(I2C_TOUCH_SCL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_PinAFConfig(I2C_TOUCH_SDA_GPIO_PORT, I2C_TOUCH_SDA_GPIO_SOURCE, I2C_TOUCH_GPIO_AF);
    GPIO_InitStruct.GPIO_Pin = I2C_TOUCH_SDA_GPIO_PIN;
    GPIO_Init(I2C_TOUCH_SDA_GPIO_PORT, &GPIO_InitStruct);

    /*!< Configure RST */
    GPIO_InitStruct.GPIO_Pin = GTP_RST_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GTP_RST_GPIO_PORT, &GPIO_InitStruct);

    /*!< Configure INT */
    GPIO_InitStruct.GPIO_Pin = GTP_INT_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN; //设置为下拉，方便初始化
    GPIO_Init(GTP_INT_GPIO_PORT, &GPIO_InitStruct);

    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStruct.I2C_ClockSpeed = I2C_TOUCH_SPEED;
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_OwnAddress1 = I2C_TOUCH_OWNADDR;
    I2C_Init(I2CX_TOUCH, &I2C_InitStruct);

    I2C_Cmd(I2CX_TOUCH, ENABLE);
    I2C_AcknowledgeConfig(I2CX_TOUCH, ENABLE);
}

/**
  * @brief  触控芯片写操作
  * @param  Writeaddr: 寄存器地址
  * @param  *pDate: 数据的指针
  * @param  Num: 字节数
  * @retval None
  */
static void I2C_Touch_WriteBuffer(uint16_t Writeaddr, uint8_t *pDate, uint16_t Num)
{
    I2C_GenerateSTART(I2CX_TOUCH, ENABLE);
    while (!I2C_CheckEvent(I2CX_TOUCH, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2CX_TOUCH, GTP_ADDRESS, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2CX_TOUCH, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;
    I2C_SendData(I2CX_TOUCH, (Writeaddr & 0xFF00) >> 8);
    while (!I2C_CheckEvent(I2CX_TOUCH, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    I2C_SendData(I2CX_TOUCH, Writeaddr & 0xFF);
    while (!I2C_CheckEvent(I2CX_TOUCH, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    while (Num--)
    {
        I2C_SendData(I2CX_TOUCH, *(pDate++));
        while (!I2C_CheckEvent(I2CX_TOUCH, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
            ;
    }
    I2C_GenerateSTOP(I2CX_TOUCH, ENABLE);
}

/**
  * @brief  触控芯片读操作
  * @param  Readaddr: 寄存器地址
  * @param  *pDate: 数据的指针
  * @param  Num: 字节数
  * @retval None
  */
static void I2C_Touch_ReadBuffer(uint16_t Readaddr, uint8_t *pDate, uint16_t Num)
{
    I2C_GenerateSTART(I2CX_TOUCH, ENABLE);
    while (!I2C_CheckEvent(I2CX_TOUCH, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2CX_TOUCH, GTP_ADDRESS, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2CX_TOUCH, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;
    I2C_SendData(I2CX_TOUCH, (Readaddr & 0xFF00) >> 8);
    while (!I2C_CheckEvent(I2CX_TOUCH, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    I2C_SendData(I2CX_TOUCH, Readaddr & 0xFF);
    while (!I2C_CheckEvent(I2CX_TOUCH, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    I2C_GenerateSTART(I2CX_TOUCH, ENABLE);
    while (!I2C_CheckEvent(I2CX_TOUCH, I2C_EVENT_MASTER_MODE_SELECT))
        ;
    I2C_Send7bitAddress(I2CX_TOUCH, GTP_ADDRESS, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2CX_TOUCH, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
        ;
    I2C_AcknowledgeConfig(I2CX_TOUCH, ENABLE);
    while (Num--)
    {
        while (!I2C_CheckEvent(I2CX_TOUCH, I2C_EVENT_MASTER_BYTE_RECEIVED))
            ;
        *(pDate++) = I2C_ReceiveData(I2CX_TOUCH);
        if (Num == 0)
        {
            I2C_AcknowledgeConfig(I2CX_TOUCH, DISABLE);
        }
        else
        {
            I2C_AcknowledgeConfig(I2CX_TOUCH, ENABLE);
        }
    }
    I2C_GenerateSTOP(I2CX_TOUCH, ENABLE);
}

#else

/* 触控芯片引脚配置 */
static void GT91x_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(I2C_TOUCH_GPIO_CLK | GTP_RST_GPIO_CLK | GTP_INT_GPIO_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;

    GPIO_InitStruct.GPIO_Pin = I2C_TOUCH_SCL_GPIO_PIN;
    GPIO_Init(I2C_TOUCH_SCL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = I2C_TOUCH_SDA_GPIO_PIN;
    GPIO_Init(I2C_TOUCH_SDA_GPIO_PORT, &GPIO_InitStruct);

    /*!< Configure RST */
    GPIO_InitStruct.GPIO_Pin = GTP_RST_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(GTP_RST_GPIO_PORT, &GPIO_InitStruct);

    /*!< Configure INT */
    GPIO_InitStruct.GPIO_Pin = GTP_INT_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN; //设置为下拉，方便初始化
    GPIO_Init(GTP_INT_GPIO_PORT, &GPIO_InitStruct);
}

/*　
CPU主频180MHz ，MDK编译环境，1级优化
循环次数为50时，SCL频率 = 333KHz 
循环次数为30时，SCL频率 = 533KHz，  
循环次数为20时，SCL频率 = 727KHz， 
*/
static void I2C_TOUCH_Delay(void)
{
    for (uint8_t i = 0; i < 50; i++)
        ;
}

/* I2C起始信号 */
static void I2C_TOUCH_Start(void)
{
    IIC_TOUCH_SDA_HIGH;
    IIC_TOUCH_SCL_HIGH;
    I2C_TOUCH_Delay();
    IIC_TOUCH_SDA_LOW;
    I2C_TOUCH_Delay();
    IIC_TOUCH_SCL_LOW;
    I2C_TOUCH_Delay();
}

/* I2C停止信号 */
static void I2C_TOUCH_Stop(void)
{
    IIC_TOUCH_SDA_LOW;
    IIC_TOUCH_SCL_HIGH;
    I2C_TOUCH_Delay();
    IIC_TOUCH_SDA_HIGH;
}

/* I2C发送一个字节 */
static void Send_Byte_TOUCH(uint8_t Value)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        if (Value & 0x80)
        {
            IIC_TOUCH_SDA_HIGH;
        }
        else
        {
            IIC_TOUCH_SDA_LOW;
        }
        I2C_TOUCH_Delay();
        IIC_TOUCH_SCL_HIGH;
        I2C_TOUCH_Delay();
        IIC_TOUCH_SCL_LOW;
        I2C_TOUCH_Delay();
        if (i == 7)
        {
            IIC_TOUCH_SDA_HIGH;
        }
        Value <<= 1;
        I2C_TOUCH_Delay();
    }
}

/* I2C接收一个字节 */
static uint8_t Receive_Byte_TOUCH(void)
{
    uint8_t Value = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        Value <<= 1;
        IIC_TOUCH_SCL_HIGH;
        I2C_TOUCH_Delay();
        if (IIC_TOUCH_SDA_READ)
        {
            Value++;
        }
        IIC_TOUCH_SCL_LOW;
        I2C_TOUCH_Delay();
    }
    return Value;
}

/* I2C等待响应 */
static void I2C_TOUCH_Wait_Ack(void)
{

    IIC_TOUCH_SDA_HIGH;
    I2C_TOUCH_Delay();
    IIC_TOUCH_SCL_HIGH;
    I2C_TOUCH_Delay();
    while (IIC_TOUCH_SDA_READ)
        ;
    IIC_TOUCH_SCL_LOW;
    I2C_TOUCH_Delay();
}

/* I2C响应信号 */
static void I2C_TOUCH_Ack(void)
{
    IIC_TOUCH_SDA_LOW;
    I2C_TOUCH_Delay();
    IIC_TOUCH_SCL_HIGH;
    I2C_TOUCH_Delay();
    IIC_TOUCH_SCL_LOW;
    I2C_TOUCH_Delay();
    IIC_TOUCH_SDA_HIGH;
}

/* I2C非响应信号 */
static void I2C_TOUCH_NoAck(void)
{
    IIC_TOUCH_SDA_HIGH;
    I2C_TOUCH_Delay();
    IIC_TOUCH_SCL_HIGH;
    I2C_TOUCH_Delay();
    IIC_TOUCH_SCL_LOW;
    I2C_TOUCH_Delay();
}

/**
  * @brief  触控芯片写操作
  * @param  Writeaddr: 寄存器地址
  * @param  *pDate: 数据的指针
  * @param  Num: 字节数
  * @retval None
  */
static void I2C_Touch_WriteBuffer(uint16_t Writeaddr, uint8_t *pDate, uint16_t Num)
{
    I2C_TOUCH_Start();
    Send_Byte_TOUCH(GTP_ADDRESS | IIC_TOUCH_WRITE_DIRECTION);
    I2C_TOUCH_Wait_Ack();
    Send_Byte_TOUCH(Writeaddr >> 8);
    I2C_TOUCH_Wait_Ack();
    Send_Byte_TOUCH(Writeaddr);
    I2C_TOUCH_Wait_Ack();
    while (Num--)
    {
        Send_Byte_TOUCH(*(pDate++));
        if (Num == 0)
        {
            I2C_TOUCH_NoAck();
        }
        else
        {
            I2C_TOUCH_Ack();
        }
    }
    I2C_TOUCH_Stop();
}

/**
  * @brief  触控芯片读操作
  * @param  Readaddr: 寄存器地址
  * @param  *pDate: 数据的指针
  * @param  Num: 字节数
  * @retval None
  */
static void I2C_Touch_ReadBuffer(uint16_t Readaddr, uint8_t *pDate, uint16_t Num)
{
    I2C_TOUCH_Start();
    Send_Byte_TOUCH(GTP_ADDRESS | IIC_TOUCH_WRITE_DIRECTION);
    I2C_TOUCH_Wait_Ack();
    Send_Byte_TOUCH(Readaddr >> 8);
    I2C_TOUCH_Wait_Ack();
    Send_Byte_TOUCH(Readaddr);
    I2C_TOUCH_Wait_Ack();
    I2C_TOUCH_Start();
    Send_Byte_TOUCH(GTP_ADDRESS | IIC_TOUCH_READ_DIRECTION);
    I2C_TOUCH_Wait_Ack();
    while (Num--)
    {
        *(pDate++) = Receive_Byte_TOUCH();
        if (Num == 0)
        {
            I2C_TOUCH_NoAck();
        }
        else
        {
            I2C_TOUCH_Ack();
        }
    }
    I2C_TOUCH_Stop();
}

#endif

/* 简单的延时函数 */
static void Touch_Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--)
        ;
}

/* 配置芯片I2C地址 */
static void GT91x_Reset(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< Configure INT */
    GPIO_InitStructure.GPIO_Pin = GTP_INT_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //设置为下拉，方便初始化
    GPIO_Init(GTP_INT_GPIO_PORT, &GPIO_InitStructure);

    /*初始化GT91x,rst为高电平，int为低电平，则gt91x的设备地址被配置为0xBA*/

    /*复位为低电平，为初始化做准备*/
    GPIO_ResetBits(GTP_RST_GPIO_PORT, GTP_RST_GPIO_PIN);
    Touch_Delay(0x0FFFFF);

    /*拉高一段时间，进行初始化*/
    GPIO_SetBits(GTP_RST_GPIO_PORT, GTP_RST_GPIO_PIN);
    Touch_Delay(0x0FFFFF);

    /*把INT引脚设置为浮空输入模式*/
    /*!< Configure INT */
    GPIO_InitStructure.GPIO_Pin = GTP_INT_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GTP_INT_GPIO_PORT, &GPIO_InitStructure);
}

/* 配置芯片EXTI中断 */
static void I2C_GTP_IRQEnable(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    /*配置 INT 为浮空输入 */
    GPIO_InitStructure.GPIO_Pin = GTP_INT_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GTP_INT_GPIO_PORT, &GPIO_InitStructure);

    /* 连接 EXTI 中断源 到INT 引脚 */
    SYSCFG_EXTILineConfig(GTP_INT_EXTI_PORTSOURCE, GTP_INT_EXTI_PINSOURCE);

    /* 选择 EXTI 中断源 */
    EXTI_InitStructure.EXTI_Line = GTP_INT_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    /*使能中断*/
    NVIC_InitStructure.NVIC_IRQChannel = GTP_INT_EXTI_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/* 获取芯片型号 */
static void GT91x_ProductID(void)
{
    uint8_t Value[4] = {0};
    I2C_Touch_ReadBuffer(GTP_PRODUCTID, Value, 4);
    printf("GT91x Product ID : %c%c%c%c\n\n", Value[0], Value[1], Value[2], Value[3]);
}

/* I2C触控芯片初始化 */
void I2C_Touch_Init(void)
{
    GT91x_GPIO_Config();
    GT91x_Reset();
    I2C_GTP_IRQEnable();
    GT91x_ProductID();
}

/* 按键按下执行函数 */
void GT91x_Touch_Down(uint8_t TrackID, int16_t PointX, int16_t PointY, int16_t PointS)
{
	if ((PointX < 600) && (PointX > 500) && (PointY < 200) && (PointY > 100))
	{
		LCD_DrawFullCircle(550, 150, 50, LCD_GROUND_START_ADDR, 0xFFFFFFFF);
	}

	if ((PointX < 600) && (PointX > 500) && (PointY < 350) && (PointY > 250))
	{
		LCD_DrawFullCircle(550, 300, 50, LCD_GROUND_START_ADDR, 0xFFFFFFFF);
	}
    //printf("\r\nTrackID = %d PointX = %d PointY = %d PointS = %d\r\n", TrackID, PointX, PointY, PointS);
}

//extern char string[16];

/* 按键释放执行函数 */
uint8_t stat_bit = 0;
void GT91x_Touch_UP(uint8_t TrackID, int16_t PointX, int16_t PointY, int16_t PointS)
{
	if ((PointX < 600) && (PointX > 500) && (PointY < 200) && (PointY > 100))
	{
		LCD_DrawFullCircle(550, 150, 50, LCD_GROUND_START_ADDR, 0xFF00FFFF);
		LCD_DrawFullRect(50,50,320,240,LCD_TOP_START_ADDR,0x00000000);
	}

	if ((PointX < 600) && (PointX > 500) && (PointY < 350) && (PointY > 250))
	{
		stat_bit = ~stat_bit;
		if(stat_bit)
		{
			LCD_DispString_CH(526,288,LCD_TOP_START_ADDR,0xFF000000,0x00000000,"单点");
			LCD_DrawFullCircle(550, 300, 50, LCD_GROUND_START_ADDR, 0xFFFF00FF);
		}
		else
		{
			LCD_DispString_CH(526,288,LCD_TOP_START_ADDR,0xFF000000,0x00000000,"连续");
			LCD_DrawFullCircle(550, 300, 50, LCD_GROUND_START_ADDR, 0xFF00FFFF);
		}
	}
    //printf("\r\nUP TrackID = %d PointX = %d PointY = %d PointS = %d\r\n", TrackID, PointX, PointY, PointS);
}

TOUCH_POINT Old_Touch_Pount[GTP_MAX_TOUCH];
uint8_t TrackID[GTP_MAX_TOUCH];
int8_t Old_Number_Points = 0;
/* 获取触控坐标 */
void GT91x_Touch_Get(void)
{
    uint8_t Res = 0x00;
    uint8_t State;
    uint8_t Value[GTP_MAX_TOUCH * 8] = {0};
    uint8_t Buffer_Status = 0;
    int8_t Now_Number_Points = 0;

    int16_t PointX;
    int16_t PointY;
    int16_t PointS;

    I2C_Touch_ReadBuffer(GTP_STATE, &State, 1);
    Buffer_Status = State & 0x80;
    Now_Number_Points = State & 0x0f;

    /* 判断是否有可读数据 */
    if (Buffer_Status == 0 || Now_Number_Points > GTP_MAX_TOUCH)
    {
        I2C_Touch_WriteBuffer(GTP_STATE, &Res, 1);
        return;
    }

    /* 读取寄存器并处理 */
    if (Now_Number_Points > 0)
    {
        I2C_Touch_ReadBuffer(GTP_POINT, Value, Now_Number_Points * 8);
        for (uint8_t i = 0; i < Now_Number_Points; i++)
        {
            PointX = Value[i * 8] | (Value[i * 8 + 1] << 8);
            PointY = Value[i * 8 + 2] | (Value[i * 8 + 3] << 8);
            PointS = Value[i * 8 + 4] | (Value[i * 8 + 5] << 8);
            TrackID[i] = Value[i * 8 + 7];
            GT91x_Touch_Down(TrackID[i], PointX, PointY, PointS);
        }
    }

    /* 检查按键释放 */
    if (Old_Number_Points > Now_Number_Points)
    {
        if (Old_Number_Points == 1)
        {
            GT91x_Touch_UP(Old_Touch_Pount[0].TrackID, Old_Touch_Pount[0].PointX, Old_Touch_Pount[0].PointY, Old_Touch_Pount[0].PointS);
        }
        else
        {
            int8_t Temp = 0;
            Temp = Old_Number_Points - Now_Number_Points;
            GT91x_Touch_UP(Old_Touch_Pount[Temp].TrackID, Old_Touch_Pount[Temp].PointX, Old_Touch_Pount[Temp].PointY, Old_Touch_Pount[Temp].PointS);
        }
    }

    /* 记录过去数据 */
    for (uint8_t i = 0; i < Now_Number_Points; i++)
    {
        Old_Touch_Pount[i].PointX = PointX;
        Old_Touch_Pount[i].PointY = PointY;
        Old_Touch_Pount[i].PointS = PointS;
        Old_Touch_Pount[i].TrackID = TrackID[i];
    }
    Old_Number_Points = Now_Number_Points;
    I2C_Touch_WriteBuffer(GTP_STATE, &Res, 1);
}


