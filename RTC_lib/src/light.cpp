#include "include/light.h"
#include "include/world.h"

#include <random>
#include <memory>
#include <utility>

namespace raytracer {
Light::Light(Tuple position, Color intensity)
    : position_(position), intensity_(std::move(intensity)), uSteps_(1), vSteps_(1), samples_(1)
{
}

Light::Light()
    : uSteps_(1), vSteps_(1), samples_(1)
{
}

void Light::setPointLight(const Tuple &position, const Color &intensity) {
    this->setAreaLight(position, createVector(1, 0, 0), 1, createVector(0, 1, 0), 1, intensity);
}


void Light::setAreaLight(const Tuple &corn, const Tuple &fullUVec, const int &uSt, const Tuple &fullVVec, const int &vSt, const Color &intensity) {
    this->corner_ = corn;
    this->uSteps_ = uSt;
    this->vSteps_ = vSt;
    this->uVec_ = fullUVec / uSt;
    this->vVec_ = fullVVec / vSt;
    this->samples_ = uSteps_ * vSteps_;
    this->intensity_ = intensity;
    this->position_ = createPoint(1, 0, 0.5);
}

float Light::intensityAt(const Tuple &point, const World &world) {
    float total = 0.0;
    for (int v = 0; v < this->vSteps_; v++) {
        for (int u = 0; u < this->uSteps_; u++) {
            if (!world.isShadowed(this->pointOnLight(u, v), point)) {
                total++;
            }
        }
    }
    return total / (float)this->samples_;
}

Tuple Light::pointOnLight(const double &u, const double &v) const {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,10);

    return this->corner_ + this->uVec_ * (u + (double)dist(rng) * 0.1) + this->vVec_ * (v + (double)dist(rng) * 0.1);;
}

bool Light::operator==(const Light &rhs) const {
    return intensity_ == rhs.intensity_ &&
           position_ == rhs.position_;
}

bool Light::operator!=(const Light &rhs) const {
    return !(rhs == *this);
}

} // namespace raytracer

