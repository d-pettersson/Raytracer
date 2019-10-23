#include "include/ray.h"

#include <utility>

namespace raytracer {
Ray::Ray()
{
}

Ray::Ray(const raytracer::Point& _origin, const raytracer::Vector& _direction)
        : origin(_origin), direction(_direction)
{
}


void Ray::setDirection(const Vector& vector) {
    direction = vector;
}

Vector Ray::getDirection() const {
    return (* this).direction;
}

Vector& Ray::getDirection() {
    return (* this).direction;
}

void Ray::setOrigin(const Point& point) {
    origin = point;
}

Point Ray::getOrigin() const {
    return (* this).origin;
}

Point& Ray::getOrigin() {
    return (* this).origin;
}

Point Ray::position(const double& t) const {
    return (* this).origin + (* this).direction * t;
}

Ray transform(const Ray& ray, Transform& t) {
    return Ray(t * ray.getOrigin() , t * ray.getDirection());
}

} // namespace raytracer

