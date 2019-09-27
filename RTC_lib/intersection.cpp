#include "intersection.h"

namespace raytracer {

    Intersection::Intersection()
        : distance(), shape()
    {
    }

    Intersection::Intersection(double d, std::shared_ptr<Shape const> s)
        : distance(d), shape(s)
    {
    }

    std::shared_ptr<Shape const> Intersection::getObject() {
        return shape;
    }

    double Intersection::getDistance() {
        return distance;
    }
} // namespace raytracer
