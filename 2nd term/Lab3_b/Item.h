#pragma once
#include <string>
#include <stdexcept>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "Item.h"

extern size_t ITEMS_COUNT_IN_DB;

const std::string UNITS_OF_MEASUREMENT[]{"kilograms", "packages", "pieces", "liters" };//should I use enum?
const int MAX_DAYS_IN_MONTH[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Date {
    //example = "14/10/2020 02:50"
    int day = 0, month = 0, year = 0;
    int h = 0, m = 0;
    inline bool LeapYear(unsigned int m_year) const { return m_year % 4 == 0 && (m_year % 100 != 0 || m_year % 400 == 0); }

    Date()= default;
    explicit Date(int day, int month,int year, int h, int m){
        this->day = day;
        this->month = month;
        this->year = year;
        this->h = h;
        this->m = m;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Date& date);
    friend std::istream& operator>>(std::istream& stream, Date& date);
    Date operator + (size_t days) const;
    bool operator<=(const Date& rhs){return (day <= rhs.day) && (month <= rhs.month) && (year <= rhs.year);};
};

class Item {
private:
    size_t ID = 0;
    std::string name = "Name";
    std::string units = "pieces";
    Date manufacture_date{0,0,0,0,0};
    int expiration_period_in_days = 0;
    float quantity = 0;

protected:
    void setID(size_t new_ID) {this->ID = new_ID;};

public:
    Item(std::string name, float quantity, int units_index, Date manufacture_date, int expiration_period_in_days);
    Item()= default;

    void setID() {ID = ITEMS_COUNT_IN_DB;};
    size_t getID() const { return ID; };

    void setName(std::string& name);
    std::string getName() const { return name; };

    void setQuantity(float& quantity);
    float getQuantity() const { return quantity; };

    void setUnits(int& units_index);
    void setUnits(std::string& units);
    std::string getUnits() const { return units; };

    void setManufactureDate(Date& manufacture_date);
    Date getManufactureDate() const { return manufacture_date; };

    void setExpirationPeriod(int& expiration_period_in_days);
    int getExpirationPeriod() const { return expiration_period_in_days; };


    friend std::ostream& operator<<(std::ostream& stream, const Item& item);
    friend std::istream& operator>>(std::istream& stream, Item& item);
    Item& operator=(const Item& rhs);

};