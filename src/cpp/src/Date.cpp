//
// Created by Kalelzar on 24/03/2020.
//

#include "Date.hpp"
#include <ctime>
#include <cstring>

#ifdef _MSC_VER
#define sprintf sprintf_s
#endif //_MSC_VER

namespace Hotel {
    Date::Date(int year, int month, int day) {
        if (month > 12) {
#ifdef PRINT
            std::clog << "A date with a month above 12 is assumed to mean the appropriate month n years later.\n";
#endif
            year += month / 12;
            month = month % 12;
            if (month == 0) {
                month = 12;
                year -= 1;
            }
        } else if (month < 1) {
#ifdef PRINT
            std::clog << "A date with a month under 1 is assumed to mean the appropriate month n years earlier.\n";
#endif
            while (month < 1) {
                month += 12;
                year -= 1;
            }
        }

        if (day < 1) {
#ifdef PRINT
            std::clog << "A date with a day under 1 is assumed to mean the appropriate day n months earlier.\n";
#endif
            while (day < 1) {
                month -= 1;

                //FIX: Remove code duplication
                if (month > 12) {
                    year += month / 12;
                    month = month % 12;
                    if (month == 0) {
                        month = 12;
                        year -= 1;
                    }
                } else if (month < 1) {
                    while (month < 1) {
                        month += 12;
                        year -= 1;
                    }
                }

                day += daysOfMonth(month, year);
            }
        } else if (day > daysOfMonth(month, year)) {
#ifdef PRINT
            std::clog << "A date with a day above the max days of the month is assumed to mean the appropriate day n months later.\n";
#endif
            while (day > daysOfMonth(month, year)) {
                day -= daysOfMonth(month, year);
                month += 1;
                //FIX: Remove code duplication
                if (month > 12) {
                    year += month / 12;
                    month = month % 12;
                    if (month == 0) {
                        month = 12;
                        year -= 1;
                    }
                } else if (month < 1) {
                    while (month < 1) {
                        month += 12;
                        year -= 1;
                    }
                }
            }
        }

        this->day = day;
        this->month = month;
        this->year = year;
    }

    Date Date::today() {
        return Date{};
    }

    int Date::daysOfMonth(int month, int year) {
        int days = 0;
        switch (month) {
            case 2:
                days += Date::isLeapYear(year) ? 29 : 28;
                break;
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                days += 1;
            case 4:
            case 6:
            case 9:
            case 11:
                days += 30;
                break;
            default:
                break;
        }
        return days;
    }

    bool Date::isLeapYear(int year) {
        if (year % 4 == 0) {
            if (year % 100 == 0) {
                return year % 400 == 0;
            } else {
                return true;
            }
        } else {
            return false;
        }
    }

    int Date::currentYear() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        return ltm->tm_year + 1900;
    }

    int Date::currentMonth() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        return ltm->tm_mon + 1;
    }

    int Date::currentDay() {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        return ltm->tm_mday;
    }

    void Date::getString(char (&str)[11]) const {
        sprintf(str, "%04d-%02d-%02d", getYear(), getMonth(), getDay());
    }

    Date::Date(const char str[11]) {
        char s_year[5];
        strncpy(s_year, str + 0, 4);
        s_year[4] = '\0';
        char s_month[3];
        strncpy(s_month, str + 5, 2);
        s_month[2] = '\0';
        char s_day[3];
        strncpy(s_day, str + 8, 2);
        s_day[2] = '\0';
        year = atoi(s_year);
        month = atoi(s_month);
        day = atoi(s_day);
    }

    Date::Date() {
        year = currentYear();
        month = currentMonth();
        day = currentDay();
    }

    Date Date::fromString(const char str[11]) {
        return {str};
    }

    int Date::daysBetween(const Date &start, const Date &end) {
        return start.daysBetween(end);
    }

    int Date::daysSince1900(const Date &date) {
        return date.daysSince1900();
    }

    int Date::daysSince1900() const {
        int days = 0;
        for (int i = 1900; i < getYear(); i++) {
            days += Date::isLeapYear(i) ? 366 : 365;
        }
        for (int i = 1; i < getMonth(); i++) {
            days += Date::daysOfMonth(i, getYear());
        }
        days += day;
        return days;
    }

    int Date::daysBetween(const Date &date) const {
        return std::abs(daysSince1900(date) - daysSince1900()) + 1;
    }

    std::ostream &operator<<(std::ostream &out, const Date &date) {
        char str[11];
        date.getString(str);

        out << str;

        return out;
    }

    static bool isDash(std::istream &in) {
        return in.get() == '-';
    }

    std::istream &operator>>(std::istream &in, Date &date) {

        int year;
        int month;
        int day;

        in >> year;

        if (!isDash(in)) {
            in.setstate(std::ios::failbit);
            return in;
        }

        in >> month;

        if (!isDash(in)) {
            in.setstate(std::ios::failbit);
            return in;
        }

        in >> day;

        date.setYear(year);
        date.setMonth(month);
        date.setDay(day);

        return in;
    }

}
