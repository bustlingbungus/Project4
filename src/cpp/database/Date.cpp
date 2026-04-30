#include "Date.hpp"



std::string Date::to_string(DateFormat format)
{
    std::string mo = std::to_string(month);
    while (mo.size() < 2) mo = '0' + mo;
    std::string dy = std::to_string(day);
    while (dy.size() < 2) dy = '0' + dy;
    std::string yr = std::to_string(year);
    while (yr.size() < 4) yr = '0' + yr;

    switch (format)
    {
        default:
        case DATEFORMAT_MMDDYYYY:
            return mo+"-"+dy+"-"+yr;
        case DATEFORMAT_YYYYMMDD:
            return yr+"-"+mo+"-"+dy;
    }
}