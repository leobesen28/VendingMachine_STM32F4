#ifndef CLASSES_ARM_H
	#define CLASSES_ARM_H

#include "main.h"




//GPIO class
class LB_GPIO {
	
	GPIO_InitTypeDef GPIO_InitStruct;
	public:
		LB_GPIO(void);
		void initGPIO(void);
};
// System Clock class
class LB_SystemClock{
	
	RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
	public:
		LB_SystemClock(void);
		void systemClockConfig(void);
};
// HALL class
class LB_Hall {
	public:
		LB_Hall(void);
		HAL_StatusTypeDef hallInit(void);
};



#endif /* __CLASS_GPIO_H__ */
