#include "DateRange.hpp"

int Hotel::DateRange::operator-(Hotel::DateRange const &r) const {
    return (from - r.to);
}

bool Hotel::DateRange::operator==(Hotel::DateRange const &r) const {
    return from == r.from && to == r.to;
}

bool Hotel::DateRange::operator==(Hotel::Date const &d) const {
    return from == d || to == d;
}

bool Hotel::DateRange::operator!=(Hotel::DateRange const &r) const {
    return !(*this == r);
}

bool Hotel::DateRange::operator!=(Hotel::Date const &d) const {
    return !(*this == d);
}

bool Hotel::DateRange::operator>(Hotel::DateRange const &r) const {
    return from > r.to;
}

bool Hotel::DateRange::operator<(Hotel::DateRange const &r) const {
    return to < r.from;
}

bool Hotel::DateRange::operator>=(Hotel::DateRange const &r) const {
    return from >= r.from;
}

bool Hotel::DateRange::operator<=(Hotel::DateRange const &r) const {
    return to <= r.to;
}

bool Hotel::DateRange::operator>(Hotel::Date const &d) const {
    return from > d;
}

bool Hotel::DateRange::operator<(Hotel::Date const &d) const {
    return to < d;
}

bool Hotel::DateRange::operator>=(Hotel::Date const &d) const {
    return to >= d;
}

bool Hotel::DateRange::operator<=(Hotel::Date const &d) const {
    return from <= d;
}
