#include "stm32f4xx.h"
#include "./usart/bsp_usart.h"
#include "./led/bsp_led.h"
#include "./lcd/bsp_lcd.h"
#include "./lcd/bsp_touch.h"
#include "./spi/bsp_spi.h"
#include "./fmc/bsp_fmc_sdram.h"


extern char string[16];
int32_t Temp[4] = {0};
extern uint8_t stat_bit;

int main(void)
{
	USART1_init();
	USART2_init();
	LED_Config();
	SPIx_Init();
	FMC_SDRAM_Init();
	LCD_Init();
	I2C_Touch_Init();

	LCD_DrawRect(50,50,320,240,LCD_TOP_START_ADDR,0xFFFF0000);
	LCD_DrawFullCircle(550, 150, 50, LCD_GROUND_START_ADDR, 0xFF00FFFF);
	LCD_DrawCircle(550, 150, 51, LCD_GROUND_START_ADDR, 0xFF000000);
	LCD_DispString_CH(526,138,LCD_TOP_START_ADDR,0xFF000000,0x00000000,"清空");
	LCD_DrawFullCircle(550, 300, 50, LCD_GROUND_START_ADDR, 0xFF00FFFF);
	LCD_DrawCircle(550, 300, 51, LCD_GROUND_START_ADDR, 0xFF000000);
	LCD_DispString_CH(526,288,LCD_TOP_START_ADDR,0xFF000000,0x00000000,"连续");
	LCD_DispString_CH(200,400,LCD_TOP_START_ADDR,0xFF000000,0x00000000,"串口通信测试");

	
	while(1)
	{
//		char value[20];
		OpenMV_Date(string, "[", ",",&Temp[0]);
		OpenMV_Date(string, ",", "]",&Temp[1]);
		if(Temp[0] < 0 | Temp[1] < 0 | Temp[0] > 320 | Temp[1] > 240 )
		{
			Temp[0] = 999;
			Temp[1] = 999;
		}

//		sprintf(value, "%d + %d = %d",Temp[0], Temp[1], Temp[0] + Temp[1]);	
		LCD_DispString_EN_CH(50,300,LCD_TOP_START_ADDR,0xFFFF0000,0x00000000,string);
//		LCD_DispString_EN_CH(50,360,LCD_TOP_START_ADDR,0xFFFF0000,0x00000000,value);
		
		LCD_DrawFullCircle(Temp[0] + 50, Temp[1] + 50, 2, LCD_TOP_START_ADDR, 0xFFFF0000);
		if(stat_bit)
		{
			LCD_DrawFullCircle(Temp[2] + 50, Temp[3] + 50, 2, LCD_TOP_START_ADDR, 0x00000000);
		}
		
		LCD_DrawRect(50,50,320,240,LCD_TOP_START_ADDR,0xFFFF0000);
		Temp[2] = Temp[0];
		Temp[3] = Temp[1];
	}
}

