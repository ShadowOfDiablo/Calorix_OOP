#include "Date.h"
#include <ctime>


Date::Date(int day, int month, int year)
    : day(day), month(month), year(year) {
}
//validation!


int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }


bool Date::operator==(const Date& other) const {
    return day == other.day &&
        month == other.month &&
        year == other.year;
}


std::string Date::dateToDtring()
{
    return std::to_string(day) + "." +
        std::to_string(month) + "." +
        std::to_string(year);
}

Date Date::today() {
    std::time_t t = std::time(nullptr);
    std::tm now{};
    localtime_s(&now, &t);

    return Date(
        now.tm_mday,
        now.tm_mon + 1,
        now.tm_year + 1900
    );
}
