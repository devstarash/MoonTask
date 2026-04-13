#include "../include/MoonCalculator.h"
bool MoonCalculator::loadFromFile(const Date &date)
{
    int year = date.getYear();
    string fileName = "moon" + to_string(year) + ".dat";
    std::ifstream file("../Moon/" + fileName);
    if (!file.is_open())
    {
        return 0;
    }
    else
    {
        std::string line;
        getline(file, line);
        while (getline(file, line))
        {
            if (line.empty())
            {
                continue;
            }
            std::stringstream ss(line);
            std::string date, hms;
            double t, r, el;
            if (ss >> date >> hms >> t >> r >> el)
            {
                Date d(date);
                moonRows.insert(MoonRow(d, hms, el));
            }
        }
        return 1;
    }
}
MoonResponse MoonCalculator::showMoonPhases(const Date &date)
{
    bool result = loadFromFile(date);
    if (result == 0)
    {
        return {Date(), Date(), Date()};
    }
    else
    {
        Array<MoonRow> currentRows;
        for (int i = 0; i < moonRows.getSize(); i++)
        {
            if (moonRows[i].date == date)
            {
                currentRows.insert(moonRows[i]);
            }
        }
        double maxEl = -100.0;
        string timeTransit;
        string timeMoonrise;
        string timeMoonset;
        for (int i = 0; i < currentRows.getSize(); i++)
        {
            if (currentRows[i].el > maxEl)
            {
                maxEl = currentRows[i].el;
                timeTransit = currentRows[i].hms;
            }

            if (i < currentRows.getSize() - 1)
            {
                double currentEl = currentRows[i].el;
                double nextEl = currentRows[i + 1].el;

                if (currentEl < 0 && nextEl > 0)
                    timeMoonrise = currentRows[i + 1].hms;
                if (currentEl > 0 && nextEl < 0)
                    timeMoonset = currentRows[i + 1].hms;
            }
        }
        return {Date(date.getDate() + "T" + timeMoonrise), Date(date.getDate() + "T" + timeMoonset), Date(date.getDate() + "T" + timeTransit)};
    }
}