#ifndef OOPPROJECT_DATERANGE_HPP
#define OOPPROJECT_DATERANGE_HPP

#include "Date.hpp"

namespace Hotel {
    struct DateRange {
        Date from;
        Date to;

        friend std::ostream &operator<<(std::ostream &out, const DateRange &r) {
            return out << r.from << " to " << r.to;
        }

        /**
         * The difference between this DateRange and another
         * is equal to the difference between the start of this range
         * and the end of the other
         *
         * This means that it isn't a commutative operation
         * i.e a - b != b - a for all a, b
         *
         * @param r the other DateRange
         * @return the difference
         */
        int operator-(DateRange const &r) const ;

        /**
         * Two date ranges are equal when they start and end on the same dates
         * @param r the other DateRange
         * @return are the two date ranges equal
         */
        bool operator==(DateRange const &r) const ;

        /**
         * A DateRange is equal to a single Date
         * when it begins and ends on that date
         * @param d the date
         * @return are the DateRange and the Date equal
         */
        bool operator==(Date const &d) const ;

        /**
         * @see operator==
         * @param r the other DateRange
         * @return are the two date ranges different
         */
        bool operator!=(DateRange const &r) const ;

        /**
         * @see operator!=
         * @param d the date
         * @return are the date range and the date different
         */
        bool operator!=(Date const &d) const ;

        /**
         * One date range is greater than another
         * when it starts after the other ends
         * @param r the other range
         * @return is this range greater than the other
         */
        bool operator>(DateRange const &r) const ;

        /**
         * One date range is less than another
         * when is ends before the other begins
         * @param r the other range
         * @return is this range less than the other
         */
        bool operator<(DateRange const &r) const ;

        /**
         * One date range is greater than or equal to another
         * when it's start is greater than or equal to the start of the other
         *
         * Defined like this, the following is <strong>not</strong> always true <br>
         * <code> (a == b) || (a > b) == a >= b </code>
         * @param r the other date range
         * @return is this range greater or equal to another
         */
        bool operator>=(DateRange const &r) const ;

        /**
         * One date range is less than or equal to another
         * when it's end is less than or equal to the end of the other
         *
         * Defined like this, the following is <strong>not</strong> always true <br>
         * <code> (a == b) || (a < b) == a <= b </code>
         * @param r the other date range
         * @return is this range greater or equal to another
         */
        bool operator<=(DateRange const &r) const ;

        /**
         * A date range is greater than a date
         * when it begins after the date
         * @param d the date
         * @return is this range greater than the date
         */
        bool operator>(Date const &d) const ;

        /**
         * A date range is less than a date
         * when it ends before the date
         * @param d the date
         * @return is this range less than the date
         */
        bool operator<(Date const &d) const ;

        /**
         * A date range is greater than or equal to a date
         * when it's end is greater than or equal to the date
         * @param d the date
         * @return is this range greater than or equal to the date
         */
        bool operator>=(Date const &d) const ;

        /**
         * A date range is less than or equal to a date
         * when it's start is less than or equal to the date
         * @param d the date
         * @return is this range less than or equal to the date
         */
        bool operator<=(Date const &d) const ;
    };
}

#endif //OOPPROJECT_DATERANGE_HPP
