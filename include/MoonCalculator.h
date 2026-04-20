#include <string>
#include "Array.h"
#include "Date.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "MoonCalculateException.h"
struct MoonResponse
{
    Date rise;
    Date set;
    Date culmination;
};
struct MoonRow
{
    Date date;
    std::string hms;
    double el;

    MoonRow() : el(0.0) {}

    MoonRow(const Date &currentDate, const std::string &currentHms, double currentEl)
        : date(currentDate), hms(currentHms), el(currentEl) {}

    friend std::ostream &operator<<(std::ostream &out, const MoonRow &row)
    {
        out << row.date.getDate() << " | " << row.hms << " | Elevation: " << row.el << endl;
        return out;
    }
};

class MoonCalculator
{
private:
    Array<MoonRow> moonRows;

public:
    MoonResponse showMoonPhases(const Date &date);
    bool loadFromFile(const Date &date);
};