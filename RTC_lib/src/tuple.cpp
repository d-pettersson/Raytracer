#include "include/tuple.h"

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

Point::Point(double xx, double yy, double zz)
    : Tuple{xx, yy, zz, 1.0f}
{
}

Point::Point()
    : Tuple()
{
}

//----------------------------------------------------------------

Vector::Vector(double xx, double yy, double zz)
    : Tuple{xx, yy, zz, 0.0f}
{
}

Vector::Vector()
    : Tuple()
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

Vector normalize(const Vector& v1) {
    return {v1.x / magnitude(v1), v1.y / magnitude(v1), v1.z / magnitude(v1)};
}

Tuple tupleAbs(Tuple *t1) {
    return {fabs(t1->x), fabs(t1->y), fabs(t1->z), fabs(t1->w)};
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

Vector cross(const Vector &v1, const Vector &v2) {
    return raytracer::Vector(v1.y * v2.z - v1.z * v2.y,
                             v1.z * v2.x - v1.x * v2.z,
                             v1.x * v2.y - v1.y * v2.x);
}


Vector reflect(const Vector& v, const Vector& n) {
    return v - n * 2 * dot(v, n);
}

// Point operator
std::ostream& operator<<(std::ostream& out, const Point& p1) {
    out << '[' << p1.x << ", " << p1.y << ", " << p1.z << ']';
    return out;
}

bool operator==(const Point &p1, const Point &p2) {
    auto * difference = new Vector();
    * difference = p1 - p2;
    return tupleAbs(difference) < EPSILON;
}

Point Point::operator-() {
    return {-(* this).x, -(* this).y, -(* this).z};
}

Point operator*(const Point& p1, const Point& p2) {
    return {p1.x * p2.x, p1.y * p2.y, p1.z * p2.z};
}

Point operator*(const Point& p1, const Vector& p2) {
    return {p1.x * p2.x, p1.y * p2.y, p1.z * p2.z};
}

Point operator*(const Point& p1, const double& scalar) {
    return {p1.x * scalar, p1.y * scalar, p1.z * scalar};
}

Point operator+(const Point& p1, const Point& p2) {
    return {p1.x + p2.x, p1.y + p2.y, p1.z + p2.z};
}

Point operator+(const Point& p1, const Vector& v2) {
    return {p1.x + v2.x, p1.y + v2.y, p1.z + v2.z};
}

Point operator-(const Point& p1, const Vector& v2) {
    return {p1.x - v2.x, p1.y - v2.y, p1.z - v2.z};
}

Vector operator-(const Point& p1, const Point& p2) {
    return {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
}

// Vector operators
bool operator==(const Vector &v1, const Vector &v2) {
    auto * difference = new Vector();
    * difference = v1 - v2;
    return tupleAbs(difference) < EPSILON;
}

Vector operator*(const Vector& v1, const double& scalar) {
    return {v1.x * scalar, v1.y * scalar, v1.z * scalar};
}

Vector operator+(const Vector &v1, const Vector &v2) {
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vector operator-(const Vector& v1, const Vector& v2) {
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vector operator-(const Vector& v1) {
    return {-v1.x, -v1.y, -v1.z};
}

Vector operator/(const Vector& v1, const double& scalar) {
    return {v1.x / scalar, v1.y / scalar, v1.z / scalar};
}

std::ostream& operator<<(std::ostream& out, const Vector& v1) {
    out << '[' << v1.x << ", " << v1.y << ", " << v1.z << ']';
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

Color operator/(const Color& c1, const double& scalar) {
    return {c1.x / scalar, c1.y / scalar, c1.z / scalar};
}

bool operator==(const Color& c1, const Color& c2) {
    auto * difference = new Color();
    * difference = c1 - c2;
    return tupleAbs(difference) < EPSILON;
}

bool operator!=(const Color& c1, const Color& c2) {
    auto * difference = new Color();
    * difference = c1 - c2;
    return !(tupleAbs(difference) < EPSILON);
}

std::ostream& operator<<(std::ostream& out, const Color& c1) {
    out << '[' << c1.r << ", " << c1.g << ", " << c1.b << ']';
    return out;
}

} // namespace raytracer

