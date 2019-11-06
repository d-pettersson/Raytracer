#ifndef RTC_LIGHT_H
#define RTC_LIGHT_H

#include "tuple.h"
#include "utils.h"

#include <vector>

namespace raytracer{

class World;

class Light {
public:
    Light();
    Light(Tuple position, Color intensity);

    void setPointLight(const Tuple &position, const Color &intensity);
//    void setAreaLight(const Point &corner, const Vector &fullUVec, const int &uSteps, const Vector &fullVVec, const int &vSteps, const Color &intensity);
//
//    Point pointOnLight(const double &u, const double &v) const;
//    float intensityAt(const Point &point, const World &world);

    Color intensity_;
    Tuple position_;

    Tuple corner_;
    Tuple uVec_;
    int uSteps_;
    Tuple vVec_;
    int vSteps_;
    int samples_;

    bool operator==(const Light &rhs) const;
    bool operator!=(const Light &rhs) const;
};
}



#endif //RTC_LIGHT_H
