#ifndef OOPPROJECT_DATERANGE_HPP
#define OOPPROJECT_DATERANGE_HPP

#include "Date.hpp"
namespace Hotel{
    struct DateRange{
        Date from;
        Date to;

        friend std::ostream &operator<<(std::ostream &out, const DateRange &r){
            return out<<r.from<<" to "<<r.to;
        }

        int operator-(DateRange const& r) const {
           return (from - r.to);
        }

        bool operator==(DateRange const& r) const{
            return from==r.from && to == r.to;
        }

        bool operator==(Date const& d) const {
            return from == d || to == d;
        }

        bool operator!=(DateRange const& r) const {
            return !(*this==r);
        }
        bool operator!=(Date const& d) const {
            return !(*this==d);
        }

        bool operator>(DateRange const& r) const {
            return from > r.to;
        }

        bool operator<(DateRange const& r) const {
            return to < r.from;
        }

        bool operator>=(DateRange const& r) const {
            return from >= r.from;
        }

        bool operator<=(DateRange const& r) const {
            return to <= r.to;
        }

        bool operator>(Date const& d) const {
            return from > d;
        }

        bool operator<(Date const& d) const {
            return to < d;
        }

        bool operator>=(Date const& d) const {
            //std::cout<<"Is "<<*this<<" >= " << d <<": " << (to >= d)<<std::endl;
            return to >= d;
        }

        bool operator<=(Date const& d) const {
            return from <= d;
        }
    };
}

#endif //OOPPROJECT_DATERANGE_HPP
