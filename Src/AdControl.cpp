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

#include "AdControl.h"

/*
List of messages to be displayed
*/

uint8_t noAds[] = 		"No ads to display...";//22
uint8_t emptyList[] = "List is empty";//13
uint8_t  receiveAd[] = "Add new ad?";
uint8_t  deleteAd[] = "Delete ad?";
uint8_t  writeAd[] = "Write new ad below:";
uint8_t  adAdded[] = "Added new AD";
uint8_t  adDeleted[] = "Deleted AD";
uint8_t  maxAdSize[] = "maximum AD size";
uint8_t  minAdSize[] = "Minimum AD size";
uint8_t  addToDisplay[] = "Transfer new ads ";
uint8_t  addedToDisplay[] = "Transfered new ads ";


//Debug - Initial ads
char adv1[] = "--Leonardo Besen--";
char adv2[] = "---Joao Batista---";

//Constructor
AdControl::AdControl(OutputInterface* output, InputInterface* input){
	

		outputPtr = output;//Set output interface
		inputPtr = input;
		//Initial advertisements - DEBUG test
	  Ad ad1(adv1); //create ad1
		Ad ad2(adv2); //create ad2
		displayAds.insertAfterLast(ad1); //insert ad1 in the displayAds queue
		displayAds.insertAfterLast(ad2); //insert ad2 in the displayAds queue
		
	
}

AdControl::~AdControl(void){}

//Transfer the ads located in NewAds to DisplayAds 
//Using overload of the operator +
void AdControl::addNewAds(void){
	
	if(newAds.getHead() == 0){
		outputPtr->printToUser(7, noAds, 22);
	}else{
		while(newAds.getHead() != 0){
			displayAds.insertAfterLast(newAds.removeFirst());
		}
	}
} 
 
//Display an Ad
void AdControl::sendAdToDisplay(uint32_t randomNumber, uint8_t* hour, uint8_t* date){
	
	
	char* pfrom; //Local variable used to get an ad 
	uint8_t toDisplay[20]; //Local variable to store an ad and send it to the output interface
	static char j = 0x03; //Controls the Hour/Date randomic presentation
	
	//Get an ad from displayAds queue if it exist
	if(displayAds.getHead() == 0){
		outputPtr->clearLCD(5);
		outputPtr->printToUser(10, emptyList, 13);
	}else{
		nowInDisplay = displayAds.removeFirst();
		nowInDisplay.getAd(pfrom);
		//char to uint8_t - the output only accepts uint8_t type
		for(int i = 0; i < 20; i++){
			toDisplay[i] = pfrom[i];
		}
		//clear and print an ad
		outputPtr->clearLCD(5);
		outputPtr->printToUser(10, toDisplay, sizeof(toDisplay));
		//Control of the Hour/Date randomic presentation
		//RNG generates and randomic number of 32 bits size
		//The size was divided in four identical parts
		//Each part will assign j with a different value between 3 and 6 
		if(j < 0x01){
				if(randomNumber > 0x00000000 && randomNumber <= 0x3FFFFFFF)
					j = 0x03;
				else if(randomNumber > 0x3FFFFFFF && randomNumber <= 0x7FFFFFFF)
					j = 0x04;
				else if(randomNumber > 0x7FFFFFFF && randomNumber <= 0xBFFFFFFF)
					j = 0x05;
				else if(randomNumber > 0xBFFFFFFF && randomNumber <= 0xFFFFFFFF)
					j = 0x06;
				//print date and hour only when j = 0
				outputPtr->printToUser(13, hour, 21);
				outputPtr->printToUser(14, date, 21);
		//If (j != 0) it will just clear the output	and decrement j	
		}else if(j>=0x01){
				j--;
				outputPtr->clearLCD(13);
		}	
	}	

	
}
//Return the Ad from the display to the end of the list
void AdControl::getAdFromDisplay(void){
	
	displayAds.insertAfterLast(nowInDisplay);
} 

//Receive new ad from user
uint8_t AdControl::getAdFromUser(uint16_t GPIO_Pin){
	
		static char addAd = 0x00; //keep state of adding a new ad
		char delAd = 0x00; //inform if the user wants to delete the current ad

		uint8_t status = 0x00; //not ready
		static char text[20] = {97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97,97}; //ASCII 'a'
		uint8_t display[20]; //print to user the current written message
		static int j = 1; //
		
		//Display info messages to the user		
		if(addAd == 0x00){
			outputPtr->clearLCD(5);
			outputPtr->printToUser(9, receiveAd, 20);
			outputPtr->printToUser(10, deleteAd, 20);
			outputPtr->printToUser(11, addToDisplay, 17);
		}
		//Checks what button was pressed
		if(GPIO_Pin == GPIO_PIN_1){
			outputPtr->clearLCD(5);
			outputPtr->printToUser(9, writeAd, 20);
			addAd = 0x01;
		}else if(GPIO_Pin == GPIO_PIN_4){
			outputPtr->clearLCD(5);
			outputPtr->printToUser(9, adDeleted, 20);
			delAd = 0x01;
		}else if(GPIO_Pin == GPIO_PIN_5){
			addNewAds(); // transfers ads from newAds to displayAds
			status = 0x01; //status ready
			outputPtr->clearLCD(5);
			outputPtr->printToUser(10, addedToDisplay, 19);
		}
		
		//Routine to add a new advertisement
		if(addAd == 0x01){
			if(GPIO_Pin == GPIO_PIN_11){ //GPIO PC11 pressed - increment value in the current text vector position
				text[j-1]++;
				for(int i = 0; i < j; i++){ //get the current written message
					display[i] = text[i];
				}
				//clear the output and display the current written message	
				outputPtr->clearLCD(5);
				outputPtr->printToUser(10, display, j);
			}else if(GPIO_Pin == GPIO_PIN_2){ //GPIO PD2 pressed - decrement value in the current text vector position
				text[j-1]--;
				for(int i = 0; i < j; i++){
					display[i] = text[i]; //get the current written message
				}
				//clear the output and display the current written message	
				outputPtr->clearLCD(5);
				outputPtr->printToUser(10, display, j);
			}else if(GPIO_Pin == GPIO_PIN_7){ //GPIO PD7 pressed - next vector text position
					if(j<=20) //checks maximum size
						j++;
					else{
						outputPtr->clearLCD(5);
						outputPtr->printToUser(10, maxAdSize, 17);
					}
			}else if(GPIO_Pin == GPIO_PIN_8){ //GPIO PC8 pressed - next vector text position
					if(j>1) //checks minimum size
						j--;
					else{
						outputPtr->clearLCD(5);
						outputPtr->printToUser(10, minAdSize, 17);
					}
					
			}else if(GPIO_Pin == GPIO_PIN_9){ //GPIO PG9 pressed - stops advertisements receiving
 				for(int d = 20; d >= j; d--){ //clear unwanted values in not written positions of the text vector
					text[d] = 0;
				}
				Ad ad(text); //creat an object with the new ad
				newAds.insertAfterLast(ad); //Inset the new ad in the queue
				status = 0x01; //status ready
				//Set initial values
				addAd = 0x00;
				j = 1;
				for(int i = 0; i < 20; i++){
					text[i] = 97;
				}
				//clear output and send info message
				outputPtr->clearLCD(5);
				outputPtr->printToUser(9, adAdded, 20);
			}
			return status;
		}else if(delAd == 0x01){
			delAd = 0x00;
			//To delete an advertisement, just send another ad without getting back the ad you want to delete
			sendAdToDisplay(0,0,0);
			status = 0x01; //status ready
			return status;
		}
		return status;
}



