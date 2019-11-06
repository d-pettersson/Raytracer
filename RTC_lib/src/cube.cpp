#include "include/cube.h"

#include <cmath>

namespace raytracer {

Cube::Cube()
        : Shape()
{
}

Cube::~Cube() = default;

//void Cube::intersect(const Ray& ray, std::vector<Intersection>& xs) const {
//    std::pair<double, double> distX = this->checkAxis(ray.getOrigin().x_, ray.getDirection().x_);
//    std::pair<double, double> distY = this->checkAxis(ray.getOrigin().y_, ray.getDirection().y_);
//    std::pair<double, double> distZ = this->checkAxis(ray.getOrigin().z_, ray.getDirection().z_);
//
//    std::initializer_list<double> listDistMin = {distX.first, distY.first, distZ.first};
//    std::initializer_list<double> listDistMax = {distX.second, distY.second, distZ.second};
//
//    double tMin = max(listDistMin);
//    double tMax = min(listDistMax);
//
//    xs.emplace_back(Intersection(tMin, shared_from_this()));
//    xs.emplace_back(Intersection(tMax, shared_from_this()));
//}

Vector Cube::getNormal(Point worldPoint) const {
    Point objectPoint = inverse(this->getTransform()) * worldPoint;
    Vector objectNormal = objectPoint - Point(0, 0, 0);
    Vector worldNormal = transpose(inverse(this->getTransform())) * objectNormal;
    worldNormal.w_ = 0;
    return normalize(worldNormal);
}

void Cube::createGlass() {
    this->material.transparency = 1.0;
    this->material.refractiveIndex = 1.5;
}

//std::pair<double, double> Cube::checkAxis(const Point &origin, const Vector &direction) {
//    auto tMinNumerator = (-1.0 - origin);
//    return std::p;
//}

    bool operator==(const Cube& c1, const Cube& c2) {
    return typeid(c1) == typeid(c2);
}

bool operator!=(const Cube& c1, const Cube& c2) {
    return !(c1 == c2);
}

} // namespace raytracer

