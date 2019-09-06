#include <cmath>

#include "Tuple.h"

namespace raytracer {

Tuple::Tuple(double xx, double yy, double zz, double ww)
        :x{xx}, y{yy}, z{zz}, w{ww}
{
}

Tuple::Tuple()
        :x{0.f}, y{0.f}, z{0.f}, w{0.f}
{
}

bool Tuple::isPoint() {
    return w == 1.0;
}

bool Tuple::isVector() {
    return w == 0.0;
}

bool isEqual(const Tuple &t1, const Tuple &t2) {
    const double epsilon = 0.00001;
    auto *difference = new Tuple();
    *difference = t1 - t2;
    return tupleAbs(difference) < epsilon;
}

Tuple createPoint(const double &x, const double &y, const double &z) {
    return {x, y, z, 1.0f};
}

Tuple createVector(const double &x, const double &y, const double &z) {
    return {x, y, z, 0.0f};
}

Tuple normalize(const Tuple& t1) {
    return {t1.x / magnitude(t1), t1.y / magnitude(t1), t1.z / magnitude(t1), t1.w / magnitude(t1)};
}

Tuple tupleAbs(Tuple *t1) {
    return {abs(t1->x), abs(t1->y), abs(t1->z), abs(t1->w)};
}

double magnitude(const Tuple& t1) {
    return sqrt(t1.x * t1.x + t1.y * t1.y + t1.z * t1.z + t1.w * t1.w);
}

double dot(const Tuple& t1, const Tuple& t2) {
    return t1.x * t2.x + t1.y * t2.y + t1.z * t2.z + t1.w * t2.w;
}

Tuple cross(const Tuple& t1, const Tuple& t2) {
    Tuple result = raytracer::createVector(
            t1.y * t2.z - t1.z * t2.y,
            t1.z * t2.x - t1.x * t2.z,
            t1.x * t2.y - t1.y * t2.x);
    return result;
}

bool operator<(const Tuple& t1, const Tuple& t2) {
    return t1.x < t2.x && t1.y < t2.y && t1.z < t2.z && t1.w < t2.w;
}

bool operator<(const Tuple& t1, const double& d1) {
    return t1.x < d1 && t1.y < d1 && t1.z < d1 && t1.w < d1;
}

bool operator==(const Tuple& t1, const Tuple& t2) {
    return t1.x == t2.x && t1.y == t2.y && t1.z == t2.z && t1.w == t2.w;
}

Tuple operator-(const Tuple& t1, const Tuple& t2) {
    return {t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w};
}

Tuple operator-(const Tuple &t1) {
    return {-t1.x, -t1.y, -t1.z, -t1.w};
}

Tuple operator+(const Tuple& t1, const Tuple& t2) {
    return {t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w};
}

Tuple operator*(const Tuple& t1, const double scalar) {
    return {t1.x * scalar, t1.y * scalar, t1.z * scalar, t1.w * scalar};
}

Tuple operator/(const Tuple& t1, const double scalar) {
    return {t1.x / scalar, t1.y / scalar, t1.z / scalar, t1.w / scalar};
}

} // namespace raytracer

