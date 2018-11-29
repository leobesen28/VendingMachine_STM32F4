/*

-----------------------------------------------------
|		FEDERAL UNIVERSITY OF SANTA CATARINA		|
|			C++ FOR EMBEDDED SYSTEMS				|
|			PROJECT: VENDING MACHINE				|
|		PROFESSOR: EDUARDO AUGUSTO BEZERRA			|
| 	 	 	 LEONARDO AURÉLIO BESEN					|
|			JOÃO BATISTA CORDEIRO NETO				|
----------------------------------------------------- 



This class creats an advertising object, witch will be displayed in the LCD

*/

#ifndef AD_H
	#define AD_H
	
#include <string.h>

class Ad {
		char advertisement[20]; //Advertising message
	public:
		Ad(void); //Constructor without params
		Ad(char*); //Constructor to instantiate the objetct with a message
		~Ad(void); //Destructor
		void getAd(char*); //Return the advertisement 
		void setAd(char*); //Change the advertisement
		
};
#endif
