#include "include/intersection.h"
#include "include/ray.h"
#include "include/shape.h"

#include <utility>
#include <algorithm>

namespace raytracer {

Intersection::Intersection()
    : distance(), shape()
{
}

Intersection::Intersection(double d, std::shared_ptr<Shape const> s)
    : distance(d), shape(std::move(s))
{
}

std::shared_ptr<Shape const> Intersection::getObject() const {
    return shape;
}

double Intersection::getDistance() const {
    return distance;
}

Intersection hit(std::vector<Intersection>const &xs) {
    for (auto const &i : xs) {
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

IntersectionData Intersection::prepareComputations(const Ray &ray, const std::vector<Intersection> &xs) {
    IntersectionData intersectionData;
    intersectionData.distance = this->getDistance();
    intersectionData.object = this->getObject();

    intersectionData.point = ray.position(intersectionData.distance);
    intersectionData.eye = -ray.getDirection();
    intersectionData.normal = intersectionData.object->getNormal(intersectionData.point);

    if (dot(intersectionData.normal, intersectionData.eye) < 0) {
        intersectionData.inside = true;
        intersectionData.normal = -intersectionData.normal;
    } else {
        intersectionData.inside = false;
    }
    intersectionData.overPoint = intersectionData.point + intersectionData.normal * EPSILON;
    intersectionData.underPoint = intersectionData.point - intersectionData.normal * EPSILON;
    intersectionData.reflect = reflect(ray.getDirection(), intersectionData.normal);

    auto containers = std::vector<std::shared_ptr<Shape const> >();

    for (auto const &i : xs) {
        if (i == (* this)) {
            if (containers.empty()) {
                intersectionData.n1 = 1.0;
            } else {
                intersectionData.n1 = containers.back()->material.refractiveIndex;
            }
        }

        if (std::find(containers.begin(), containers.end(), i.getObject()) != containers.end()) {
            auto it = std::find(containers.begin(), containers.end(), i.getObject());
            int index = std::distance(containers.begin(), it);
            containers.erase(containers.begin() + index);
        } else {
            containers.emplace_back(i.getObject());
        }

        if (i == (* this)) {
            if (containers.empty()) {
                intersectionData.n2 = 1.0;
            } else {
                intersectionData.n2 = containers.back()->material.refractiveIndex;
            }
        }
    }

    return intersectionData;
}

bool Intersection::operator==(const Intersection &rhs) const {
    return distance == rhs.distance &&
           shape == rhs.shape;
}

bool Intersection::operator!=(const Intersection &rhs) const {
    return !(rhs == *this);
}


} // namespace raytracer
