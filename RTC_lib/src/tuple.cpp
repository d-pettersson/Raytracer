#include "include/tuple.h"

#include <cmath>

namespace raytracer {

Tuple::Tuple(double x, double y, double z, double w)
        : x{x}, y{y}, z{z}, w{w}
{
}

Tuple::Tuple()
        : x{0.0}, y{0.0}, z{0.0}, w{0.0}
{
}

//----------------------------------------------------------------

Color::Color(double r, double g, double b)
    : Tuple(r, g, b, 0.0), r(x), g(y), b(z)
{
}

Color::Color()
    : Tuple(), r(), g(), b()
{
}

//----------------------------------------------------------------

double& Tuple::operator()(size_t index) {
    switch (index) {
        case (0):
            return x;
        case (1):
            return y;
        case (2):
            return z;
        case (3):
            return w;
        default:
            break;
    }
}

double Tuple::operator()(size_t index) const {
    switch (index) {
        case (0):
            return x;
        case (1):
            return y;
        case (2):
            return z;
        case (3):
            return w;
        default:
            break;
    }
}

bool Tuple::isPoint() {
    return w == 1.0;
}

bool Tuple::isVector() {
    return w == 0.0;
}

Tuple Tuple::operator-() {
    return {-x, -y, -z, -w};
}

Tuple createPoint(const double &x, const double &y, const double &z) {
    return {x, y, z, 1.0};
}

Tuple createVector(const double &x, const double &y, const double &z) {
    return {x, y, z, 0.0};
}

Tuple createColor(const double &r, const double &g, const double &b) {
    return {r, g, b, 0.0};
}

Tuple normalize(const Tuple &t) {
    return {t.x / magnitude(t), t.y / magnitude(t), t.z / magnitude(t), t.w / magnitude(t)};
}

Tuple abs(const Tuple &t) {
    return {fabs(t.x), fabs(t.y), fabs(t.z), fabs(t.w)};
}

double magnitude(const Tuple& v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}

double dot(const Tuple& v1, const Tuple& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

Tuple cross(const Tuple& v1, const Tuple& v2) {
    Tuple result = raytracer::createVector(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x);
    return result;
}

Tuple reflect(const Tuple &v, const Tuple &n) {
    return v - n * 2 * dot(v, n);
}

// Tuple operators
bool operator<(const Tuple& t1, const Tuple& t2) {
    return t1.x < t2.x && t1.y < t2.y && t1.z < t2.z && t1.w < t2.w;
}

bool operator<(const Tuple& t1, const double& d1) {
    return t1.x < d1 && t1.y < d1 && t1.z < d1 && t1.w < d1;
}

bool operator==(const Tuple& t1, const Tuple& t2) {
    auto difference = t1 - t2;
    return abs(difference) < EPSILON;
}

bool operator!=(const Tuple& t1, const Tuple& t2) {
    return !(t1 == t2);
}

Tuple operator-(const Tuple& t1, const Tuple& t2) {
    return {t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w};
}

Tuple operator-(const Tuple& t1) {
    return {-t1.x, -t1.y, -t1.z, -t1.w};
}

Tuple operator+(const Tuple& t1, const Tuple& t2) {
    return {t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w};
}

Tuple operator*(const Tuple& t1, const Tuple& t2) {
    return {t1.x * t2.x, t1.y * t2.y, t1.z * t2.z, t1.w * t2.w};
}

Tuple operator*(const Tuple& t1, const double& scalar) {
    return {t1.x * scalar, t1.y * scalar, t1.z * scalar, t1.w * scalar};
}

Tuple operator/(const Tuple& t1, const double& scalar) {
    return {t1.x / scalar, t1.y / scalar, t1.z / scalar, t1.w / scalar};
}

std::ostream& operator<<(std::ostream& out, const Tuple& t1) {
    out << '[' << t1.x << ", " << t1.y << ", " << t1.z << ", " << t1.w << ']';
    return out;
}

// Color operators
Color operator-(const Color& c1, const Color& c2) {
    return {c1.r - c2.r, c1.g - c2.g, c1.b - c2.b};
}

Color operator+(const Color& c1, const Color& c2) {
    return {c1.r + c2.r, c1.g + c2.g, c1.b + c2.b};
}

Color operator*(const Color& c1, const Color& c2) {
    return {c1.r * c2.r, c1.g * c2.g, c1.b * c2.b};
}

Color operator*(const Color& c1, const double& scalar) {
    return {c1.r * scalar, c1.g * scalar, c1.b * scalar};
}

Color operator/(const Color& c1, const double& scalar) {
    return {c1.x / scalar, c1.y / scalar, c1.z / scalar};
}

bool operator==(const Color& c1, const Color& c2) {
    auto difference = c1 - c2;
    return abs(difference) < EPSILON;
}

bool operator!=(const Color& c1, const Color& c2) {
    return !(c1 == c2);
}

std::ostream& operator<<(std::ostream& out, const Color& c1) {
    out << '[' << c1.r << ", " << c1.g << ", " << c1.b << ']';
    return out;
}

} // namespace raytracer

