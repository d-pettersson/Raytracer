#ifndef RTC_SPHERE_H
#define RTC_SPHERE_H

#include "shape.h"

namespace raytracer {
class Sphere : public Shape {
    public:
        Sphere();

        void intersect(const Ray &ray, std::vector<Intersection>& xs) const override;

        Vector getNormal(Point worldPoint) const override;
    };

    bool operator==(const Sphere& s1, const Sphere& s2);
}

#endif //RTC_SPHERE_H
