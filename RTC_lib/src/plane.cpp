#include "include/plane.h"

#include <cmath>

namespace raytracer {

Plane::Plane()
    : Shape()
{
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