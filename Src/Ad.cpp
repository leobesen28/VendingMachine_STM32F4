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

This class creats an advertising object, witch will be displayed in the LCD

*/
#include "Ad.h"

Ad::Ad(void){
	strcpy(advertisement, "EMPTY");
}
Ad::Ad(char* ad){
	strcpy(advertisement, ad);
}
Ad::~Ad(void){
	//cout << "Destrutor cliente..." << endl;
}
void Ad::getAd(char* adv){
	 strcpy(adv, advertisement);
}
void Ad::setAd(char* ad){
	strcpy(advertisement, ad);
}


