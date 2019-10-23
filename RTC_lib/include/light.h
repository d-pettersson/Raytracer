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
    Light(const Point &_position, const Color &_intensity);

    void setPointLight(const Point &_position, const Color &_intensity);
//    void setAreaLight(const Point &corner, const Vector &fullUVec, const int &uSteps, const Vector &fullVVec, const int &vSteps, const Color &intensity);
//
//    Point pointOnLight(const double &u, const double &v) const;
//    float intensityAt(const Point &point, const World &world);

    Color intensity;
    Point position;

    Point corner;
    Vector uVec;
    int uSteps;
    Vector vVec;
    int vSteps;
    int samples;

    bool operator==(const Light &_light) const;
    bool operator!=(const Light &_light) const;
};

std::ostream& operator<<(std::ostream& out, const Light &_light);

}



#endif //RTC_LIGHT_H
