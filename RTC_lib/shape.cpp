#include "shape.h"

#include <cmath>

namespace raytracer {

    Shape::Shape()
        : shapePtr()
    {
        id = ++nextId;
    }


    size_t Shape::nextId = 0;

    bool operator==(const Shape& s1, const Shape& s2) {
        return typeid(s1) == typeid(s2);
    }

} // namespace raytracer

