
#include "date.h"


Date ParseDate(istream& is) {
    string a, b, c;
    getline(is, a, '-');
    getline(is, b, '-');
    is >> c;

    return {atoi(a.c_str()), atoi(b.c_str()), atoi(c.c_str())};
}



ostream& operator<<(ostream& os, const Date& date) {
    os << date.year / 1000 << date.year / 100 % 10 << date.year / 10 % 10 << date.year % 10 << "-"
    << date.month / 10 % 10 << date.month % 10 << "-" << date.day / 10 % 10 << date.day % 10;
    return os;
}



bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.year != rhs.year) {
        return lhs.year < rhs.year;
    }
    if (lhs.month != rhs.month) {
        return lhs.month < rhs.month;
    }
    return lhs.day < rhs.day;
}

bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Date& lhs, const Date& rhs) {
    return !(lhs <= rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}
