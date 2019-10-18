#include "include/sphere.h"

#include <cmath>

namespace raytracer {

Sphere::Sphere()
    : Shape()
{
}

Sphere::~Sphere() = default;

void Sphere::intersect(const Ray& ray, std::vector<Intersection>& xs) const {
    Transform sphereTransform = this->getTransform();
    Transform invertedTransform = inverse(sphereTransform);
    raytracer::Ray newRay = transform(ray, invertedTransform);

    raytracer::Point center = raytracer::Point(0, 0, 0);
    raytracer::Vector sphereToRay = newRay.getOrigin() - center;

    double a = dot(newRay.getDirection(), newRay.getDirection());
    double b = 2 * dot(newRay.getDirection(), sphereToRay);
    double c = dot(sphereToRay, sphereToRay) - 1;

    double discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant > 0) {
        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);
        xs.emplace_back(t1, shared_from_this());
        xs.emplace_back(t2, shared_from_this());
    }
}

Vector Sphere::getNormal(Point worldPoint) const {
    raytracer::Point objectPoint = inverse(this->getTransform()) * worldPoint;
    raytracer::Vector objectNormal = objectPoint - Point(0, 0, 0);
    raytracer::Vector worldNormal = transpose(inverse(this->getTransform())) * objectNormal;
    worldNormal.w = 0;
    return normalize(worldNormal);
}

void Sphere::createGlass() {
    this->material.transparency = 1.0;
    this->material.refractiveIndex = 1.5;
}

bool operator==(const Sphere& s1, const Sphere& s2) {
    return typeid(s1) == typeid(s2);
}

} // namespace raytracer

