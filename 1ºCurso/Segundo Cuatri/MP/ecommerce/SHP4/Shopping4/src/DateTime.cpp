/**
 * @file DateTime.cpp
 * @author MP-Team DECSAI
 * @note To be implemented by students 
 * 
 */
#include <string>
#include <iostream>
#include <sstream>
#include "DateTime.h"
using namespace std;

/**
 * @brief auxiliar function to check if the date and the time are in correct format, taking into account, leap year etc.
 * @param year input
 * @param month input
 * @param day input
 * @param hour input
 * @param min input
 * @param sec input
 * @return true if is correct, else return false
 */
bool isCorrect(int year, int month, int day, int hour, int min, int sec);
/**
 * @brief split the first field in 6 components of the data time.
 * Please consider using string::substr(int, int)[https://en.cppreference.com/w/cpp/string/basic_string/substr] to cut the line
 * into the appropriate substrings and then convert it into integer values with 
 * the function stoi(string) [https://en.cppreference.com/w/cpp/string/basic_string/stol]
 * ~~~~
 *      YYYY-MM-dd hh:mm:ss UTC 
 *      +----+----+----+----+----+ 
 *      |    |    |    |    |    |
 *      0    5    10   15   20   25
 * ~~~~
 *  * @param line input string
 * @param y output int
 * @param m output int
 * @param d output int
 * @param h output int
 * @param mn output int
 * @param s output int
 */
void split(const std::string& line, int &y, int & m, int & d, int & h, int &mn, int &s);

DateTime::DateTime() {
    initDefault();
}

void DateTime::initDefault() {
    set(DATETIME_DEFAULT);
}

bool isCorrect(int year, int month, int day, int hour, int min, int sec) {

    bool ok;
    int lastDay = 31; // length of the month by default
    if (month == 4 || month == 6 || month == 9 || month == 11)
        lastDay = 30;
    else if (month == 2) { // February
        lastDay = 28;
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) // leap years
            lastDay = 29;
    }
    ok = (month >=1 && month <=12) && (day > 0 && day <= lastDay) && (hour >= 0 && hour <24) && (min >= 0 && min < 60) && (sec >= 0 && sec < 60);
    return ok;
}

void split(const std::string& line, int &y, int & m, int & d, int & h, int &mn, int &s) {
    try {
        y = stoi(line.substr(0, 4));
        m = stoi(line.substr(5, 2));
        d = stoi(line.substr(8, 2));
        h = stoi(line.substr(11, 2));
        mn = stoi(line.substr(14, 2));
        s = stoi(line.substr(17, 2));
    } catch (const std::invalid_argument& e) {
        split(DATETIME_DEFAULT, y, m, d, h, m, s);
    }
}

void DateTime::set(const std::string & line) {
    int year, month, day, hour, min, sec;
    split(line, year, month, day, hour, min, sec);
    if (isCorrect(year, month, day, hour, min, sec)) {
        _year = year;
        _month = month;
        _day = day;
        _hour = hour;
        _min = min;
        _sec = sec;
    } else
        initDefault();
}

DateTime::DateTime(const string & line) {
    set(line);
}

int DateTime::year() const {
    return _year;
}

int DateTime::month() const {
    return _month;
}

int DateTime::day() const {
    return _day;
}

int DateTime::hour() const {
    return _hour;
}

int DateTime::min() const {
    return _min;
}

int DateTime::sec() const {
    return _sec;
}

string DateTime::to_string() const {
    char local[64];
    sprintf(local, "%04i-%02i-%02i %02i:%02i:%02i UTC", _year, _month, _day, _hour, _min, _sec);
    return local;
}

bool DateTime::isBefore(const DateTime & one) const {
    return to_string() < one.to_string();
}

bool DateTime::sameDay(const DateTime &other) const {
    return (this->_year) == other._year && (this->_month == other._month) && (this->_day == other._day);
}

int DateTime::weekDay() const {
    int a = (14 - _month) / 12;
    int y = _year - a;
    int m = _month + 12 * a - 2;
    int wDay;
    wDay = (_day + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
    return wDay;
}

DateTime & DateTime::operator=(const DateTime & one){
    _year = one._year;
    _month = one._month;
    _day = one._day;
    _hour = one._hour;
    _min = one._min;
    _sec = one._sec;
    
    return *this;
}