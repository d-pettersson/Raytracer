#include "light.h"

namespace raytracer {
    Light::Light(const raytracer::Point &position, const raytracer::Color &intensity)
        : position(position), intensity(intensity)
    {
    }

    Light::Light()
    {
    }

    void Light::setPointLight(const raytracer::Point &position, const raytracer::Color &intensity) {
        this->position = position;
        this->intensity = intensity;
    }
} // namespace raytracer

