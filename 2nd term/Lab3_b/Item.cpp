#include "Item.h"

Item::Item(std::string name, float quantity, int units_index, Date manufacture_date, int expiration_period_in_days) {
    setID();
    setName(name);
    setQuantity(quantity);
    setUnits(units_index);
    setManufactureDate(manufacture_date);
    setExpirationPeriod(expiration_period_in_days);
}

std::ostream& operator<<(std::ostream& stream, const Item& item) {
    stream << std::setfill('0');
    stream << item.getID();
    stream << ' ' << item.getName();
    stream << ' ' << item.getQuantity();
    stream << ' ' << item.getUnits();
    stream << ' ' << item.getManufactureDate();
    stream << ' ' << item.getExpirationPeriod();
    return stream;
}

std::istream& operator>>(std::istream& stream, Item& item) {
    std::string name;
    float quantity;
    int units_index, expiration;
    Date date;

    std::cout << "Name: "; stream >> name;
    std::cout << "Quantity: "; stream >> quantity;
    std::cout << "Units of Measurement(0 - kilograms, 1 - packages, 2 - pieces, 3 - liters): "; stream >> units_index;
    std::cout << "Manufacture date(d/m/y h:m): "; stream >> date;
    std::cout << "Expiration Period(days): "; stream >> expiration;

    item.setID();
    item.setName(name);
    item.setQuantity(quantity);
    item.setUnits(units_index);
    item.setManufactureDate(date);
    item.setExpirationPeriod(expiration);
    return stream;
}


Item& Item::operator= (Item const &other){
    if (&other != this) {
        this->setID(other.getID());
        name = other.getName();
        units = other.getUnits();
        manufacture_date = other.getManufactureDate();
        expiration_period_in_days = other.getExpirationPeriod();
        quantity = other.getQuantity();
        return *this;
    }
    else return *this;
}


std::ostream& operator<<(std::ostream& stream, const Date& date) {
    stream << std::setfill('0');
    stream << std::setw(2) << date.day << '/' << std::setw(2) << date.month << '/' << date.year << ' ';
    stream << std::setw(2) << date.h << ':' << std::setw(2) << date.m;
    return stream;
}

Date Date::operator + (size_t days) const {
    int max_days = MAX_DAYS_IN_MONTH[month] + (month == 2 && LeapYear(year) ? 1 : 0);//+1 extra day to February during leap years

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
        max_days = MAX_DAYS_IN_MONTH[month] + (month == 2 && LeapYear(year) ? 1 : 0);
    }

    return Date(res_days, res_month, res_year, h, m);
}

std::istream& operator>>(std::istream& stream, Date& date) {
    //TODO:check if date is valid
    stream >> date.day;
    stream.ignore(1);
    stream >> date.month;
    stream.ignore(1);
    stream >> date.year;
    stream.ignore(1);
    stream >> date.h;
    stream.ignore(1);
    stream >> date.m;
    return stream;
}

std::ifstream& operator>>(std::ifstream& stream, Date& date) {
    int day = 0, month = 0, year = 0, h = 0, m = 0;
    stream >> day;
    stream.ignore(1);
    stream >> month;
    stream.ignore(1);
    stream >> year;
    stream.ignore(1);
    stream >> h;
    stream.ignore(1);
    stream >> m;
    date = Date(day,month,year,h,m);
    return stream;
}

void Item::setName(std::string& name){
    if (name.length()!=0 || name.find(' ') == std::string::npos)
        this->name = name;
    else throw std::invalid_argument("name cannot be null");
}

void Item::setQuantity(float& quantity){
    if (quantity >= 0)
        this->quantity = quantity;
    else throw std::invalid_argument("quantity cannot be negative");
}

void Item::setUnits(int& unit_index){
    if (unit_index >= 0 && unit_index < 4)//0..3
        this->units = UNITS_OF_MEASUREMENT[unit_index];
    else throw std::invalid_argument("wrong unit index");
}

void Item::setManufactureDate(Date& manufacture_date){
    this->manufacture_date = manufacture_date;
}

void Item::setExpirationPeriod(int& expiration_period_in_days){
    if (expiration_period_in_days < 365 * 10)
        this->expiration_period_in_days = expiration_period_in_days;
    else throw std::invalid_argument("expiration period has to be less than 10 years");
}
