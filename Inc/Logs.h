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

#ifndef LOGS_H
	#define LOGS_H

#include "ClockCalendar.h"
#include <string.h>

//Logs of the vending machine sells
//This class inherits ClockCalendar
//It keeps the product type (MEET or ETIRPS) and the date/hour of the sell

class Logs : public ClockCalendar{
	bool meet;
	bool etirps;
	public:
		Logs();
		~Logs();
		void setLog(char p);
		char getLog(void);
};
#endif

