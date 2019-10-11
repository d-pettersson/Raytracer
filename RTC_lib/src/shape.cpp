#include "include/shape.h"

#include <cmath>

namespace raytracer {

Shape::Shape()
    : shapePtr(), transformMat()
{
    id = ++nextId;
    transformMat = generateIdentity(4, 4);
}

size_t Shape::nextId = 0;

Transform Shape::getTransform() const {
    return transformMat;
}

void Shape::setTransform(const Transform& t) {
    transformMat = t;
}

bool operator==(const Shape& s1, const Shape& s2) {
    return typeid(s1) == typeid(s2);
}

} // namespace raytracer

