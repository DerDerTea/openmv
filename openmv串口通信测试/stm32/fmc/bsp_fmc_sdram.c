#include "./fmc/bsp_fmc_sdram.h"

static void FMC_SDRAM_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*地址信号线*/
    RCC_AHB1PeriphClockCmd(FMC_A0_GPIO_CLK | FMC_A1_GPIO_CLK | FMC_A2_GPIO_CLK |
                               FMC_A3_GPIO_CLK | FMC_A4_GPIO_CLK | FMC_A5_GPIO_CLK |
                               FMC_A6_GPIO_CLK | FMC_A7_GPIO_CLK | FMC_A8_GPIO_CLK |
                               FMC_A9_GPIO_CLK | FMC_A10_GPIO_CLK | FMC_A11_GPIO_CLK |
                               FMC_A12_GPIO_CLK | FMC_BA0_GPIO_CLK | FMC_BA1_GPIO_CLK |
                               /*数据信号线*/
                               FMC_D0_GPIO_CLK | FMC_D1_GPIO_CLK | FMC_D2_GPIO_CLK |
                               FMC_D3_GPIO_CLK | FMC_D4_GPIO_CLK | FMC_D5_GPIO_CLK |
                               FMC_D6_GPIO_CLK | FMC_D7_GPIO_CLK | FMC_D8_GPIO_CLK |
                               FMC_D9_GPIO_CLK | FMC_D10_GPIO_CLK | FMC_D11_GPIO_CLK |
                               FMC_D12_GPIO_CLK | FMC_D13_GPIO_CLK | FMC_D14_GPIO_CLK |
                               FMC_D15_GPIO_CLK |
                               /*控制信号线*/
                               FMC_CS_GPIO_CLK | FMC_WE_GPIO_CLK | FMC_RAS_GPIO_CLK |
                               FMC_CAS_GPIO_CLK | FMC_CLK_GPIO_CLK | FMC_CKE_GPIO_CLK |
                               FMC_UDQM_GPIO_CLK | FMC_LDQM_GPIO_CLK,
                           ENABLE);

    /*-- GPIO 配置 -----------------------------------------------------*/

    /* 通用 GPIO 配置 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //配置为复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

    /*A行列地址信号线 针对引脚配置*/
    GPIO_InitStructure.GPIO_Pin = FMC_A0_GPIO_PIN;
    GPIO_Init(FMC_A0_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A0_GPIO_PORT, FMC_A0_PINSOURCE, FMC_A0_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_A1_GPIO_PIN;
    GPIO_Init(FMC_A1_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A1_GPIO_PORT, FMC_A1_PINSOURCE, FMC_A1_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_A2_GPIO_PIN;
    GPIO_Init(FMC_A2_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A2_GPIO_PORT, FMC_A2_PINSOURCE, FMC_A2_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_A3_GPIO_PIN;
    GPIO_Init(FMC_A3_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A3_GPIO_PORT, FMC_A3_PINSOURCE, FMC_A3_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_A4_GPIO_PIN;
    GPIO_Init(FMC_A4_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A4_GPIO_PORT, FMC_A4_PINSOURCE, FMC_A4_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_A5_GPIO_PIN;
    GPIO_Init(FMC_A5_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A5_GPIO_PORT, FMC_A5_PINSOURCE, FMC_A5_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_A6_GPIO_PIN;
    GPIO_Init(FMC_A6_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A6_GPIO_PORT, FMC_A6_PINSOURCE, FMC_A6_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_A7_GPIO_PIN;
    GPIO_Init(FMC_A7_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A7_GPIO_PORT, FMC_A7_PINSOURCE, FMC_A7_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_A8_GPIO_PIN;
    GPIO_Init(FMC_A8_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A8_GPIO_PORT, FMC_A8_PINSOURCE, FMC_A8_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_A9_GPIO_PIN;
    GPIO_Init(FMC_A9_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A9_GPIO_PORT, FMC_A9_PINSOURCE, FMC_A9_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_A10_GPIO_PIN;
    GPIO_Init(FMC_A10_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A10_GPIO_PORT, FMC_A10_PINSOURCE, FMC_A10_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_A11_GPIO_PIN;
    GPIO_Init(FMC_A11_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A11_GPIO_PORT, FMC_A11_PINSOURCE, FMC_A11_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_A12_GPIO_PIN;
    GPIO_Init(FMC_A12_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_A12_GPIO_PORT, FMC_A12_PINSOURCE, FMC_A12_AF);

    /*BA地址信号线*/
    GPIO_InitStructure.GPIO_Pin = FMC_BA0_GPIO_PIN;
    GPIO_Init(FMC_BA0_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_BA0_GPIO_PORT, FMC_BA0_PINSOURCE, FMC_BA0_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_BA1_GPIO_PIN;
    GPIO_Init(FMC_BA1_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_BA1_GPIO_PORT, FMC_BA1_PINSOURCE, FMC_BA1_AF);

    /*DQ数据信号线 针对引脚配置*/
    GPIO_InitStructure.GPIO_Pin = FMC_D0_GPIO_PIN;
    GPIO_Init(FMC_D0_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D0_GPIO_PORT, FMC_D0_PINSOURCE, FMC_D0_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D1_GPIO_PIN;
    GPIO_Init(FMC_D1_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D1_GPIO_PORT, FMC_D1_PINSOURCE, FMC_D1_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D2_GPIO_PIN;
    GPIO_Init(FMC_D2_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D2_GPIO_PORT, FMC_D2_PINSOURCE, FMC_D2_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D3_GPIO_PIN;
    GPIO_Init(FMC_D3_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D3_GPIO_PORT, FMC_D3_PINSOURCE, FMC_D3_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D4_GPIO_PIN;
    GPIO_Init(FMC_D4_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D4_GPIO_PORT, FMC_D4_PINSOURCE, FMC_D4_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D5_GPIO_PIN;
    GPIO_Init(FMC_D5_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D5_GPIO_PORT, FMC_D5_PINSOURCE, FMC_D5_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D6_GPIO_PIN;
    GPIO_Init(FMC_D6_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D6_GPIO_PORT, FMC_D6_PINSOURCE, FMC_D6_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D7_GPIO_PIN;
    GPIO_Init(FMC_D7_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D7_GPIO_PORT, FMC_D7_PINSOURCE, FMC_D7_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D8_GPIO_PIN;
    GPIO_Init(FMC_D8_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D8_GPIO_PORT, FMC_D8_PINSOURCE, FMC_D8_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D9_GPIO_PIN;
    GPIO_Init(FMC_D9_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D9_GPIO_PORT, FMC_D9_PINSOURCE, FMC_D9_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D10_GPIO_PIN;
    GPIO_Init(FMC_D10_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D10_GPIO_PORT, FMC_D10_PINSOURCE, FMC_D10_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D11_GPIO_PIN;
    GPIO_Init(FMC_D11_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D11_GPIO_PORT, FMC_D11_PINSOURCE, FMC_D11_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D12_GPIO_PIN;
    GPIO_Init(FMC_D12_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D12_GPIO_PORT, FMC_D12_PINSOURCE, FMC_D12_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D13_GPIO_PIN;
    GPIO_Init(FMC_D13_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D13_GPIO_PORT, FMC_D13_PINSOURCE, FMC_D13_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D14_GPIO_PIN;
    GPIO_Init(FMC_D14_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D14_GPIO_PORT, FMC_D14_PINSOURCE, FMC_D14_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_D15_GPIO_PIN;
    GPIO_Init(FMC_D15_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_D15_GPIO_PORT, FMC_D15_PINSOURCE, FMC_D15_AF);

    /*控制信号线*/
    GPIO_InitStructure.GPIO_Pin = FMC_CS_GPIO_PIN;
    GPIO_Init(FMC_CS_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_CS_GPIO_PORT, FMC_CS_PINSOURCE, FMC_CS_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_WE_GPIO_PIN;
    GPIO_Init(FMC_WE_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_WE_GPIO_PORT, FMC_WE_PINSOURCE, FMC_WE_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_RAS_GPIO_PIN;
    GPIO_Init(FMC_RAS_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_RAS_GPIO_PORT, FMC_RAS_PINSOURCE, FMC_RAS_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_CAS_GPIO_PIN;
    GPIO_Init(FMC_CAS_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_CAS_GPIO_PORT, FMC_CAS_PINSOURCE, FMC_CAS_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_CLK_GPIO_PIN;
    GPIO_Init(FMC_CLK_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_CLK_GPIO_PORT, FMC_CLK_PINSOURCE, FMC_CLK_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_CKE_GPIO_PIN;
    GPIO_Init(FMC_CKE_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_CKE_GPIO_PORT, FMC_CKE_PINSOURCE, FMC_CKE_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_UDQM_GPIO_PIN;
    GPIO_Init(FMC_UDQM_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_UDQM_GPIO_PORT, FMC_UDQM_PINSOURCE, FMC_UDQM_AF);

    GPIO_InitStructure.GPIO_Pin = FMC_LDQM_GPIO_PIN;
    GPIO_Init(FMC_LDQM_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(FMC_LDQM_GPIO_PORT, FMC_LDQM_PINSOURCE, FMC_LDQM_AF);
}

static void FMC_SDRAM_Config(void)
{
    FMC_SDRAMTimingInitTypeDef FMC_SDRAMTimingInitStructure;
    FMC_SDRAMInitTypeDef FMC_SDRAMInitStruct;

    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE);

    /* SDRAM时序结构体，根据SDRAM参数表配置----------------*/
    /* SDCLK： 90 Mhz (HCLK/2 :180Mhz/2) 1个时钟周期Tsdclk =1/90MHz=11.11ns*/
    /* TXSR: min=70ns (7x11.11ns) */
    FMC_SDRAMTimingInitStructure.FMC_ExitSelfRefreshDelay = 7;
    /* TMRD: 2 Clock cycles */
    FMC_SDRAMTimingInitStructure.FMC_LoadToActiveDelay = 2;
    /* TRCD: 15ns => 2x11.11ns */
    FMC_SDRAMTimingInitStructure.FMC_RCDDelay = 2;
    /* TRC:  min=60 (6x11.11ns) */
    FMC_SDRAMTimingInitStructure.FMC_RowCycleDelay = 6;
    /* TRP:  15ns => 2x11.11ns */
    FMC_SDRAMTimingInitStructure.FMC_RPDelay = 2;
    /* TRAS: min=42ns (4x11.11ns) max=120k (ns) */
    FMC_SDRAMTimingInitStructure.FMC_SelfRefreshTime = 4;
    /* TWR: 2 Clock cycles */
    FMC_SDRAMTimingInitStructure.FMC_WriteRecoveryTime = 2;

    /* FMC SDRAM 控制配置 */
    /*选择存储区域*/
    FMC_SDRAMInitStruct.FMC_Bank = FMC_Bank2_SDRAM;
    /* CAS潜伏期 */
    FMC_SDRAMInitStruct.FMC_CASLatency = FMC_CAS_Latency_2;
    /* 行地址线宽度: [8:0] */
    FMC_SDRAMInitStruct.FMC_ColumnBitsNumber = FMC_ColumnBits_Number_9b;
    /* SDRAM内部bank数量*/
    FMC_SDRAMInitStruct.FMC_InternalBankNumber = FMC_InternalBank_Number_4;
    /* 突发读模式设置*/
    FMC_SDRAMInitStruct.FMC_ReadBurst = FMC_Read_Burst_Enable;
    /* 读延迟配置 */
    FMC_SDRAMInitStruct.FMC_ReadPipeDelay = FMC_ReadPipe_Delay_0;
    /* 列地址线宽度: [12:0] */
    FMC_SDRAMInitStruct.FMC_RowBitsNumber = FMC_RowBits_Number_13b;
    /* SDCLK时钟分频因子，SDCLK = HCLK/SDCLOCK_PERIOD*/
    FMC_SDRAMInitStruct.FMC_SDClockPeriod = FMC_SDClock_Period_2;
    /* 数据线宽度 */
    FMC_SDRAMInitStruct.FMC_SDMemoryDataWidth = FMC_SDMemory_Width_16b;
    /* SDRAM时序参数 */
    FMC_SDRAMInitStruct.FMC_SDRAMTimingStruct = &FMC_SDRAMTimingInitStructure;
    /* 禁止写保护*/
    FMC_SDRAMInitStruct.FMC_WriteProtection = FMC_Write_Protection_Disable;

    FMC_SDRAMInit(&FMC_SDRAMInitStruct);
}

static void FMC_SDRAM_InitSequence(void)
{
    FMC_SDRAMCommandTypeDef FMC_SDRAMCommandStruct;
    uint32_t tmpr = 0;

    /* 配置命令：开启提供给SDRAM的时钟 */
    FMC_SDRAMCommandStruct.FMC_CommandMode = FMC_Command_Mode_CLK_Enabled;
    FMC_SDRAMCommandStruct.FMC_CommandTarget = FMC_Command_Target_bank2;
    FMC_SDRAMCommandStruct.FMC_AutoRefreshNumber = 0;
    FMC_SDRAMCommandStruct.FMC_ModeRegisterDefinition = 0;
    while (FMC_GetFlagStatus(FMC_Bank2_SDRAM, FMC_FLAG_Busy) != RESET)
        ;
    FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStruct);

    /* 延时 */
    for (uint32_t i = 0xFFFFF; i > 0; i--)
        ;

    /* 配置命令：对所有的bank预充电 */
    FMC_SDRAMCommandStruct.FMC_CommandMode = FMC_Command_Mode_PALL;
    FMC_SDRAMCommandStruct.FMC_CommandTarget = FMC_Command_Target_bank2;
    FMC_SDRAMCommandStruct.FMC_AutoRefreshNumber = 0;
    FMC_SDRAMCommandStruct.FMC_ModeRegisterDefinition = 0;
    while (FMC_GetFlagStatus(FMC_Bank2_SDRAM, FMC_FLAG_Busy) != RESET)
        ;
    FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStruct);

    /* 配置命令：自动刷新 */
    FMC_SDRAMCommandStruct.FMC_CommandMode = FMC_Command_Mode_AutoRefresh;
    FMC_SDRAMCommandStruct.FMC_CommandTarget = FMC_Command_Target_bank2;
    FMC_SDRAMCommandStruct.FMC_AutoRefreshNumber = 2;
    FMC_SDRAMCommandStruct.FMC_ModeRegisterDefinition = 0;
    while (FMC_GetFlagStatus(FMC_Bank2_SDRAM, FMC_FLAG_Busy) != RESET)
        ;
    FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStruct);

    /* 设置sdram寄存器配置 */
    tmpr = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_4 |
           SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
           SDRAM_MODEREG_CAS_LATENCY_2 |
           SDRAM_MODEREG_OPERATING_MODE_STANDARD |
           SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;
    /* 配置命令：设置SDRAM寄存器 */
    FMC_SDRAMCommandStruct.FMC_CommandMode = FMC_Command_Mode_LoadMode;
    FMC_SDRAMCommandStruct.FMC_CommandTarget = FMC_Command_Target_bank2;
    FMC_SDRAMCommandStruct.FMC_AutoRefreshNumber = 1;
    FMC_SDRAMCommandStruct.FMC_ModeRegisterDefinition = tmpr;
    while (FMC_GetFlagStatus(FMC_Bank2_SDRAM, FMC_FLAG_Busy) != RESET)
        ;
    FMC_SDRAMCmdConfig(&FMC_SDRAMCommandStruct);

    /* 设置刷新计数器 */
    /*刷新速率 = (COUNT + 1) x SDRAM 频率时钟
    COUNT =（ SDRAM 刷新周期/行数) - 20*/
    /* 64ms/8192=7.813us  (7.813 us x FSDCLK) - 20 =683 */
    FMC_SetRefreshCount(683);
    while (FMC_GetFlagStatus(FMC_Bank2_SDRAM, FMC_FLAG_Busy) != RESET)
        ;
}

void FMC_SDRAM_Init(void)
{
    FMC_SDRAM_GPIO_Config();
    FMC_SDRAM_Config();
    FMC_SDRAM_InitSequence();
}
