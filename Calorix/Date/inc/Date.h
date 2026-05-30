#ifndef DATE_H
#define DATE_H

#include <string>
#include <compare>

class Date
{
private:
    int s8Day;
    int s8Month;
    int s8Year;

public:
    Date(int s8Day, int s8Month, int s8Year);

    int getDay()   const;
    int getMonth() const;
    int getYear()  const;

    std::string toString()     const;
    std::string dateToDtring();

    bool operator==(const Date& other) const;

    auto operator<=>(const Date& other) const
    {
        if(s8Year != other.s8Year)
            return s8Year <=> other.s8Year;
        if(s8Month != other.s8Month)
            return s8Month <=> other.s8Month;
        return s8Day <=> other.s8Day;
    }

    static Date today();
};

#endif // DATE_H
