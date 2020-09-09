#pragma once
#include "string"

class Date {
public:
	unsigned int day; 
	unsigned int month; 
	unsigned int year;

	unsigned int hour;
	unsigned int minute;

	bool isValidDate();
	std::string getWeekday();
	
	int timeDifferenceInDays(Date date1, Date date2);
	int timeDifferenceInMinutes(Date date1, Date date2);

	Date addMinutesToDate(int minutes, Date date);
	Date addDaysToDate(int days, Date date);

};
