#include "Date.h"

inline bool isLeap(unsigned int year) {
    return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}
 
bool Date::isValidDate(){
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;

    if (minute < 0 || minute > 59)
        return false;
    if (hour < 0 || hour > 23)
        return false;

    if (month == 2) { // February 
        if (isLeap(year))
            return (day <= 29);
        else
            return (day <= 28);
    }

    if (month == 4 || month == 6 ||
        month == 9 || month == 11)
        return (day <= 30);

    return true;
}

//Zeller’s algorythm
 std::string Date::getWeekday() {
     if (month == 1) {
         month = 13;
         year--;
     } else if (month == 2) {
         month = 14;
         year--;
     }

     int k = year % 100;
     int j = year / 100;
     int w = day + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j;

     switch(w%7) {
     case 0: return "Saturday";
     case 1: return "Sunday";
     case 2: return "Monday";
     case 3: return "Tuesday";
     case 4: return "Wednesday";
     case 5: return "Thursday";
     case 6: return "Friday";
     }
}


 std::ostream& operator<<(std::ostream& stream, const Date& date) {
     stream << std::setfill('0');
     stream << std::setw(2) << date.day << '/' << std::setw(2) << date.month << '/' << date.year << ' ';
     stream << std::setw(2) << date.hour << ':' << std::setw(2) << date.minute;
     return stream;
 }

 std::istream& operator>>(std::istream& stream, Date& date) {
     stream >> date.day;
     stream.ignore(1);
     stream >> date.month;
     stream.ignore(1);
     stream >> date.year;
     stream.ignore(1);
     stream >> date.hour;
     stream.ignore(1);
     stream >> date.minute;
     return stream;
 }


 // would cause overflow for years >= ~5883516
 int Date::timeDifferenceInDays(Date date1, Date date2){     
     // (year number* days in year) + (month number * days in month) + days;
     int date1_in_days = date1.year * 365 + isLeap(date1.year) + MAX_DAYS_IN_MONTH[date1.month] * date1.month + date1.day;
     int date2_in_days = date2.year * 365 + isLeap(date2.year) + MAX_DAYS_IN_MONTH[date2.month] * date2.month + date2.day;

     return abs(date1_in_days - date2_in_days);
 }


 int Date::timeDifferenceInMinutes(Date date1, Date date2) {

     int date1_time_in_minutes = date1.hour * 60 + date1.minute;
     int date2_time_in_minutes = date2.hour * 60 + date2.minute;

     return timeDifferenceInDays(date1, date2)*24*60 + abs(date1_time_in_minutes - date2_time_in_minutes);
 }

 Date Date::addDaysToDate(int days, Date date) {
     int max_days = MAX_DAYS_IN_MONTH[month] + (month == 2 && isLeap(year) ? 1 : 0);//+1 extra day to February during leap years

     int res_year = year;
     int res_month = month;
     int res_days = day + days;

     // iterating until met a valid number of days in a month
     while (res_days > max_days) {
         //subtracts until difference is less than month length
         res_days -= max_days;

         // advance to next month
         ++res_month;

         // check if result date falls on tothe next year
         if (res_month > 12) {
             // setting to January of the next year
             res_month = 1;
             ++res_year;
         }

         //update max_days value for the next month
         max_days = MAX_DAYS_IN_MONTH[month] + (month == 2 && isLeap(year) ? 1 : 0);
     }

     return Date(res_days, res_month, res_year, hour, minute);
 }


 Date Date::addMinutesToDate(int minutes, Date date) {
     
     int res_hour = date.hour, res_minute = date.minute + minutes;
     int days_to_add = 0;

     while (res_minute >= 60) {
         res_hour++;
         minutes -= 60;
     }

     while (res_hour > 23) {
         res_hour -= 24;
         days_to_add++;
     }

     return addMinutesToDate(days_to_add, Date(day, month, year, res_hour, res_minute));
 }