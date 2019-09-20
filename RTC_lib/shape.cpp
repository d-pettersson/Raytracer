#include "shape.h"

#include <cmath>

namespace raytracer {

    Shape::Shape()
        : intersects(2)
    {
        id = ++nextId;
    }


    Sphere::Sphere()
            : Shape()
    {
    }

    int Shape::count() {
        return intersects.size();
    }

    double Shape::getIntersects(const int& index) {
        return intersects[index];
    }

    std::vector<double> Shape::intersect(const Ray& ray) {
        raytracer::Point center = raytracer::Point(0, 0, 0);
        raytracer::Vector sphereToRay = ray.getOrigin() - center;

        double a = dot(ray.getDirection(), ray.getDirection());
        double b = 2 * dot(ray.getDirection(), sphereToRay);
        double c = dot(sphereToRay, sphereToRay) - 1;

        double discriminant = pow(b, 2) - 4 * a * c;

        if (discriminant < 0) {
            (* this).intersects.clear();
        } else {
            double t1 = (-b - sqrt(discriminant)) / (2 * a);
            double t2 = (-b + sqrt(discriminant)) / (2 * a);
            (* this).intersects[0] = t1;
            (* this).intersects[1] = t2;
        }
        return (* this).intersects;
    }

    double& Shape::operator[](const int &index) {
        return (*this).intersects[index];
    }

    double Shape::operator[](const int &index) const {
        return (*this).intersects[index];
    }

    size_t Shape::nextId = 0;

    bool operator==(const Shape& s1, const Shape& s2) {
        return typeid(s1) == typeid(s2);
    }

} // namespace raytracer

