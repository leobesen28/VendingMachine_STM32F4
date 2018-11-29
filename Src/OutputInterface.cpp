#include "OutputInterface.h"


LB_Lcd::LB_Lcd(void){
	
	BSP_LCD_Init(); //init LCD
	BSP_LCD_LayerDefaultInit(1, SDRAM_DEVICE_ADDR); //set the layer buffer address into SDRAM
	BSP_LCD_SelectLayer(1); //select on which layer we write
	BSP_LCD_DisplayOn(); //turn on LCD
	BSP_LCD_Clear(LCD_COLOR_BLACK); //clear the LCD on blue color
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK); //set text background color
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE); //set text color
	

	clearLCD(0);
	uint8_t text1[] = "   Vending Machine  ";
	BSP_LCD_DisplayStringAtLine(0, text1);
	uint8_t text2[] = "         C++        ";
	BSP_LCD_DisplayStringAtLine(1, text2);
	uint8_t text3[] = "   Embedded Systems  ";
	BSP_LCD_DisplayStringAtLine(2, text3);
	BSP_LCD_SetTextColor(LCD_COLOR_LIGHTBLUE); //set text color
	uint8_t text4[] = "    Leonardo Besen  ";
	BSP_LCD_DisplayStringAtLine(3, text4);
	uint8_t text5[] = "     Joao Batista   ";
	BSP_LCD_DisplayStringAtLine(4, text5);
	BSP_LCD_DrawRect(10, 0, 220, 77);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE); //set text color

	
}
//Clear the LCD starting from Line especified
void LB_Lcd::clearLCD(uint16_t Line){
		for(uint16_t i = Line; i < 20; i++)
			BSP_LCD_ClearStringLine(i);
}

void LB_Lcd::printToUser(uint16_t Line, uint8_t *ptr, uint16_t size){
	//Send message to the LCD
	BSP_LCD_DisplayStringAtLine(Line, ptr);
}

void LB_Uart::printToUser(uint16_t Line, uint8_t *ptr, uint16_t size){
	//Send message to the UART Tx port
	HAL_UART_Transmit(&huart4, ptr, size, 500);

}
