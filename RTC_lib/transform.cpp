#include "transform.h"

namespace raytracer {

Transform::Transform()
    :x{0.f}, y{0.f}, z{0.f}
{
}

Transform::Transform(double xx, double yy, double zz)
        : x{xx}, y{yy}, z{zz}
{

}

Matrix Transform::translation(const double& x, const double& y, const double& z) {
    return Matrix();
}

Matrix Transform::translation(const Transform& t) {
    return Matrix();
}

Tuple Transform::operator*(const Tuple& tup) {
    return {this->x * tup.x, this->y * tup.y, this->z * tup.z, tup.w};
}

Point Transform::operator*(const Transform& trans) {
    return {this->x * trans.x, this->y * trans.y, this->z * trans.z};
}

std::ostream& operator<<(std::ostream& out, const Transform& t1) {
    out << '[' << t1.x << ", " << t1.y << ", " << t1.z << ']';
    return out;
}

} // namespace raytracer
