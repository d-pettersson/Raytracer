//
// Created by David P on 06.09.19.
//

#include "Tuple.h"
#include <cmath>

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

bool isEqual(Tuple t1, Tuple t2) {
    const double epsilon = 0.00001;
    return tupleAbs(t1 - t2) < epsilon;
}

Tuple createPoint(double x, double y, double z) {
    return {x, y, z, 1.0f};
}

Tuple createVector(double x, double y, double z) {
    return {x, y, z, 0.0f};
}

Tuple tupleAbs(Tuple t1) {
    return {abs(t1.x), abs(t1.y), abs(t1.z), abs(t1.w)};
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

Tuple operator+(const Tuple& t1, const Tuple& t2) {
    return {t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w};
}

Tuple operator-(const Tuple& t1, const Tuple& t2) {
    return {t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w};
}
