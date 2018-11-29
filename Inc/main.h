
#ifndef __MAIN_H__
#define __MAIN_H__


/* Choose the output Interface by uncommenting the one you want to use  */

//#define OUTPUT_LCD
#define OUTPUT_UART

/*------------------------Output Interface------------------*/


#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "stm32f4xx_hal.h"

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif 
