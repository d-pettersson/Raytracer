#include "tuple.h"

#include <cmath>

namespace raytracer {

Tuple::Tuple(double xx, double yy, double zz, double ww)
        :x{xx}, y{yy}, z{zz}, w{ww}
{
}

Tuple::Tuple()
        :x{0.0f}, y{0.0f}, z{0.0f}, w{0.0f}
{
}

//----------------------------------------------------------------

Point::Point(double x, double y, double z)
    : Tuple(x, y, z, 1.0f)
{
}

Point::Point()
    : Tuple(0.0f, 0.0f, 0.0f, 1.0f)
{
}

//----------------------------------------------------------------

Vector::Vector(double x, double y, double z)
    : Tuple(x, y, z, 0.0f)
{
}

Vector::Vector()
    : Tuple(0.0f, 0.0f, 0.0f, 0.0f)
{
}

//----------------------------------------------------------------

Color::Color(double r, double g, double b)
    : Tuple(r, g, b, 0.0f)
{
    this->r = x;
    this->g = y;
    this->b = z;
}

Color::Color()
    : Tuple()
{
}

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

//bool isEqual(const Tuple &t1, const Tuple &t2) {
//    const double epsilon = 0.00001;
//    auto * difference = new Tuple();
//    * difference = t1 - t2;
//    return tupleAbs(difference) < epsilon;
//}

//bool isEqual(const Tuple& t1, const Tuple& t2) {
//    return t1.x == t2.x && t1.y == t2.y && t1.z == t2.z && t1.w == t2.w;
//}

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

// Point operator
std::ostream& operator<<(std::ostream& out, const Point& p1) {
    out << '[' << p1.x << ", " << p1.y << ", " << p1.z << ']';
    return out;
}

// Tuple operators
bool operator<(const Tuple& t1, const Tuple& t2) {
    return t1.x < t2.x && t1.y < t2.y && t1.z < t2.z && t1.w < t2.w;
}

bool operator<(const Tuple& t1, const double& d1) {
    return t1.x < d1 && t1.y < d1 && t1.z < d1 && t1.w < d1;
}

bool operator==(const Tuple& t1, const Tuple& t2) {
    auto * difference = new Tuple();
    * difference = t1 - t2;
    return tupleAbs(difference) < EPSILON;
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

bool operator==(const Color& c1, const Color& c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}

bool operator!=(const Color& c1, const Color& c2) {
    return c1.r != c2.r || c1.g != c2.g || c1.b != c2.b;
}

std::ostream& operator<<(std::ostream& out, const Color& c1) {
    out << '[' << c1.r << ", " << c1.g << ", " << c1.b << ']';
    return out;
}

} // namespace raytracer

