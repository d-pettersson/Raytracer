#include "include/ray.h"

#include <utility>

namespace raytracer {
Ray::Ray() = default;

Ray::Ray(Tuple origin, Tuple direction)
        : origin_(origin), direction_(direction)
{
}


void Ray::setDirection(const Tuple &vector) {
    direction_ = vector;
}

Tuple Ray::getDirection() const {
    return (* this).direction_;
}

Tuple& Ray::getDirection() {
    return (* this).direction_;
}

void Ray::setOrigin(const Tuple &point) {
    origin_ = point;
}

Tuple Ray::getOrigin() const {
    return (* this).origin_;
}

Tuple& Ray::getOrigin() {
    return (* this).origin_;
}

Tuple Ray::position(const double& t) const {
    return (* this).origin_ + (* this).direction_ * t;
}

Ray transform(const Ray &ray, Transform &transform) {
    return Ray(transform * ray.getOrigin() , transform * ray.getDirection());
}

} // namespace raytracer

