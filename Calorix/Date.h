#pragma once
#include <string>
#include <compare>

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int day, int month, int year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    std::string toString() const;

    bool operator==(const Date& other) const;

    auto operator<=>(const Date& other) const {
        if (year != other.year)
            return year <=> other.year;

        if (month != other.month)
            return month <=> other.month;

        return day <=> other.day;
    }
    std::string dateToDtring();

    static Date today();
};