#include "Calendar.h"
#include <iostream>
#include <iomanip>
using namespace std;

Calendar::Calendar(int _month, int _year) {

	month = _month;
	year = _year;
}

void Calendar::setFirstDay() {
	//This part determines which day will be the first day of that year (0 for Sunday, 1 for Monday, etc.)
	int day = 1;
	int y = year - (14 - month) / 12;
	int m = month + 12 * ((14 - month) / 12) - 2;
	firstday = (day + y + y / 4 - y / 100 + y / 400 + (31 * m / 12)) % 7;
}

void Calendar::print() {

	int NumberOfDaysInMonth;
	int FirstDayOfMonth = 0;
	int DayOfWeekCounter = 0;
	int DateCounter = 1;

	switch (month)
	{
	case 1:
		cout << setw(21) << "January " << year;
		NumberOfDaysInMonth = 31;
		break;
	case 2:
		cout << setw(21) << "February " << year;
		if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
			NumberOfDaysInMonth = 29;
		else
			NumberOfDaysInMonth = 28;
		break;
	case 3:
		cout << setw(21) << "March " << year;
		NumberOfDaysInMonth = 31;
		break;
	case 4:
		cout << setw(21) << "April " << year;
		NumberOfDaysInMonth = 30;
		break;
	case 5:
		cout << setw(21) << "May " << year;
		NumberOfDaysInMonth = 31;
		break;
	case 6:
		cout << setw(21) << "June " << year;
		NumberOfDaysInMonth = 30;
		break;
	case 7:
		cout << setw(21) << "July " << year;
		NumberOfDaysInMonth = 31;
		break;
	case 8:
		cout << setw(21) << "August " << year;
		NumberOfDaysInMonth = 31;
		break;
	case 9:
		cout << setw(21) << "September " << year;
		NumberOfDaysInMonth = 30;
		break;
	case 10:
		cout << setw(21) << "October " << year;
		NumberOfDaysInMonth = 31;
		break;
	case 11:
		cout << setw(21) << "November " << year;
		NumberOfDaysInMonth = 30;
		break;
	case 12:
		cout << setw(21) << "December " << year;
		NumberOfDaysInMonth = 31;
		break;
	}

	//Display the days at the top of each month

	cout << "\nSun   Mon   Tue   Wed   Thu   Fri   Sat";
	cout << "\n\n" << setw(2);

	//Determine where the first day begins

	for (FirstDayOfMonth; FirstDayOfMonth < firstday; ++FirstDayOfMonth)
	{

		cout << setw(14);
	}

	int tempfirstday = firstday;
	DateCounter = 1;
	DayOfWeekCounter = tempfirstday;
	//This loop represents the date display and will continue to run until
	//the number of days in that month have been reached
	for (DateCounter; DateCounter <= NumberOfDaysInMonth; ++DateCounter)
	{
		cout << DateCounter << setw(6);
		++DayOfWeekCounter;
		if (DayOfWeekCounter > 6)
		{
			cout << "\n\n" << setw(2);
			DayOfWeekCounter = 0;
		}
	}
	cout << " \n";

	tempfirstday = DayOfWeekCounter + 1;
}
