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

#include "Logs.h"

/*
When creating a new log, you must choose the value 'p' to indicate which of the products were sold
p = 0x00 -> MEET sold
p = 0x01 -> ETIRPS sold
*/

Logs::Logs(void) : ClockCalendar(){

   		meet = false;
   		etirps = false;
}

Logs::~Logs(){}

void Logs::setLog(char p){
	   if(p == 0x00){
	   		meet = true;
	   		etirps = false;
	   }else if(p == 0x01){
  	        meet = false;
	   		etirps = true;
	   }
}

/*
To get the log info about what product was sold 
*/
char Logs::getLog(void){
	if(meet == true)
		return 'M';
	else
		return 'E';
}
