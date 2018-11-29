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

#include "MachineState.h"


/*
Messages to be displayed in the stm32f429 LCD 
*/
	  uint8_t t000[] =  		"Credit = R$ 0.00"; //17
	  uint8_t t025[] =  		"Credit = R$ 0.25";
	  uint8_t  t050[] = 		"Credit = R$ 0.50";
	  uint8_t  t075[] = 		"Credit = R$ 0.75";
	  uint8_t  t100[] = 		"Credit = R$ 1.00";
	  uint8_t  t125[] = 		"Credit = R$ 1.25";
	  uint8_t  t150[] = 		"Credit = R$ 1.50";
	  uint8_t  d000[] = 		"Returned = R$ 0.00"; //19
	  uint8_t  d025[] = 		"Returned = R$ 0.25";
	  uint8_t  d050[] = 		"Returned = R$ 0.50";
	  uint8_t  d075[] = 		"Returned = R$ 0.75";
	  uint8_t  d100[] = 		"Returned = R$ 1.00";
	  uint8_t  d125[] = 		"Returned = R$ 1.25";
	  uint8_t  d150[] = 		"Returned = R$ 1.50";
	  uint8_t  s_MEET[] = 	"MEET released!"; //15
	  uint8_t  s_ETIRPS[] = "EITRPS released!"; //17
		uint8_t  nec[] = 			"Not enough credit"; //18
		uint8_t  ple[] = 			"Please insert:"; //15
	  uint8_t  v025[] = 		"R$ 0.25"; //8
	  uint8_t  v050[] = 		"R$ 0.50";
	  uint8_t  v075[] = 		"R$ 0.75";
	  uint8_t  v100[] = 		"R$ 1.00";
	  uint8_t  v125[] = 		"R$ 1.25";
	  uint8_t  v150[] = 		"R$ 1.50";
		uint8_t	 avMEET[] = 	"Available MEET"; //15
		uint8_t  avETIRPS[] = "Available ETIRPS"; //17
		uint8_t  addStock[] = "ADD MORE TO STOCK?"; //19
		uint8_t  adMEET[] = 	"ADD MORE MEET?"; //15
		uint8_t  adETIRPS[] = "ADD MORE ETIRPS?"; //17
		uint8_t	 qMEET[] = 		"ADD MEET QUANTITY"; //18
		uint8_t  qETIRPS[] = 	"ADD ETIRPS QUANTITY"; //21
		uint8_t	 addedMEET[] = "ADDED MEET";//11
		uint8_t	 addedETIRPS[] = "ADDED ETIRPS"; //13
		uint8_t	 notaddedMEET[] = "NOT ADDED MEET";//15
		uint8_t	 notaddedETIRPS[] = "NOT ADDED ETIRPS";//17
		uint8_t  s_cash[] = 	"CASH";//5
		uint8_t  stock_MEET[] = "STOCK OF MEET EMPTY";//20
		uint8_t	 stock_ETIRPS[] = "STOCK OF ETIRPS EMPTY";//22
		uint8_t  sel_other[] = 		"SELECT OTHER OR PRESS DEV";//26
		uint8_t  max_value_input_stock[] = "MAX 10";//6
		
/*
end messages
*/



MachineState::MachineState(OutputInterface* output){
	
	//get output interface
	outputPtr = output;
	
	state = 0x00; //Keeps current state	
	lastState = 0x00; //Keeps last state
	
	//Keed the quantity informed by the user
	user_input = 0;
	
	setQuantity(0x00, 2, 0x00);
	setQuantity(0x01, 2, 0x00);
}

MachineState::~MachineState(void){}


