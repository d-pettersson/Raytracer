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
    if (std::abs(ray.getDirection().y_) < EPSILON) {
        return;
    }

    double distance = -ray.getOrigin().y_ / ray.getDirection().y_;

    xs.emplace_back(Intersection(distance,shared_from_this()));
}

Tuple Plane::getNormal(Tuple worldPoint) const {
    return createVector(0, 1, 0);
}



} // namespace raytracer