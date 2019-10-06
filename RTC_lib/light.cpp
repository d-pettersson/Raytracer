#include "light.h"
#include "world.h"

namespace raytracer {
Light::Light(const raytracer::Point &position, const raytracer::Color &intensity)
    : position(position), intensity(intensity)
{
}

Light::Light()
{
}

void Light::setPointLight(const raytracer::Point &pos, const raytracer::Color &intens) {
    this->position = pos;
    this->intensity = intens;
}

void Light::setAreaLight(const Point &corn, const Vector &fullUVec, const int &uSt, const Vector &fullVVec, const int &vSt, const Color &intens) {
    this->corner = corn;
    this->uSteps = uSt;
    this->vSteps = vSt;
    this->uVec = fullUVec / uSt;
    this->vVec = fullVVec / vSt;
    this->samples = uSteps * vSteps;
    this->intensity = intens;
    this->position = raytracer::Point(1, 0, 0.5);
}

float Light::intensityAt(const Point &point, const World &world) const {
    float total = 0.0;
    for (int v = 0; v < this->vSteps; v++) {
        for (int u = 0; u < this->uSteps; u++) {
            if (!world.isShadowed(this->pointOnLight(u, v), point)) {
                total++;
            }
        }
    }
    return total / (float)this->samples;
}

Point Light::pointOnLight(const double &u, const double &v) const {
    return this->corner + this->uVec * (u + 0.5) + this->vVec * (v + 0.5);
}


bool Light::operator==(const Light &rhs) const {
    return intensity == rhs.intensity &&
           position == rhs.position;
}

bool Light::operator!=(const Light &rhs) const {
    return !(rhs == *this);
}

} // namespace raytracer

