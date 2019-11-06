#ifndef RTC_SPHERE_H
#define RTC_SPHERE_H

#include "shape.h"

namespace raytracer {
class Sphere : public Shape {
    public:
        Sphere();
        ~Sphere() override;

        void createGlass() override;

        void intersect(const Ray &ray, std::vector<Intersection>& xs) const override;
        Tuple getNormal(Tuple worldPoint) const override;
    };

    bool operator==(const Sphere& s1, const Sphere& s2);
    bool operator!=(const Sphere& s1, const Sphere& s2);
}

#endif //RTC_SPHERE_H
