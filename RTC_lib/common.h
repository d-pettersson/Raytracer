#ifndef RTC_COMMON_H
#define RTC_COMMON_H

#include <iostream>

bool endsWith(std::string const& value, std::string const& ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

#endif //RTC_COMMON_H
