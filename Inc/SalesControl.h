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
SalesControl class manage the sells in the vending machine

cash : total cash of the sales
Q_MEET : total number of MEET available to sell
Q_ETIRPS : total number of ETIPS available to sell
*/
#ifndef SALES_CONTROL_H
	#define SALES_CONTROL_H



#include "StackNode.h"
#include "OutputInterface.h"

class SalesControl {
	Stack* reg;
	Logs* log;
	int Q_ETIRPS;
	int Q_MEET; 
	public:
		SalesControl(void);
		~SalesControl(void);
		void setCash(float);
		float getCash(void);
		void setQuantity(uint8_t, int, uint8_t);
		int getQuantity(uint8_t);
		void listLogs(OutputInterface*);
};
#endif
