#ifndef RTC_PATTERNS_H
#define RTC_PATTERNS_H

#include "tuple.h"

namespace raytracer {
class Patterns {

public:
    Patterns(const Color &c1, const Color &c2);

private:
    Color c1;
    Color c2;
};
} // namespace raytracer



#endif //RTC_PATTERNS_H