uint8_t MachineState::nextState(uint16_t GPIO_Pin){
		
		uint8_t quantity = 0x00;
		
			//Update the pressed button state
			switch(GPIO_Pin){
			case 0x0002: //PC1
				if(state != 7){
					resetButtonState(0x01, 0x00);
					setButtonState(BUTTON_M025, 1);
				}else
					setButtonState(BUTTON_STOCK_ACCESS, 1); //access stock increment
				break;
			case 0x0010: //PD4
				if(state != 7){
					resetButtonState(0x01, 0x00);
					setButtonState(BUTTON_M050, 1);
				}else
					setButtonState(BUTTON_ADD_MEET, 1); //add more meet
				break;
			case 0x0020: //PD5
				if(state != 7){
					resetButtonState(0x01, 0x00);
					setButtonState(BUTTON_M100, 1);
				}else
					setButtonState(BUTTON_ADD_ETIRPS, 1);//add more etirps
				break;
			case 0x0800://PC11
				if(state != 7){
					resetButtonState(0x01, 0x00);
					setButtonState(BUTTON_DEV, 1);
				}else
					setButtonState(BUTTON_STOCK_INC, 1);//increment
				break;
			case 0x0004://PD2
				if(state != 7){
					resetButtonState(0x01, 0x00);
					setButtonState(BUTTON_MEET, 1);
				}else
					setButtonState(BUTTON_STOCK_DEC, 1);//decrement
			 break;
			case 0x0200://PG9
				if(state != 7){
					resetButtonState(0x01, 0x00);
					setButtonState(BUTTON_ETIRPS, 1);
				}else
					setButtonState(BUTTON_STOCK_STOP, 1);//stop
				break;
			case 0x0080://PD7
				if(state != 7){
					resetButtonState(0x01, 0x00);
					setButtonState(BUTTON_STOCK, 1);
				}
				break;
			case 0x0100://PC8
				if(state != 7){
					resetButtonState(0x01, 0x00);
					setButtonState(BUTTON_CASH, 1);
				}
				break;
			default:
				break;
		}
			
		switch(state)
		{
			//State S000
			//Credit R$ 0.00
			case 0x00: 
				if(getButtonState(BUTTON_M025)){
					state = 0x01;
					//  Total Credit: 25
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t025, 17);
				}else if(getButtonState(BUTTON_M050)){
					state = 0x02;
					//   Total Credit: 50 
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t050, 17);
				}else if(getButtonState(BUTTON_M100)){
					state = 0x04;
					//  Total Credit: 100
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t100, 17);					
				}else if(getButtonState(BUTTON_DEV)){
					state = 0x00;
					// Return 0
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, d000, 19);
				}else if(getButtonState(BUTTON_MEET)){
					state = 0x00;
					//Not enough credit
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, nec, 18);
					outputPtr->printToUser(12, ple, 15);
					outputPtr->printToUser(13, v150, 8);
				}else if(getButtonState(BUTTON_ETIRPS)){
					state = 0x00;
					//Not enough credit
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, nec, 18);
					outputPtr->printToUser(12, ple, 15);
					outputPtr->printToUser(13, v150, 8);
				}else if(getButtonState(BUTTON_STOCK)){
					state = 0x07;
					lastState = 0x00;
					//STOCK
					outputPtr->clearLCD(5);
					outputPtr->printToUser(6, avMEET, 15);
					quantity = 0x30 + getQuantity(0x00);
					outputPtr->printToUser(7, &quantity, sizeof(&quantity));
					outputPtr->printToUser(8, avETIRPS, 17);
					quantity = 0x30 + getQuantity(0x01);
					outputPtr->printToUser(9, &quantity, sizeof(&quantity));
					outputPtr->printToUser(10, addStock, 19);
					
					listLogs(outputPtr);
				}else if(getButtonState(BUTTON_CASH)){
					state = 0x00;
					//CASH
					outputPtr->clearLCD(5);
					outputPtr->printToUser(11, t000, 17);
				}else{
					state = 0x00;	
				}
				return state;
			//State S025
			//Credit R$ 0.25
			case 0x01:
				if(getButtonState(BUTTON_M025)){
					state = 0x02;
					//  Total Credit: 50
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t050, 17);  
				}else if(getButtonState(BUTTON_M050)){
					state = 0x03;
					//  Total Credit: 75 
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t075, 17);
				}else if(getButtonState(BUTTON_M100)){
					state = 0x05;
					//  Total Credit: 125 
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t125, 17);
				}else if(getButtonState(BUTTON_DEV)){
					state = 0x00;
					//  Return:  25
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, d025, 19);
				}else if(getButtonState(BUTTON_MEET)){
					state = 0x01;
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, nec, 18);
					outputPtr->printToUser(12, ple, 15);
					outputPtr->printToUser(13, v125, 8);
				}else if(getButtonState(BUTTON_ETIRPS)){
					state = 0x01;
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, nec, 18);
					outputPtr->printToUser(12, ple, 15);
					outputPtr->printToUser(13, v125, 8);
				}else if(getButtonState(BUTTON_STOCK)){
					lastState = 0x01;
					state = 0x07;
					//STOCK
					outputPtr->clearLCD(5);
					outputPtr->printToUser(6, avMEET, 15);
					quantity = 0x30 + getQuantity(0x00);
					outputPtr->printToUser(7, &quantity, sizeof(&quantity));
					outputPtr->printToUser(8, avETIRPS, 17);
					quantity = 0x30 + getQuantity(0x01);
					outputPtr->printToUser(9, &quantity, sizeof(&quantity));
					outputPtr->printToUser(10, addStock, 19);
				}else if(getButtonState(BUTTON_CASH)){
					state = 0x01;
					//CASH
					outputPtr->clearLCD(5);
					outputPtr->printToUser(11, t025, 17);
				}else{
					state = 0x01;	
				}
				return state;
			//State S050
			//Credit R$ 0.50
			case 0x02:
				if(getButtonState(BUTTON_M025)){
					state = 0x03;
					//  Total Credit: 75 
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t075, 17);
				}else if(getButtonState(BUTTON_M050)){
					state = 0x04;
					//  Total Credit: 100
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t100, 17);  
				}else if(getButtonState(BUTTON_M100)){
					state = 0x06;
					//  Total Credit: 150 
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t150, 17);  
				}else if(getButtonState(BUTTON_DEV)){
					state = 0x00;
					//  Return:  50  
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, d050, 19);  
				}else if(getButtonState(BUTTON_MEET)){
					state = 0x02;
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, nec, 18);
					outputPtr->printToUser(12, ple, 15);
					outputPtr->printToUser(13, v100, 8);
				}else if(getButtonState(BUTTON_ETIRPS)){
					state = 0x02;
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, nec, 18);
					outputPtr->printToUser(12, ple, 15);
					outputPtr->printToUser(13, v100, 8);
				}else if(getButtonState(BUTTON_STOCK)){
					lastState = 0x02;
					state = 0x07;
					//STOCK
					outputPtr->clearLCD(5);
					outputPtr->printToUser(6, avMEET, 15);
					quantity = 0x30 + getQuantity(0x00);
					outputPtr->printToUser(7, &quantity, sizeof(&quantity));
					outputPtr->printToUser(8, avETIRPS, 17);
					quantity = 0x30 + getQuantity(0x01);
					outputPtr->printToUser(9, &quantity, sizeof(&quantity));
					outputPtr->printToUser(10, addStock, 19);
				}else if(getButtonState(BUTTON_CASH)){
					state = 0x02;
					//CASH
					outputPtr->clearLCD(5);
					outputPtr->printToUser(11, t050, 17);
				}else{
					state = 0x02;	
				}
				return state;
			//State S075
			//Credit R$ 0.75
			case 0x03:
				if(getButtonState(BUTTON_M025)){
					state = 0x04;
					//  Total Credit: 100
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t100, 17);  
				}else if(getButtonState(BUTTON_M050)){
					state = 0x05;
					//  Total Credit: 125
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t125, 17);  
				}else if(getButtonState(BUTTON_M100)){
					state = 0x06;
					//  Total Credit: 150 
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t150, 17);  
					//  Return:  25  
					outputPtr->printToUser(12, d025, 19);
				}else if(getButtonState(BUTTON_DEV)){
					state = 0x00;
					//  Return:  75  
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, d075, 19);
				}else if(getButtonState(BUTTON_MEET)){
					state = 0x03;
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, nec, 18);
					outputPtr->printToUser(12, ple, 15);
					outputPtr->printToUser(13, v075, 8);
				}else if(getButtonState(BUTTON_ETIRPS)){
					state = 0x03;
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, nec, 18);
					outputPtr->printToUser(12, ple, 15);
					outputPtr->printToUser(13, v075, 8);
				}else if(getButtonState(BUTTON_STOCK)){
					lastState = 0x03;
					state = 0x07;
					//STOCK
					outputPtr->clearLCD(5);
					outputPtr->printToUser(6, avMEET, 15);
					quantity = 0x30 + getQuantity(0x00);
					outputPtr->printToUser(7, &quantity, sizeof(&quantity));
					outputPtr->printToUser(8, avETIRPS, 17);
					quantity = 0x30 + getQuantity(0x01);
					outputPtr->printToUser(9, &quantity, sizeof(&quantity));
					outputPtr->printToUser(10, addStock, 19);
				}else if(getButtonState(BUTTON_CASH)){
					state = 0x03;
					//CASH
					outputPtr->clearLCD(5);
					outputPtr->printToUser(11, t075, 17);
				}else{
					state = 0x03;	
				}
				return state;
			//State S100
			//Credit R$ 1.00
			case 0x04:
				if(getButtonState(BUTTON_M025)){
					state = 0x05;
					//  Total Credit: 125  
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t125, 17); 
				}else if(getButtonState(BUTTON_M050)){
					state = 0x06;
					//  Total Credit: 150  
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t150, 17); 
				}else if(getButtonState(BUTTON_M100)){
					state = 0x06;
					//  Total Credit: 150 
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t150, 17);  
					//  Return:  50  
					outputPtr->printToUser(12, d050, 19);  
				}else if(getButtonState(BUTTON_DEV)){
					state = 0x00;
					//  Return:  100  
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, d100, 19); 
				}else if(getButtonState(BUTTON_MEET)){
					state = 0x04;
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, nec, 18);
					outputPtr->printToUser(12, ple, 15);
					outputPtr->printToUser(13, v050, 8);
				}else if(getButtonState(BUTTON_ETIRPS)){
					state = 0x04;
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, nec, 18);
					outputPtr->printToUser(12, ple, 15);
					outputPtr->printToUser(13, v050, 8);
				}else if(getButtonState(BUTTON_STOCK)){
					lastState = 0x04;
					state = 0x07;
					//STOCK
					outputPtr->clearLCD(5);
					outputPtr->printToUser(6, avMEET, 15);
					quantity = 0x30 + getQuantity(0x00);
					outputPtr->printToUser(7, &quantity, sizeof(&quantity));
					outputPtr->printToUser(8, avETIRPS, 17);
					quantity = 0x30 + getQuantity(0x01);
					outputPtr->printToUser(9, &quantity, sizeof(&quantity));
					outputPtr->printToUser(10, addStock, 19);
				}else if(getButtonState(BUTTON_CASH)){
					state = 0x04;
					//CASH
					outputPtr->clearLCD(5);
					outputPtr->printToUser(11, t100, 17);
				}else{
					state = 0x04;	
				}
				return state;
			//State S125
			//Credit R$ 1.25
			case 0x05:
				if(getButtonState(BUTTON_M025)){
					state = 0x06;
					//  Total Credit: 150
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t150, 17);   
				}else if(getButtonState(BUTTON_M050)){
					state = 0x06;
					//  Total Credit: 150
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t150, 17);   
					//  Return:  25  
					outputPtr->printToUser(12, d025, 19); 
				}else if(getButtonState(BUTTON_M100)){
					state = 0x06;
					//  Total Credit: 150
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t150, 17);    
					//  Return:  75  
					outputPtr->printToUser(12, d075, 19); 
				}else if(getButtonState(BUTTON_DEV)){
					state = 0x00;
					//  Return:  125  
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, d125, 19);
				}else if(getButtonState(BUTTON_MEET)){
					state = 0x05; 
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, nec, 18);
					outputPtr->printToUser(12, ple, 15);
					outputPtr->printToUser(13, v025, 8);
				}else if(getButtonState(BUTTON_ETIRPS)){
					state = 0x05;
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, nec, 18);
					outputPtr->printToUser(12, ple, 15);
					outputPtr->printToUser(13, v025, 8);
				}else if(getButtonState(BUTTON_STOCK)){
					lastState = 0x05;
					state = 0x07;
					//STOCK
					outputPtr->clearLCD(5);
					outputPtr->printToUser(6, avMEET, 15);
					quantity = 0x30 + getQuantity(0x00);
					outputPtr->printToUser(7, &quantity, sizeof(&quantity));
					outputPtr->printToUser(8, avETIRPS, 17);
					quantity = 0x30 + getQuantity(0x01);
					outputPtr->printToUser(9, &quantity, sizeof(&quantity));
					outputPtr->printToUser(10, addStock, 19);
				}else if(getButtonState(BUTTON_CASH)){
					state = 0x05;
					//CASH
					outputPtr->clearLCD(5);
					outputPtr->printToUser(11, t125, 17);
				}else{
					state = 0x05;	
				}
				return state;
			//State S150
			//Credit R$ 1.50
			case 0x06:
				if(getButtonState(BUTTON_M025)){
					state = 0x06;
					//  Total Credit: 150 
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t150, 17);   
					//  Return:  25  
					outputPtr->printToUser(12, d025, 19); 
				}else if(getButtonState(BUTTON_M050)){
					state = 0x06;
					//  Total Credit: 150  
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t150, 17);  
					//  Return:  50  
					outputPtr->printToUser(12, d050, 19);   
				}else if(getButtonState(BUTTON_M100)){
					state = 0x06;
					//  Total Credit: 150 
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, t150, 17);   
					//  Return:  100  
					outputPtr->printToUser(12, d100, 19);  
				}else if(getButtonState(BUTTON_DEV)){
					state = 0x00;
					//  Return:  150  
					outputPtr->clearLCD(7);
					outputPtr->printToUser(11, d150, 19);
				}else if(getButtonState(BUTTON_MEET)){
					if(getQuantity(0x00) == 0){
						outputPtr->clearLCD(7);
						outputPtr->printToUser(11,stock_MEET, 20);
						outputPtr->printToUser(12, sel_other, 26);
						state = 0x06;
					}else{
						state = 0x00;
						//Reliase:  MEET  
						outputPtr->clearLCD(7);
						outputPtr->printToUser(11, s_MEET, 15);
						//Decrement the product quantity
						setQuantity(0x00, getQuantity(0x00) - 1, 0x01);
					}
				}else if(getButtonState(BUTTON_ETIRPS)){
					if(getQuantity(0x01) == 0){
						outputPtr->clearLCD(7);
						outputPtr->printToUser(11, stock_ETIRPS, 22);
						outputPtr->printToUser(12, sel_other, 26);
						state = 0x06;
					}else{
						state = 0x00;
						//Reliase:  ETIRPS 
						outputPtr->clearLCD(7);
						outputPtr->printToUser(11, s_ETIRPS, 17);
						//Decrement the product quantity
						setQuantity(0x01, getQuantity(0x01) - 1, 0x01);
					}
				}else if(getButtonState(BUTTON_STOCK)){
					state = 0x07;
					lastState = 0x06;
					//STOCK
					outputPtr->clearLCD(5);
					outputPtr->printToUser(6, avMEET, 15);
					quantity = 0x30 + getQuantity(0x00);
					outputPtr->printToUser(7, &quantity, sizeof(&quantity));
					outputPtr->printToUser(8, avETIRPS, 17);
					quantity = 0x30 + getQuantity(0x01);
					outputPtr->printToUser(9, &quantity, sizeof(&quantity));
					outputPtr->printToUser(10, addStock, 19);
				}else if(getButtonState(BUTTON_CASH)){
					state = 0x06;
					//CASH
					outputPtr->clearLCD(5);
					outputPtr->printToUser(11, t150, 17);
				}else{
					state = 0x06;	
				}
				return state;
            //State ADD - manage stock
			case 0x07:
				addInStock(lastState);
				return state;
			default:
				break;
		}
		return state;
}


