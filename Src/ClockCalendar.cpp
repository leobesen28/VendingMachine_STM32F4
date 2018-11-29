#include "ClockCalendar.h"


/*
ClockCalendar Constructor
When an object is intanciate, it saves the current date and hour
*/
ClockCalendar::ClockCalendar(void) {
	
	HAL_RTC_GetDate(&hrtc, &myDate, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc, &myTime, RTC_FORMAT_BIN);
	sprintf((char *) hour, "Hour:      %2d:%2d:%2d", myTime.Hours,myTime.Minutes, myTime.Seconds);
	sprintf((char *) date, "Date:      %2d/%2d/%2d", myDate.Month,myDate.Date, myDate.Year + 2000);
}
/*
Get time clock

*/

void ClockCalendar::readClock(uint8_t* clock) {
	strcpy((char *)clock, (char *)hour);
}
/*
Get date
*/

void ClockCalendar::readCalendar(uint8_t* dat) {
	strcpy((char *)dat, (char *)date);
}

