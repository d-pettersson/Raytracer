#ifndef RTC_COMMON_H
#define RTC_COMMON_H

#include "tuple.h"

#include <iostream>
#include <functional>
#include <map>

bool endsWith(std::string const& value, std::string const& ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

template <typename R, typename... Args>
std::function<R (Args...)> memo(R (*fn)(Args...)) {
    std::map<std::tuple<Args...>, R> table;
    return [fn, table](Args... args) mutable -> R {
        auto argt = std::make_tuple(args...);
        auto memoized = table.find(argt);
        if(memoized == table.end()) {
            auto result = fn(args...);
            table[argt] = result;
            return result;
        } else {
            return memoized->second;
        }
    };
}

raytracer::Color black = raytracer::Color(0.0, 0.0, 0.0);
raytracer::Color white = raytracer::Color(1.0, 1.0, 1.0);
#endif //RTC_COMMON_H
