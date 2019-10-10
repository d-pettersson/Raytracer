#include "pattern.h"
#include "shape.h"

#include <cmath>

namespace raytracer {

Pattern::Pattern()
    : patternPtr(), transformMat(), hasPattern(true)
{
    transformMat = generateIdentity(4, 4);
}


void Pattern::setPatternTransform(const Transform &t) {
    transformMat = t;
}

Transform Pattern::getPatternTransform() const {
    return transformMat;
}

// Stripe pattern

StripePattern::StripePattern()
    : hasPattern(true)
{
}

StripePattern::StripePattern(const raytracer::Color &c1, const raytracer::Color &c2)
    : c1(c1), c2(c2), hasPattern(true)
{
}

Color StripePattern::patternAt(const Point &p) const {
    return (int)floor(p.x) % 2 == 0 ? this->c1 : this->c2;
}

Color StripePattern::patternAtShape(const std::shared_ptr<Shape const> &s, const Point &p) const {
    Point objectPoint = inverse(s->getTransform()) * p;
    Point patternPoint = inverse(this->getPatternTransform()) * objectPoint;
    return this->patternAt(patternPoint);
}

// Gradient pattern

GradientPattern::GradientPattern()
    : hasPattern(true)
{
}

GradientPattern::GradientPattern(const Color &c1, const Color &c2)
    : c1(c1), c2(c2), hasPattern(true)
{
}

Color GradientPattern::patternAt(const Point &p) const {
    Color distance = this->c2 - this->c1;
    double fraction = p.x - floor(p.x);
    return this->c1 + distance * fraction;
}

Color GradientPattern::patternAtShape(const std::shared_ptr<Shape const> &s, const Point &p) const {
    Point objectPoint = inverse(s->getTransform()) * p;
    Point patternPoint = inverse(this->getPatternTransform()) * objectPoint;
    return this->patternAt(patternPoint);
}


} // namespace raytracer

