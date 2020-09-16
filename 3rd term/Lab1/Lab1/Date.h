#pragma once
#include "string"
#include <fstream>
#include <istream>
#include <iomanip>

const int MAX_DAYS_IN_MONTH[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date {
public:
	unsigned int day; 
	unsigned int month; 
	unsigned int year;

	unsigned int hour;
	unsigned int minute;

	Date() = default;
	explicit Date(int day, int month, int year, int hour, int minute) {
		this->day = day;
		this->month = month;
		this->year = year;
		this->hour = hour;
		this->minute = minute;
	}

	bool isValidDate();
	std::string getWeekday();
	
	int timeDifferenceInDays(Date date1, Date date2);
	int timeDifferenceInMinutes(Date date1, Date date2);

	Date addMinutesToDate(int minutes, Date date);
	Date addDaysToDate(int days, Date date);

	friend std::ostream& operator<<(std::ostream& stream, const Date& date);
	friend std::istream& operator>>(std::istream& stream, Date& date);
	bool operator<=(const Date& rhs) { return (day <= rhs.day) && (month <= rhs.month) && (year <= rhs.year); };
};
