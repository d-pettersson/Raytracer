#ifndef RTC_LIGHT_H
#define RTC_LIGHT_H

#include "tuple.h"

namespace raytracer{
class Light {
public:
    Light();
    Light(const Point &position, const Color &intensity);

    void setPointLight(const Point &position, const Color &intensity);

    Color intensity;
    Point position;

};
}



#endif //RTC_LIGHT_H
