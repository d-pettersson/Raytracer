#ifndef RTC_MATERIAL_H
#define RTC_MATERIAL_H

#include "tuple.h"
#include "light.h"

namespace raytracer {
class Material {
    public:
    Material(const Color &color, const double ambient, const double& specular, const double& shininess, const double& diffuse);

    Material();

    Color setPhongLighting(const Light& light, const Point& position, const Vector& eye, const Vector& normal, const float &inShadow) const;

    Color color;
    double ambient;
    double specular;
    double shininess;
    double diffuse;

    bool operator==(const Material &rhs) const;
    bool operator!=(const Material &rhs) const;

};
} // namespace raytracer



#endif //RTC_MATERIAL_H
