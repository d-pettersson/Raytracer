#ifndef RTC_PLANE_H
#define RTC_PLANE_H

#include "shape.h"

namespace raytracer {
class Plane : public Shape {
    public:
        Plane();
        ~Plane() override;

        void createGlass() override;

        void intersect(const Ray &ray, std::vector<Intersection>& xs) const override;
        Tuple getNormal(Tuple worldPoint) const override;
};

}


#endif //RTC_PLANE_H
