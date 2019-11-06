#ifndef RTC_CUBE_H
#define RTC_CUBE_H

#include "shape.h"

namespace raytracer {
    class Cube : public Shape {
    public:
        Cube();
        ~Cube() override;

        void createGlass() override;

        void intersect(const Ray &ray, std::vector<Intersection>& xs) const override;
        Vector getNormal(Point worldPoint) const override;

        std::pair<double, double> checkAxis(const Point &origin, const Vector &direction);
    };

    bool operator==(const Cube& s1, const Cube& s2);
    bool operator!=(const Cube& c1, const Cube& c2);
}

#endif //RTC_SPHERE_H
