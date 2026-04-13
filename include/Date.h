#pragma once
#include "DateException.h"
#include <string>
#include <cstdio>
using namespace std;
struct TimeDiff
{
    int days;
    int hours;
    int minutes;
    int seconds;
};
class Date
{
private:
    int year, month, day;
    int hour, minute, second;
    bool isValidDate(const int &year, const int &month, const int &day) const;
    bool isLeapYear(const int &year) const;
    bool isValidTime(const int &hour, const int &minute, const int &second) const;
    double toJulianDay() const;

public:
    Date(int y, int m, int d, int h, int min, int sec);
    Date(const string &date);
    Date();
    string getDate() const;
    string getFullDate() const;
    bool operator==(const Date &anotherDate) const;
    int getDayOfWeek() const;
    TimeDiff diffInDay(const Date &other) const;
    static Date calculateEaster(int year);
    int getYear() const;
    int getMonth() const;
    int getDay() const;
};