#include "../include/Date.h"
bool Date::isLeapYear(const int &year) const
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
bool Date::isValidDate(const int &year, const int &month, const int &day) const
{
    if (month < 1 || month > 12 || year < 1582)
    {
        return false;
    }
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
    {
        return day >= 1 && day <= 29;
    }
    return day >= 1 && day <= daysInMonth[month - 1];
}
bool Date::isValidTime(const int &hour, const int &minute, const int &second) const
{
    bool isValidHour = hour >= 0 && hour < 24;
    bool isValidMinute = minute >= 0 && minute < 60;
    bool isValidSecond = second >= 0 && second < 60;
    return isValidHour && isValidMinute && isValidSecond;
}
Date::Date(int y, int m, int d, int h, int min, int sec)
    : year(y), month(m), day(d), hour(h), minute(min), second(sec)
{
    if (!isValidDate(y, m, d) || !isValidTime(h, m, sec))
    {
        throw DateException();
    }
}
Date::Date()
{
    *this = Date(2020, 11, 30, 23, 34, 34);
}
Date::Date(const string &dateStr)
{
    int y = 0, m = 0, d = 0, h = 0, min = 0, sec = 0;
    int count = 0;
    if (dateStr.length() == 17 && dateStr[10] == 'T')
    {
        count = sscanf(dateStr.c_str(), "%d-%d-%dT%2d%2d%2d", &y, &m, &d, &h, &min, &sec);
    }

    else if (dateStr.length() == 15 && dateStr[8] == 'T')
    {
        count = sscanf(dateStr.c_str(), "%4d%2d%2dT%2d%2d%2d", &y, &m, &d, &h, &min, &sec);
    }

    else if (dateStr.length() == 8)
    {
        count = sscanf(dateStr.c_str(), "%4d%2d%2d", &y, &m, &d);
    }

    else if (strchr(dateStr.c_str(), '-'))
    {
        if (strchr(dateStr.c_str(), ':'))
        {
            count = sscanf(dateStr.c_str(), "%d-%d-%dT%d:%d:%d", &y, &m, &d, &h, &min, &sec);
        }
        else
        {
            count = sscanf(dateStr.c_str(), "%d-%d-%d", &y, &m, &d);
        }
    }

    if (count < 3)
    {
        throw DateException();
    }

    *this = Date(y, m, d, h, min, sec);
}
string Date::getFullDate() const
{
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02dT%02d:%02d:%02d",
             year, month, day, hour, minute, second);

    return string(buffer);
}
string Date::getDate() const
{
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d",
             year, month, day);

    return string(buffer);
}
double Date::toJulianDay() const
{
    int y = year;
    int m = month;
    double d = day;

    if (m <= 2)
    {
        y -= 1;
        m += 12;
    }

    int a = y / 100;
    int b = 2 - a + (a / 4);

    double jd = int(365.25 * (y + 4716)) + int(30.6001 * (m + 1)) + d + b - 1524.5;

    double fraction = (hour * 3600.0 + minute * 60.0 + second) / 86400.0;

    return jd + fraction;
}
int Date::getDayOfWeek() const
{
    long jdn = (long)(toJulianDay() + 0.5);
    return (jdn % 7) + 1;
}
TimeDiff Date::diffInDay(const Date &anotherDate) const
{
    double jdn1 = this->toJulianDay();
    double jdn2 = anotherDate.toJulianDay();
    double diffJdn = jdn1 - jdn2 > 0 ? jdn1 - jdn2 : jdn2 - jdn1;
    int fullDays = (int)diffJdn;
    long totalSeconds = (long)((diffJdn - fullDays) * 86400 + 0.5);
    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;
    return {fullDays, hours, minutes, seconds};
}
Date Date::calculateEaster(int year)
{
    int a = year % 19;
    int b = year % 4;
    int c = year % 7;
    int d = (19 * a + 15) % 30;
    int e = (2 * b + 4 * c + 6 * d + 6) % 7;
    int f = d + e;
    char buffer[11];
    if (f <= 26)
    {
        int day = f + 4;
        snprintf(buffer, sizeof(buffer), "%04d-04-%02d", year, day);
    }
    else
    {
        int day = 26 - f;
        snprintf(buffer, sizeof(buffer), "%04d-04-%02d", year, day);
    }
    return Date(buffer);
}
int Date::getYear() const
{
    return this->year;
}
int Date::getMonth() const
{
    return this->month;
}
int Date::getDay() const
{
    return this->day;
}
bool Date::operator==(const Date &anotherDate) const
{
    return this->year == anotherDate.year && this->month == anotherDate.month && this->day == anotherDate.day;
}