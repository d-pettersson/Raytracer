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

Tuple Tuple::operator-() {
    return {-x_, -y_, -z_, -w_};
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

Tuple normalize(const Tuple &t1) {
    return {t1.x_ / magnitude(t1), t1.y_ / magnitude(t1), t1.z_ / magnitude(t1), t1.w_ / magnitude(t1)};
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

Tuple reflect(const Tuple &v, const Tuple &n) {
    return v - n * 2 * dot(v, n);
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

