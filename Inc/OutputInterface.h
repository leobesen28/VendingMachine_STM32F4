#ifndef OUTPUT_H
	#define OUTPUT_H
	


#include "main.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f429i_discovery_lcd.h"

#ifdef __cplusplus
}
#endif

extern UART_HandleTypeDef huart4;

//Abstract class for output interface
class OutputInterface{
	public:
		virtual void printToUser(uint16_t Line, uint8_t *ptr, uint16_t size) = 0;
		virtual void clearLCD(uint16_t Line) = 0;
};

//LCD class
class LB_Lcd : public OutputInterface {
	public:
		LB_Lcd(void);
		void printToUser(uint16_t Line, uint8_t *ptr, uint16_t size);
		void clearLCD(uint16_t Line);
};
//UART class
class LB_Uart : public OutputInterface {
	public:
		LB_Uart(void){}
		void printToUser(uint16_t Line, uint8_t *ptr, uint16_t size);
		void clearLCD(uint16_t Line){}
};

#endif

