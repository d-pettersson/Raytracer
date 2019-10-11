#include "include/pattern.h"
#include "include/shape.h"

#include <cmath>

namespace raytracer {

Pattern::Pattern()
    : patternPtr(), transformMat(), hasPattern()
{
    transformMat = generateIdentity(4, 4);
}

Pattern::Pattern(const Color &c1, const Color &c2)
    : c1(c1), c2(c2), hasPattern()
{
}

void Pattern::setPatternTransform(const Transform &t) {
    transformMat = t;
}

Transform Pattern::getPatternTransform() const {
    return transformMat;
}

// Stripe pattern

StripePattern::StripePattern()
    : Pattern()
{
    this->hasPattern = true;
}

StripePattern::StripePattern(const Color &c1, const Color& c2)
    : Pattern(c1, c2)
{
    this->hasPattern = true;
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
    : Pattern()
{
    this->hasPattern = true;
}

GradientPattern::GradientPattern(const Color &c1, const Color& c2)
    : Pattern(c1, c2)
{
    this->hasPattern = true;
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

// Ring pattern

RingPattern::RingPattern()
    : Pattern()
{
    this->hasPattern = true;
}

RingPattern::RingPattern(const Color &c1, const Color& c2)
    : Pattern(c1, c2)
{
    this->hasPattern = true;
}

Color RingPattern::patternAt(const Point &p) const {
    return (int)floor(sqrt(pow(p.x, 2) + pow(p.z, 2))) % 2 == 0 ? this->c1 : this->c2;
}

Color RingPattern::patternAtShape(const std::shared_ptr<Shape const> &s, const Point &p) const {
    Point objectPoint = inverse(s->getTransform()) * p;
    Point patternPoint = inverse(this->getPatternTransform()) * objectPoint;
    return this->patternAt(patternPoint);
}

// Checker pattern

CheckerPattern::CheckerPattern()
    : Pattern()
{
    this->hasPattern = true;
}

CheckerPattern::CheckerPattern(const Color &c1, const Color &c2)
    : Pattern(c1, c2)
{
    this->hasPattern = true;
}

Color CheckerPattern::patternAtShape(const std::shared_ptr<Shape const> &s, const Point &p) const {
    Point objectPoint = inverse(s->getTransform()) * p;
    Point patternPoint = inverse(this->getPatternTransform()) * objectPoint;
    return this->patternAt(patternPoint);
}

Color CheckerPattern::patternAt(const Point &p) const {
    return (int)floor(p.x) + (int)floor(p.y) + (int)floor(p.z) % 2 == 0 ? this->c1 : this->c2;
}
} // namespace raytracer

