#include "pattern.h"
#include "shape.h"

#include <cmath>

namespace raytracer {

Pattern::Pattern()
    : c1(), c2(), hasPattern()
{
}

Pattern::Pattern(const raytracer::Color &c1, const raytracer::Color &c2)
    : c1(c1), c2(c2), hasPattern(false)
{
}

Pattern Pattern::createStripePattern(const Color &stripeC1, const Color &stripeC2) {
    this->c1 = stripeC1;
    this->c2 = stripeC2;
    this->hasPattern = true;
    return * this;
}

Color Pattern::stripeAt(const Point &p) const {
    return (int)floor(p.x) % 2 == 0 ? this->c1 : this->c2;
}

Color Pattern::stripeAtObject(const std::shared_ptr<Shape const> &s, const Point &p) const {
    Point objectPoint = inverse(s->getTransform()) * p;
    Point patternPoint = inverse(this->getPatternTransform()) * objectPoint;
    return this->stripeAt(patternPoint);
}

void Pattern::setPatternTransform(const Transform &t) {
    transformMat = t;
}

Transform Pattern::getPatternTransform() const {
    return transformMat;
}


} // namespace raytracer

