#include "Date.h"
#include <ctime>

Date::Date(int s8Day, int s8Month, int s8Year)
    : s8Day(s8Day), s8Month(s8Month), s8Year(s8Year)
{
}

int Date::getDay()   const { return s8Day; }
int Date::getMonth() const { return s8Month; }
int Date::getYear()  const { return s8Year; }

bool Date::operator==(const Date& other) const
{
    return s8Day   == other.s8Day   &&
           s8Month == other.s8Month &&
           s8Year  == other.s8Year;
}

std::string Date::toString() const
{
    return std::to_string(s8Day) + "." +
           std::to_string(s8Month) + "." +
           std::to_string(s8Year);
}

std::string Date::dateToDtring()
{
    return std::to_string(s8Day) + "." +
           std::to_string(s8Month) + "." +
           std::to_string(s8Year);
}

Date Date::today()
{
    std::time_t t = std::time(nullptr);
    std::tm now{};
#ifdef _WIN32
    localtime_s(&now, &t);
#else
    localtime_r(&t, &now);
#endif
    return Date(now.tm_mday, now.tm_mon + 1, now.tm_year + 1900);
}
