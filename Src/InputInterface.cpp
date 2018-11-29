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

#include "InputInterface.h"

/*
			--- ATENTION ---
			
InputInterface class is not being used in this project because it has only one input - GPIO ports

We did not deleted this class from the project because when we do it, it causes an hard fault error on the board processor.


*/


/*
sel = 0x00 -> read quantity
sel = 0x01 -> YES/NO
*/

uint8_t InputInterfaceARM::inputButton(char sel){
	return 0x00;
} 
uint8_t InputInterfaceARM::inputAd(void){
	return 0x00;
}

