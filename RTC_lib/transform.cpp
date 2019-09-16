#include "transform.h"

#include <cmath>

namespace raytracer {

Transform::Transform()
    : Matrix(4, 4)
{
}

Transform::Transform(const Matrix& m)
    : Matrix(m)
{
}

Transform Transform::translate(const double& x, const double& y, const double& z) {
    Point p = Point(x, y, z);
    Matrix output = generateIdentity(this->getRowSize(), this->getColSize());
    for (int i = 0; i < this->getRowSize() - 1; i++) {
        output(i, this->getRowSize() - 1) = p(i);
    }
    * this = output;
    return * this;
}

Transform Transform::scale(const double &x, const double &y, const double &z) {
    Point p = Point(x, y, z);
    Matrix output = generateIdentity(this->getRowSize(), this->getColSize());
    for (int i = 0; i < this->getRowSize() - 1; i++) {
        output(i, i) = p(i);
    }
    * this = output;
    return * this;
}

Transform Transform::rotateX(const double& angle) {
    Matrix output = generateIdentity(this->getRowSize(), this->getColSize());
    output(1, 1) = cos(angle);
    output(1, 2) = -sin(angle);
    output(2, 1) = sin(angle);
    output(2, 2) = cos(angle);
    * this = output;
    return * this;
}

Transform Transform::rotateY(const double &angle) {
    Matrix output = generateIdentity(this->getRowSize(), this->getColSize());
    output(0, 0) = cos(angle);
    output(0, 2) = sin(angle);
    output(2, 0) = -sin(angle);
    output(2, 2) = cos(angle);
    * this = output;
    return * this;
}

Transform Transform::rotateZ(const double &angle) {
    Matrix output = generateIdentity(this->getRowSize(), this->getColSize());
    output(0, 0) = cos(angle);
    output(0, 1) = -sin(angle);
    output(1, 0) = sin(angle);
    output(1, 1) = cos(angle);
    * this = output;
    return * this;
}

Transform Transform::shear(const double &xy, const double &xz,
                           const double &yx, const double &yz,
                           const double &zx, const double &zy) {
    Matrix output = generateIdentity(this->getRowSize(), this->getColSize());
    output(0, 1) = xy;
    output(0, 2) = xz;
    output(1, 0) = yx;
    output(1, 2) = yz;
    output(2, 0) = zx;
    output(2, 1) = zy;
    * this = output;
    return * this;
}


} // namespace raytracer
