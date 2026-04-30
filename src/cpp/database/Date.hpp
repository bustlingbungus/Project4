#pragma once

#include <string>

enum DateFormat
{
    DATEFORMAT_MMDDYYYY,
    DATEFORMAT_YYYYMMDD
};


struct Date
{
    int month;
    int day;
    int year;

    std::string to_string(DateFormat format = DATEFORMAT_MMDDYYYY);
};