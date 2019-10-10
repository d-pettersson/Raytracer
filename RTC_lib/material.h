#ifndef RTC_MATERIAL_H
#define RTC_MATERIAL_H

#include "tuple.h"
#include "light.h"
#include "pattern.h"

namespace raytracer {
class Material {
    public:
        Material(const Color &color, const double &ambient, const double& specular, const double& shininess, const double& diffuse);

        Material();

        Color setPhongLighting(const std::shared_ptr<Shape const> &s, const Light& light, const Point& position, const Vector& eye, const Vector& normal, const float &intensity) const;

        Color color;
        double ambient;
        double specular;
        double shininess;
        double diffuse;
        Pattern pattern;

        bool operator==(const Material &rhs) const;
        bool operator!=(const Material &rhs) const;

};
} // namespace raytracer



#endif //RTC_MATERIAL_H
