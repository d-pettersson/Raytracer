#ifndef RTC_MATERIAL_H
#define RTC_MATERIAL_H

#include "include/tuple.h"
#include "include/light.h"
#include "include/pattern.h"

namespace raytracer {
class Material {
    public:
        Material(const raytracer::Color &color,
                 const double &ambient,
                 const double &diffuse,
                 const double &specular,
                 const double &reflection,
                 const double &shininess);

        Material();

        Color setPhongLighting(const std::shared_ptr<Shape const> &s,
                               const Light& light,
                               const Point& position,
                               const Vector& eye,
                               const Vector& normal,
                               const float &intensity) const;

        Color color;
        double ambient;
        double specular;
        double shininess;
        double diffuse;
        double reflection;

        std::shared_ptr<Pattern> pattern;

        bool operator==(const Material &rhs) const;
        bool operator!=(const Material &rhs) const;

};
} // namespace raytracer



#endif //RTC_MATERIAL_H
