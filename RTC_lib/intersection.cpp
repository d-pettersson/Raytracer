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

Intersection hit(std::vector<Intersection>const& xs) {
    for (auto i : xs) {
        if (i.getDistance() > 0)
            return i;
    }
    return Intersection(0.f, nullptr);
}


bool Intersection::operator<(const raytracer::Intersection &rhs) const {
    return distance < rhs.distance;
}

bool Intersection::operator>(const raytracer::Intersection &rhs) const {
    return rhs < *this;
}

bool Intersection::operator<=(const raytracer::Intersection &rhs) const {
    return !(rhs < *this);
}

bool Intersection::operator>=(const raytracer::Intersection &rhs) const {
    return !(*this < rhs);
}

} // namespace raytracer
