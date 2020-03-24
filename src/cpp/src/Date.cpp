//
// Created by Kalelzar on 24/03/2020.
//

#include "Date.hpp"
#include <ctime>
#include <iostream>
namespace Hotel {
    Date::Date(int year, int month, int day) {
        if (month > 12) {
#ifdef PRINT
            std::clog << "A date with a month above 12 is assumed to mean the appropriate month n years later.\n";
#endif
            year += month / 12;
            month = month % 12;
            if(month == 0) {
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
            while(day < 1){
                month-=1;

                //FIX: Remove code duplication
                if (month > 12) {
                    year += month / 12;
                    month = month % 12;
                    if(month == 0) {
                        month = 12;
                        year -= 1;
                    }
                } else if (month < 1) {
                    while (month < 1) {
                        month += 12;
                        year -= 1;
                    }
                }

                day+=daysOfMonth(month, year);
            }
        }else if(day > daysOfMonth(month, year)){
#ifdef PRINT
            std::clog << "A date with a day above the max days of the month is assumed to mean the appropriate day n months later.\n";
#endif
            while(day > daysOfMonth(month, year)){
                day-=daysOfMonth(month, year);
                month+=1;
                //FIX: Remove code duplication
                if (month > 12) {
                    year += month / 12;
                    month = month % 12;
                    if(month == 0) {
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
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);

        return {ltm->tm_year, ltm->tm_mon, ltm->tm_mday};
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
        if(year % 4 == 0){
            if(year % 100 == 0){
                return year % 400 == 0;
            }else{
                return true;
            }
        }else{
            return false;
        }
    }

}