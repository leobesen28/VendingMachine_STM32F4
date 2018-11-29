/*

-----------------------------------------------------
|		FEDERAL UNIVERSITY OF SANTA CATARINA		|
|			C++ FOR EMBEDDED SYSTEMS				|
|			PROJECT: VENDING MACHINE				|
|		PROFESSOR: EDUARDO AUGUSTO BEZERRA			|
| 	 	 	 LEONARDO AURÉLIO BESEN					|
|			JOÃO BATISTA CORDEIRO NETO				|
----------------------------------------------------- 

*/


/*
		--- ATENTION ---

InputInterface class is not being used in this project because it has only one input - GPIO ports

We did not deleted this class from the project because when we do it, it causes an hard fault error on the board processor.


*/

#ifndef INPUT_H
	#define INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#ifdef __cplusplus
}
#endif

class InputInterface {
	public:
		virtual uint8_t inputButton(char) = 0;
		virtual uint8_t inputAd(void) = 0;
};


class InputInterfaceARM : public InputInterface{

	public:
		uint8_t inputButton(char);
		uint8_t inputAd(void);
	
};


#endif
