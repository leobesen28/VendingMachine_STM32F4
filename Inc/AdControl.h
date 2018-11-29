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
#ifndef AD_CONTROL_H
	#define AD_CONTROL_H

#include "main.h"
#include "FilaNode.h"
#include "OutputInterface.h"
#include "InputInterface.h"
#include "ClockCalendar.h"

//External RNG handler struck 
extern RNG_HandleTypeDef hrng;

/*
AdControl class controls: 
						Advertisement flow to the output interface;
						Received ads from the user
*/
class AdControl {
	public:
		Fila displayAds;
		Fila newAds;
		Ad nowInDisplay;
		OutputInterface* outputPtr;
		InputInterface* inputPtr;
		ClockCalendar* clock;
	
		AdControl(OutputInterface*, InputInterface*); //Constructor
		~AdControl(void);//Destructor
		uint8_t getAdFromUser(uint16_t); //Receive ads from the user when requested 
		void addNewAds(void); //Transfer the ads located in NewAds to DisplayAds 
		void sendAdToDisplay(uint32_t randomNumber, uint8_t* hour, uint8_t* date); //Display an Ad
		void getAdFromDisplay(void); //Return the Ad from the display to the end of the list
		
};

#endif

