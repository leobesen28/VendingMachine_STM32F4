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

#include "SalesControl.h"

uint8_t s_logs[] =   "LOGS";//5
uint8_t o_MEET[] =   "MEET";//5
uint8_t o_ETIRPS[] = "ETIRPS";//6



//Constructor
SalesControl::SalesControl(void){
	Q_MEET = 2;
	Q_ETIRPS = 2;
	
	reg = new Stack;
}
//Destructor
SalesControl::~SalesControl(void){
	delete reg;
}
//set que quantity of products available
//select the product in 'p'
//	p = 0x00 => MEET
//	p = 0x01 => ETIRPS 
//set the quantity in 'q'
//sell - when a product was sold, sell = 0x01  
void SalesControl::setQuantity(uint8_t p, int q, uint8_t sell){
	if(p == 0x00){
		Q_MEET = q;
	}else if(p == 0x01){
		Q_ETIRPS = q;
	}
	if(sell == 0x01){
		log = new Logs();
		log->setLog(p);
		reg->insertFirst(*log);

		delete log;
	}
}
//get que quantity of products available
//select the product in 'p'
//	p = 0x00 => MEET
//	p = 0x01 => ETIRPS 
int SalesControl::getQuantity(uint8_t p){
	if(p == 0x00){
		return Q_MEET;
	}else if(p == 0x01){
		return Q_ETIRPS;
	}
	return 0;
}

//Sends via USB to a terminal (windows/linux)
void SalesControl::listLogs(OutputInterface* output){
	//print info message
	output->printToUser(12, s_logs, 5);
	Node_S* auxNode = reg->getHead(); //get pointer to the first node
	Logs auxLog; //create an auxiliar log
	uint8_t clk[21]; //Format: "Hour:       ho:mi:se"
	uint8_t date[21]; //Format: "Date:       mo:da:yr"
	uint16_t i = 13; //Controls line to print in the display
	
	while (auxNode != 0){
		auxLog = auxNode->getValue();
		if(auxLog.getLog() == 'M'){ //check the product present in the log
			output->printToUser(i, o_MEET, 5);
		}else{
			output->printToUser(i, o_ETIRPS, 6);
		}
		//get hour and date of the log
		auxLog.readCalendar(date);
		auxLog.readClock(clk);
		//print hour and date
		output->printToUser(i+1,date, 10);
		output->printToUser(i+2,clk, 10);
		//increment by 4 the line control variable to print the next log
		i += 4;
		auxNode = auxNode->getNextNode();
    }
}

