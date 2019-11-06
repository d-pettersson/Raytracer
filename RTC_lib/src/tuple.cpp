#include "include/tuple.h"

#include <cmath>

namespace raytracer {

Tuple::Tuple(double x, double y, double z, double w)
        : x_{x}, y_{y}, z_{z}, w_{w}
{
}

Tuple::Tuple()
        : x_{0.0}, y_{0.0}, z_{0.0}, w_{0.0}
{
}

//----------------------------------------------------------------

Point::Point(double x, double y, double z)
    : Tuple{x, y, z, 1.0}
{
}

Point::Point()
    : Tuple()
{
}

//----------------------------------------------------------------

Vector::Vector(double x, double y, double z)
    : Tuple{x, y, z, 0.0}
{
}

Vector::Vector()
    : Tuple()
{
}

//----------------------------------------------------------------

Color::Color(double r, double g, double b)
    : Tuple(r, g, b, 0.0), r_(x_), g_(y_), b_(z_)
{
}

Color::Color()
    : Tuple(), r_(), g_(), b_()
{
}

double& Tuple::operator()(size_t index) {
    switch (index) {
        case (0):
            return x_;
        case (1):
            return y_;
        case (2):
            return z_;
        case (3):
            return w_;
        default:
            break;
    }
}

double Tuple::operator()(size_t index) const {
    switch (index) {
        case (0):
            return x_;
        case (1):
            return y_;
        case (2):
            return z_;
        case (3):
            return w_;
        default:
            break;
    }
}

bool Tuple::isPoint() {
    return w_ == 1.0;
}

bool Tuple::isVector() {
    return w_ == 0.0;
}

Tuple createPoint(const double &x, const double &y, const double &z) {
    return {x, y, z, 1.0};
}

Tuple createVector(const double &x, const double &y, const double &z) {
    return {x, y, z, 0.0};
}

Tuple normalize(const Tuple &t1) {
    return {t1.x_ / magnitude(t1), t1.y_ / magnitude(t1), t1.z_ / magnitude(t1), t1.w_ / magnitude(t1)};
}

Vector normalize(const Vector &v1) {
    return {v1.x_ / magnitude(v1), v1.y_ / magnitude(v1), v1.z_ / magnitude(v1)};
}

Tuple abs(const Tuple &t1) {
    return {fabs(t1.x_), fabs(t1.y_), fabs(t1.z_), fabs(t1.w_)};
}

double magnitude(const Tuple& t1) {
    return sqrt(t1.x_ * t1.x_ + t1.y_ * t1.y_ + t1.z_ * t1.z_ + t1.w_ * t1.w_);
}

double dot(const Tuple& t1, const Tuple& t2) {
    return t1.x_ * t2.x_ + t1.y_ * t2.y_ + t1.z_ * t2.z_ + t1.w_ * t2.w_;
}

Tuple cross(const Tuple& t1, const Tuple& t2) {
    Tuple result = raytracer::createVector(
            t1.y_ * t2.z_ - t1.z_ * t2.y_,
            t1.z_ * t2.x_ - t1.x_ * t2.z_,
            t1.x_ * t2.y_ - t1.y_ * t2.x_);
    return result;
}

Vector cross(const Vector &v1, const Vector &v2) {
    return raytracer::Vector(v1.y_ * v2.z_ - v1.z_ * v2.y_,
                             v1.z_ * v2.x_ - v1.x_ * v2.z_,
                             v1.x_ * v2.y_ - v1.y_ * v2.x_);
}


Vector reflect(const Vector& v, const Vector& n) {
    return v - n * 2 * dot(v, n);
}

// Point operator
std::ostream& operator<<(std::ostream& out, const Point& p1) {
    out << '[' << p1.x_ << ", " << p1.y_ << ", " << p1.z_ << ']';
    return out;
}

Point abs(const Point &p) {
    return {fabs(p.x_), fabs(p.y_), fabs(p.z_)};
}

bool operator==(const Point &p1, const Point &p2) {
    auto difference = p1 - p2;
    return abs(difference) < EPSILON;
}

bool operator!=(const Point &p1, const Point &p2) {
    return !(p1 == p2);
}

Point Point::operator-() {
    return {-(* this).x_, -(* this).y_, -(* this).z_};
}

Point operator*(const Point& p1, const Point& p2) {
    return {p1.x_ * p2.x_, p1.y_ * p2.y_, p1.z_ * p2.z_};
}

Point operator*(const Point& p1, const Vector& p2) {
    return {p1.x_ * p2.x_, p1.y_ * p2.y_, p1.z_ * p2.z_};
}

Point operator*(const Point& p1, const double& scalar) {
    return {p1.x_ * scalar, p1.y_ * scalar, p1.z_ * scalar};
}

Point operator+(const Point& p1, const Point& p2) {
    return {p1.x_ + p2.x_, p1.y_ + p2.y_, p1.z_ + p2.z_};
}

Point operator+(const Point& p1, const Vector& v2) {
    return {p1.x_ + v2.x_, p1.y_ + v2.y_, p1.z_ + v2.z_};
}

Point operator-(const Point& p1, const Vector& v2) {
    return {p1.x_ - v2.x_, p1.y_ - v2.y_, p1.z_ - v2.z_};
}

Point operator-(const Point& p1, const double &scalar) {
    return {scalar - p1.x_, scalar - p1.y_, scalar - p1.z_};
}

Vector operator-(const Point& p1, const Point& p2) {
    return {p1.x_ - p2.x_, p1.y_ - p2.y_, p1.z_ - p2.z_};
}

// Vector operators
Vector abs(const Vector &v) {
    return {fabs(v.x_), fabs(v.y_), fabs(v.z_)};
}

bool operator==(const Vector &v1, const Vector &v2) {
    auto difference = v1 - v2;
    return abs(difference) < EPSILON;
}

bool operator!=(const Vector &v1, const Vector &v2) {
    return !(v1 == v2);
}

Vector operator*(const Vector& v1, const double& scalar) {
    return {v1.x_ * scalar, v1.y_ * scalar, v1.z_ * scalar};
}

Vector operator+(const Vector &v1, const Vector &v2) {
    return {v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_};
}

Vector operator-(const Vector& v1, const Vector& v2) {
    return {v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_};
}

Vector operator-(const Vector& v1) {
    return {-v1.x_, -v1.y_, -v1.z_};
}

Vector operator/(const Vector& v1, const double& scalar) {
    return {v1.x_ / scalar, v1.y_ / scalar, v1.z_ / scalar};
}

std::ostream& operator<<(std::ostream& out, const Vector& v1) {
    out << '[' << v1.x_ << ", " << v1.y_ << ", " << v1.z_ << ']';
    return out;
}


// Tuple operators
bool operator<(const Tuple& t1, const Tuple& t2) {
    return t1.x_ < t2.x_ && t1.y_ < t2.y_ && t1.z_ < t2.z_ && t1.w_ < t2.w_;
}

bool operator<(const Tuple& t1, const double& d1) {
    return t1.x_ < d1 && t1.y_ < d1 && t1.z_ < d1 && t1.w_ < d1;
}

bool operator==(const Tuple& t1, const Tuple& t2) {
    auto difference = t1 - t2;
    return abs(difference) < EPSILON;
}

bool operator!=(const Tuple& t1, const Tuple& t2) {
    return !(t1 == t2);
}

Tuple operator-(const Tuple& t1, const Tuple& t2) {
    return {t1.x_ - t2.x_, t1.y_ - t2.y_, t1.z_ - t2.z_, t1.w_ - t2.w_};
}

Tuple operator-(const Tuple& t1) {
    return {-t1.x_, -t1.y_, -t1.z_, -t1.w_};
}

Tuple operator+(const Tuple& t1, const Tuple& t2) {
    return {t1.x_ + t2.x_, t1.y_ + t2.y_, t1.z_ + t2.z_, t1.w_ + t2.w_};
}

Tuple operator*(const Tuple& t1, const Tuple& t2) {
    return {t1.x_ * t2.x_, t1.y_ * t2.y_, t1.z_ * t2.z_, t1.w_ * t2.w_};
}

Tuple operator*(const Tuple& t1, const double& scalar) {
    return {t1.x_ * scalar, t1.y_ * scalar, t1.z_ * scalar, t1.w_ * scalar};
}

Tuple operator/(const Tuple& t1, const double& scalar) {
    return {t1.x_ / scalar, t1.y_ / scalar, t1.z_ / scalar, t1.w_ / scalar};
}

std::ostream& operator<<(std::ostream& out, const Tuple& t1) {
    out << '[' << t1.x_ << ", " << t1.y_ << ", " << t1.z_ << ", " << t1.w_ << ']';
    return out;
}

// Color operators
Color operator-(const Color& c1, const Color& c2) {
    return {c1.r_ - c2.r_, c1.g_ - c2.g_, c1.b_ - c2.b_};
}

Color operator+(const Color& c1, const Color& c2) {
    return {c1.r_ + c2.r_, c1.g_ + c2.g_, c1.b_ + c2.b_};
}

Color operator*(const Color& c1, const Color& c2) {
    return {c1.r_ * c2.r_, c1.g_ * c2.g_, c1.b_ * c2.b_};
}

Color operator*(const Color& c1, const double& scalar) {
    return {c1.r_ * scalar, c1.g_ * scalar, c1.b_ * scalar};
}

Color operator/(const Color& c1, const double& scalar) {
    return {c1.x_ / scalar, c1.y_ / scalar, c1.z_ / scalar};
}

bool operator==(const Color& c1, const Color& c2) {
    auto difference = c1 - c2;
    return abs(difference) < EPSILON;
}

bool operator!=(const Color& c1, const Color& c2) {
    return !(c1 == c2);
}

std::ostream& operator<<(std::ostream& out, const Color& c1) {
    out << '[' << c1.r_ << ", " << c1.g_ << ", " << c1.b_ << ']';
    return out;
}

} // namespace raytracer

