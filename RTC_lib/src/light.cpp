#include "include/light.h"
#include "include/world.h"

#include <random>
#include <memory>
#include <utility>

namespace raytracer {
Light::Light(const Point &_position, const Color &_intensity)
    : position(_position), intensity(_intensity), uSteps(1), vSteps(1), samples(1)
{
}

Light::Light()
    : position(), intensity(), uSteps(1), vSteps(1), samples(1)
{
}

void Light::setPointLight(const Point &_position, const Color &_intensity) {
    this->position  = _position;
    this->intensity = _intensity;
}

/* Area light related
void Light::setPointLight(const raytracer::Point &pos, const raytracer::Color &intens) {
    this->setAreaLight(pos, Vector(1, 0, 0), 1, Vector(0, 1, 0), 1, intens);
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

float Light::intensityAt(const Point &point, const World &world) {
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
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,10);

    return this->corner + this->uVec * (u + (double)dist(rng) * 0.1) + this->vVec * (v + (double)dist(rng) * 0.1);;
}
*/

bool Light::operator==(const Light &_light) const {
    return this->intensity == _light.intensity &&
           this->position == _light.position;
}

bool Light::operator!=(const Light &_light) const {
    return !(_light == * this);
}

std::ostream& operator<<(std::ostream& out, const Light &_light) {
    out << _light.position << " " << _light.intensity;
    return out;
}

} // namespace raytracer

