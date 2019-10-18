#include "include/plane.h"

#include <cmath>

namespace raytracer {

Plane::Plane()
    : Shape()
{
}

Plane::~Plane() = default;


void Plane::createGlass() {
    this->material.transparency = 1.0;
    this->material.refractiveIndex = 1.5;
}

void Plane::intersect(const Ray &ray, std::vector<Intersection> &xs) const {
    if (std::abs(ray.getDirection().y) < EPSILON) {
        return;
    }

    double distance = -ray.getOrigin().y / ray.getDirection().y;

    xs.emplace_back(Intersection(distance,shared_from_this()));
}

Vector Plane::getNormal(Point worldPoint) const {
    return Vector(0, 1, 0);
}



} // namespace raytracer