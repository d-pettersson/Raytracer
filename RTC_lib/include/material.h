#ifndef RTC_MATERIAL_H
#define RTC_MATERIAL_H

#include "include/tuple.h"
#include "include/light.h"
#include "include/pattern.h"

namespace raytracer {
class Material {
    public:
        Material(const Color &_color,
                 const double &_ambient,
                 const double &_diffuse,
                 const double &_specular,
                 const double &_reflection,
                 const double &_shininess,
                 const double &_transparency,
                 const double &_refractiveIndex);

        Material();

//        Color setPhongLighting(const std::shared_ptr<Shape const> &s,
//                               const Light& light,
//                               const Point& position,
//                               const Vector& eye,
//                               const Vector& normal,
//                               const float &intensity) const;

        Color setPhongLighting(const std::shared_ptr<Shape const> &s,
                               const Light& light,
                               const Point& position,
                               const Vector& eye,
                               const Vector& normal,
                               const bool &isShadowed) const;

        Color color;
        double ambient;
        double specular;
        double shininess;
        double diffuse;
        double reflection;
        double transparency;
        double refractiveIndex;

        std::shared_ptr<Pattern> pattern;

        bool operator==(const Material &rhs) const;
        bool operator!=(const Material &rhs) const;

};
} // namespace raytracer



#endif //RTC_MATERIAL_H
