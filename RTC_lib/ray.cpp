#include "ray.h"

namespace raytracer {
Ray::Ray()
{
}

Ray::Ray(raytracer::Point ori, raytracer::Vector dir)
        : origin(ori), direction(dir)
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

Point Ray::position(const double& t) {
    return (* this).origin + (* this).direction * t;
}

Ray transform(const Ray& ray, Transform& t) {
    return Ray(t * ray.getOrigin() , t * ray.getDirection());
}

} // namespace raytracer

