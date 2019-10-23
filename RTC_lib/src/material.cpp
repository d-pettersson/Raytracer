#include "include/material.h"
#include "include/common.h"

#include <utility>

namespace raytracer {
Material::Material(const Color& _color, const double &_ambient, const double &_diffuse, const double &_specular, const double &_reflection, const double &_shininess, const double &_transparency, const double &_refractiveIndex)
    : color(_color), ambient(_ambient), diffuse(_diffuse), specular(_specular), shininess(_shininess), reflection(_reflection), pattern(), transparency(_transparency), refractiveIndex(_refractiveIndex)
{
    this->pattern = std::make_shared<NoPattern>(); // set an "empty" shared_ptr as instantiation of the abstract base class is not allowed
}

Material::Material()
    : color(), ambient(0.1), diffuse(0.9), specular(0.9), shininess(200.0), reflection(0.0), pattern(), transparency(0.0), refractiveIndex(1.0)
{
    this->color = Color(1, 1, 1);
    this->pattern = std::make_shared<NoPattern>();
}

bool Material::operator==(const Material &rhs) const {
    return color == rhs.color &&
           ambient == rhs.ambient &&
           specular == rhs.specular &&
           shininess == rhs.shininess &&
           diffuse == rhs.diffuse &&
           transparency == rhs.transparency &&
           refractiveIndex == rhs.refractiveIndex;
}

bool Material::operator!=(const Material &rhs) const {
    return !(rhs == *this);
}

//    Color Material::setPhongLighting(const Light &light, const Point &point, const Vector &eye, const Vector &normal, const float &intensity) const {
//        raytracer::Color dif, spec;
//        raytracer::Color effectiveColor = this->color * light.intensity;
//        raytracer::Vector lightVector = normalize(light.position - point);
//        raytracer::Color amb = effectiveColor * this->ambient;
//        double lightDotNormal = dot(lightVector, normal);
//        if (lightDotNormal < 0) {
//            dif = black;
//            spec = black;
//        } else {
//            dif = effectiveColor * this->diffuse * lightDotNormal;
//            raytracer::Vector reflectVector = reflect(-lightVector, normal);
//            double reflectDotEye = dot(reflectVector, eye);
//            if (reflectDotEye <= 0) {
//                spec = black;
//            } else {
//                double factor = pow(reflectDotEye, this->shininess);
//                spec = light.intensity * this->specular * factor;
//            }
//        }
//        return raytracer::Color(amb + (dif * intensity) + (spec * intensity));
//    }

/* Area light related
Color Material::setPhongLighting(const std::shared_ptr<Shape const> &s, const Light &light, const Point &position, const Vector &eye, const Vector &normal, const float &intensity) const {
    Color amb, dif, spec, sum, effectiveColor, newColor;

    if (this->pattern->hasPattern) {
        newColor = this->pattern->patternAtShape(s, position);
        effectiveColor = newColor * light.intensity;
    } else {
        effectiveColor = this->color * light.intensity;
    }

    amb = effectiveColor * this->ambient;

    auto * lightVector = new Vector();
    double lightDotNormal;

    sum = black;

    for (int i = 0; i < light.samples; i++) {
        * lightVector = normalize(light.pointOnLight(i % light.uSteps, i / light.vSteps) - position);
        lightDotNormal = dot(* lightVector, normal);
        if (lightDotNormal < 0) {
            dif = black;
            spec = black;
        } else {
            dif = effectiveColor * this->diffuse * lightDotNormal;
            raytracer::Vector reflectVector = reflect(- * lightVector, normal);
            double reflectDotEye = dot(reflectVector, eye);
            if (reflectDotEye <= 0) {
                spec = black;
            } else {
                double factor = pow(reflectDotEye, this->shininess);
                spec = light.intensity * this->specular * factor;
            }
        }
        sum = sum + dif;
        sum = sum + spec;
    }

    return amb + (sum / (double)light.samples) * intensity;
}
*/

Color Material::setPhongLighting(const std::shared_ptr<Shape const> &s, const Light &light, const Point &position, const Vector &eye, const Vector &normal, const bool &isShadowed) const {
    Color amb, dif, spec, effectiveColor, newColor;

    if (this->pattern->hasPattern) {
        newColor = this->pattern->patternAtShape(s, position);
        effectiveColor = newColor * light.intensity;
    } else {
        effectiveColor = this->color * light.intensity;
    }

    amb = effectiveColor * this->ambient;

    Vector lightVector = normalize(light.position - position);

    double lightDotNormal = dot(lightVector, normal);
    if (lightDotNormal < 0) {
        dif = black;
        spec = black;
    } else {
        dif = effectiveColor * this->diffuse * lightDotNormal;
        Vector reflectVector = reflect(-lightVector, normal);
        double reflectDotEye = dot(reflectVector, eye);
        if (reflectDotEye <= 0) {
            spec = black;
        } else {
            double factor = pow(reflectDotEye, this->shininess);
            spec = light.intensity * this->specular * factor;
        }
    }
    return isShadowed ? amb : amb + dif + spec;

}
} // namespace raytracer


