#ifndef CLOCK_CALENDAR_H
	#define CLOCK_CALENDAR_H

#include "rtc.h"
#include <string.h>

//External RTC handler struck
extern RTC_HandleTypeDef hrtc;

/*
ClockCalendar class keeps the current hour and date when an object is instanciate 
*/

class ClockCalendar {
protected:
	RTC_TimeTypeDef myTime; //Struck for getting time from RTC functions
	RTC_DateTypeDef myDate;	//Struck for getting date from RTC functions
	uint8_t hour[21]; //Format: "Hour:       ho:mi:se"
	uint8_t date[21]; //Format: "Date:       mo:da:yr"
public:
	ClockCalendar(void);
	void readClock(uint8_t* clock);
	void readCalendar(uint8_t* date);
};
#endif
