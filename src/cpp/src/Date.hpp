//
// Created by Kalelzar on 24/03/2020.
//

#ifndef OOPPROJECT_DATE_HPP
#define OOPPROJECT_DATE_HPP
namespace Hotel {
/**
 * Stores a date and has some useful methods for working with dates
 */
    class Date {
    private:
        int year;
        int month;
        int day;
    public:
        /**
         * Constructs a date with the provided arguments
         * @param year the year
         * @param month the month
         * @param day the day
         */
        Date(int year, int month, int day);

        /**
         * Prints the date in the ISO 8601 format ( <year>-<month>-<day> )
         */
        void print() const;

        /**
         * Prints the date in the ISO 8601 format ( <year>-<month>-<day> ) and a newline
         */
        void println() const;

        /**
         * Returns the current date
         * @return the current date
         */
        static Date today();

        /**
         * Returns the amount of days in a month
         * @param month the month for which to check
         * @param year the year for which to check
         * @return the days in the provided month during the provided year.
         */
        static int daysOfMonth(int month, int year);

        /**
         * Checks if the provided year is a leap year.
         *
         * @param year the year which to check.
         * @return is the provided year a leap year.
         */
        static bool isLeapYear(int year);

        int getDay() const { return day; }

        int getMonth() const { return month; }

        int getYear() const { return year; }

    };

}
#endif //OOPPROJECT_DATE_HPP
