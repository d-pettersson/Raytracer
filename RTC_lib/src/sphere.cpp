#include "include/sphere.h"
//#include "include/common.h"

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
    Ray newRay = transform(ray, invertedTransform);

    Tuple center = createPoint(0, 0, 0);
    Tuple sphereToRay = newRay.getOrigin() - center;

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

Tuple Sphere::getNormal(Tuple worldPoint) const {
    Tuple objectPoint = inverse(this->getTransform()) * worldPoint;
    Tuple objectNormal = objectPoint - createPoint(0, 0, 0);
    Tuple worldNormal = transpose(inverse(this->getTransform())) * objectNormal;
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

bool operator!=(const Sphere& s1, const Sphere& s2) {
    return !(s1 == s2);
}

} // namespace raytracer

