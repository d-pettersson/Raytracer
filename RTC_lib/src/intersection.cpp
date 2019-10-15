#include "include/intersection.h"
#include "include/ray.h"
#include "include/shape.h"

#include <utility>

namespace raytracer {

Intersection::Intersection()
    : distance(), shape()
{
}

Intersection::Intersection(double d, std::shared_ptr<Shape const> s)
    : distance(d), shape(std::move(s))
{
}

std::shared_ptr<Shape const> Intersection::getObject() {
    return shape;
}

double Intersection::getDistance() {
    return distance;
}



Intersection hit(std::vector<Intersection>const &xs) {
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

IntersectionData Intersection::prepareComputations(const Ray &ray) {
    auto * intersectionData = new IntersectionData();
    intersectionData->distance = this->getDistance();
    intersectionData->object = this->getObject();

    intersectionData->point = ray.position(intersectionData->distance);
    intersectionData->eye = -ray.getDirection();
    intersectionData->normal = intersectionData->object->getNormal(intersectionData->point);

    if (dot(intersectionData->normal, intersectionData->eye) < 0) {
        intersectionData->inside = true;
        intersectionData->normal = -intersectionData->normal;
    } else {
        intersectionData->inside = false;
    }
    intersectionData->overPoint = intersectionData->point + intersectionData->normal * EPSILON;
    intersectionData->reflect = reflect(ray.getDirection(), intersectionData->normal);
    return * intersectionData;
}


} // namespace raytracer
