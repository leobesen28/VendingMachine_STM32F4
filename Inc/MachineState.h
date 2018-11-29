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
/////////////////////////////////////////////////////////////////////////////
							TABELA DE ESTADOS
EA		NADA	M025		M050		M100		DEV			MEET	ETIRPS
0x00	0x00	0x01		0x02		0x04		0x00		0x00	0x00
0x01	0x01	0x02		0x03		0x05		0x00,D025	0x01	0x01
0x02	0x02	0x03		0x04		0x06		0x00,D050	0x02	0x02
0x03	0x03	0x04		0x05		0x06, D025	0x00,D075	0x03	0x03
0x04	0x04	0x05		0x06		0x06, D050	0x00,D100	0x04	0x04
0x05	0x05	0x06		0x06,D025	0x06, D075	0x00,D125	0x05	0x05
0x06	0x06	0x06,D025	0x06,D050	0x06, D100	0x00,D150	0x00	0x00
0x07    0x07    0x07        0x07        0x07        0x07        0x07    0x07 
//////////////////////////////////////////////////////////////////////////////
*/
#ifndef MACHINESTATE_H
	#define MACHINESTATE_H
	
#include "SalesControl.h"
#include "ButtonState.h"
/*
MachineState class if the FSM of the vending machine
It inherits SalesControl to manage logs and ButtonState to update and get the buttons state
*/

class MachineState : public ButtonState, public SalesControl {
		char state;
		char lastState;
		short int user_input;
		OutputInterface* outputPtr;
	public:
		MachineState(OutputInterface*);
		~MachineState(void);	
		uint8_t nextState(uint16_t GPIO_Pin);
		void addInStock(char lastState);
	  void incMEET(void);
		void incETIRPS(void);
};
#endif
