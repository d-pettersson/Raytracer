#include "include/transform.h"

namespace raytracer {

Transform::Transform()
    : Matrix(4, 4)
{
    * this = generateIdentity(this->getRowSize(), this->getColSize());
}

Transform::Transform(const Matrix& m)
    : Matrix(m)
{
}

Transform& Transform::translate(const double &x, const double &y, const double &z) {
    Point p = Point(x, y, z);
    for (int i = 0; i < this->getRowSize() - 1; i++) {
        (* this)(i, this->getRowSize() - 1) = p(i);
    }
    return * this;
}

Transform& Transform::scale(const double &x, const double &y, const double &z) {
    Point p = Point(x, y, z);
    for (int i = 0; i < this->getRowSize() - 1; i++) {
        (* this)(i, i) = p(i);
    }
    return * this;
}

Transform& Transform::rotateX(const double &angle) {
    (* this)(1, 1) = cos(angle);
    (* this)(1, 2) = -sin(angle);
    (* this)(2, 1) = sin(angle);
    (* this)(2, 2) = cos(angle);
    return * this;
}

Transform& Transform::rotateY(const double &angle) {
    (* this)(0, 0) = cos(angle);
    (* this)(0, 2) = sin(angle);
    (* this)(2, 0) = -sin(angle);
    (* this)(2, 2) = cos(angle);
    return * this;
}

Transform& Transform::rotateZ(const double &angle) {
    (* this)(0, 0) = cos(angle);
    (* this)(0, 1) = -sin(angle);
    (* this)(1, 0) = sin(angle);
    (* this)(1, 1) = cos(angle);
    return * this;
}

Transform& Transform::shear(const double &xy, const double &xz,
                            const double &yx, const double &yz,
                            const double &zx, const double &zy) {
    (*this)(0, 1) = xy;
    (*this)(0, 2) = xz;
    (*this)(1, 0) = yx;
    (*this)(1, 2) = yz;
    (*this)(2, 0) = zx;
    (*this)(2, 1) = zy;
    return * this;
}

Transform viewTransform(const Point &from, const Point &to, const Vector &up) {
    auto * forward = new Vector();
    auto * left = new Vector();
    auto * trueUp = new Vector();
    auto * orientationData = new std::vector<double>(16);
    auto * orientationMatrix = new Matrix(4, 4);
    auto * transform = new Transform();

    * forward = normalize(to - from);
    * left = cross(* forward, normalize(up));
    * trueUp = cross(* left, * forward);
    * orientationData = std::vector<double>{left->x, left->y, left->z, 0,
                                            trueUp->x, trueUp->y, trueUp->z, 0,
                                            -forward->x, -forward->y, -forward->z, 0,
                                            0, 0, 0, 1};
    orientationMatrix->setMatrixData(* orientationData);
    auto * orientation = new raytracer::Transform(* orientationMatrix);
    return * orientation * transform->translate(-from.x, -from.y, -from.z);
}


} // namespace raytracer
