#ifndef RTC_UTILS_H
#define RTC_UTILS_H

#include <vector>

namespace raytracer {
struct Gen{
    float next() {
        counter++;
        if (counter < 0) { counter = 0; }
        else { counter > this->sequence.size() - 1 ? counter = 0 : counter; }
        return this->sequence[counter];
    };

    int counter = -1;
    std::vector<float> sequence;
};

}

#endif //RTC_UTILS_H
