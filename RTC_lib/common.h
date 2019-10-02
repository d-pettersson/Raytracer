#ifndef RTC_COMMON_H
#define RTC_COMMON_H

#include "tuple.h"

#include <iostream>

bool endsWith(std::string const& value, std::string const& ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

raytracer::Color black = raytracer::Color(0.0, 0.0, 0.0);

#endif //RTC_COMMON_H