void MachineState::addInStock(char lastState){

	//outputPtr->printToUser(10, addStock, 19);
	//To get access in the stock increment, press BUTTON_STOCK_ACCESS
	//If not, press BUTTON_STOCK_STOP
	if(getButtonState(BUTTON_STOCK_ACCESS)){ 
				outputPtr->clearLCD(5);
				outputPtr->printToUser(10, adMEET, 15);
				outputPtr->printToUser(11, adETIRPS, 17);
				if(getButtonState(BUTTON_ADD_MEET)){
				 	incMEET();
				}
				if(getButtonState(BUTTON_ADD_ETIRPS)){
					incETIRPS();
				}
	//Leave if the button BUTTON_STOCK_STOP was pressed		
	}else if(getButtonState(BUTTON_STOCK_STOP)){
		resetButtonState(0x00, BUTTON_STOCK_STOP);
		state = lastState;
		listLogs(outputPtr);
	}
}

void MachineState::incMEET(void){
	
				uint8_t quantity = 0x30;
	
				//To increment MEET Stock, press BUTTON_ADD_MEET
				//If not, press BUTTON_STOCK_STOP to leave
				 
				outputPtr->clearLCD(5);
				outputPtr->printToUser(10, qMEET, 18);
				outputPtr->printToUser(11, max_value_input_stock, 6);
				//To increment the stock by one, press BUTTON_STOCK_INC
				//To decrement the stock by one, press BUTTON_STOCK_DEC
				//To end the stock inc/dec, press BUTTON_STOCK_STOP
				if(!getButtonState(BUTTON_STOCK_STOP)){
							//Increment the stock
							if(getButtonState(BUTTON_STOCK_INC)){
								resetButtonState(0x00, BUTTON_STOCK_INC);;
								if(user_input < 10)
									user_input++;
							}
							//Decrement the stock
							if(getButtonState(BUTTON_STOCK_DEC)){
								resetButtonState(0x00, BUTTON_STOCK_DEC);
								if(user_input > 0)
									user_input--;
							}
							//Print the current quantity informed by the user
							quantity += user_input;
							outputPtr->printToUser(12, &quantity, sizeof(&quantity));
					}else if(getButtonState(BUTTON_STOCK_STOP)){
								//Update the stock quantity
								//Get the current quantity and sum with the new one informed by the user
								user_input += getQuantity(0x00);
								resetButtonState(0x01, 0x00);
								//Stock limit of 10 units
								//If more then 10 units, it will not be added to the stock, the operation will be cancelled
								if(user_input <= 10){
									setQuantity(0x00, user_input, 0x00);
									outputPtr->printToUser(13, addedMEET, 11);
									user_input = 0;
									state = lastState;
								}else{
									outputPtr->printToUser(13, notaddedMEET, 15);
									user_input = 0;
									state = lastState;
								}
					}
}
void MachineState::incETIRPS(void){
				
				uint8_t quantity = 0x30;
	
				//To increment ETIRPS Stock, press BUTTON_ADD_ETIRPS
				//If not, press BUTTON_STOCK_STOP to leave
				
				outputPtr->clearLCD(5);
				outputPtr->printToUser(10, qETIRPS, 21);
				outputPtr->printToUser(11, max_value_input_stock, 6);
				//To increment the stock by one, press BUTTON_STOCK_INC
				//To decrement the stock by one, press BUTTON_STOCK_DEC
				//To end the stock inc/dec, press BUTTON_STOCK_STOP
				if(!getButtonState(BUTTON_STOCK_STOP)){
							//Increment the stock
							if(getButtonState(BUTTON_STOCK_INC)){
								resetButtonState(0x00, BUTTON_STOCK_INC);;
								if(user_input < 10)
									user_input++;
							}
							//Decrement the stock
							if(getButtonState(BUTTON_STOCK_DEC)){
								resetButtonState(0x00, BUTTON_STOCK_DEC);
								if(user_input > 0)
									user_input--;
							}
							//Print the current quantity informed by the user
							quantity += user_input;
							outputPtr->printToUser(12, &quantity, sizeof(quantity));
					}else if(getButtonState(BUTTON_STOCK_STOP)){
								//Update the stock quantity
								//Get the current quantity and sum with the new one informed by the user
								user_input += getQuantity(0x01);
								resetButtonState(0x01, 0x00);
								//Stock limit of 10 units
								//If more then 10 units, it will not be added to the stock, the operation will be cancelled
								if(user_input <= 10){
									setQuantity(0x01, user_input, 0x00);
									outputPtr->printToUser(13, addedETIRPS, 13);
									user_input = 0;
									state = lastState;
								}else{
									outputPtr->printToUser(13, notaddedETIRPS, 17);
									user_input = 0;
									state = lastState;
								}
					}
}	

