#include "material.h"
#include "common.h"

#include <cmath>

namespace raytracer {
    Material::Material(const raytracer::Color &color, const double ambient, const double& diffuse, const double& specular, const double& shininess)
        : color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
    {
    }

    Material::Material()
        : color(raytracer::Color(1, 1, 1)), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200.0)
    {
    }

    bool Material::operator==(const Material &rhs) const {
        return color == rhs.color &&
               ambient == rhs.ambient &&
               specular == rhs.specular &&
               shininess == rhs.shininess &&
               diffuse == rhs.diffuse;
    }

    bool Material::operator!=(const Material &rhs) const {
        return !(rhs == *this);
    }

    Color Material::setPhongLighting(const Light &light, const Point &point, const Vector &eye, const Vector &normal, const float &inShadow) const {
        raytracer::Color dif, spec;
        raytracer::Color effectiveColor = this->color * light.intensity;
        raytracer::Vector lightVector = normalize(light.position - point);
        raytracer::Color amb = effectiveColor * this->ambient;
        double lightDotNormal = dot(lightVector, normal);
        if (lightDotNormal < 0) {
            dif = black;
            spec = black;
        } else {
            dif = effectiveColor * this->diffuse * lightDotNormal;
            raytracer::Vector reflectVector = reflect(-lightVector, normal);
            double reflectDotEye = dot(reflectVector, eye);
            if (reflectDotEye <= 0) {
                spec = black;
            } else {
                double factor = pow(reflectDotEye, this->shininess);
                spec = light.intensity * this->specular * factor;
            }
        }
        return raytracer::Color(amb + (dif * inShadow) + (spec * inShadow));
    }
} // namespace raytracer


