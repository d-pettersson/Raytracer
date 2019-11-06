#include "include/pattern.h"
#include "include/shape.h"

#include <cmath>
#include <utility>

namespace raytracer {

Pattern::Pattern()
    : patternPtr(), transformMat(), hasPattern()
{
    transformMat = generateIdentity(4, 4);
}

Pattern::~Pattern() = default;


Pattern::Pattern(Color c1, Color c2)
    : c1(std::move(c1)), c2(std::move(c2)), hasPattern()
{
}

void Pattern::setPatternTransform(const Transform &t) {
    transformMat = t;
}

Transform Pattern::getPatternTransform() const {
    return transformMat;
}

// No pattern

NoPattern::NoPattern()
        : Pattern()
{
}

NoPattern::~NoPattern() = default;

Color NoPattern::patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const {
    return Color();
}

Color NoPattern::patternAt(const Tuple &p) const {
    return Color();
}

// Test pattern

TestPattern::TestPattern()
    : Pattern()
{
    this->hasPattern = true;
}

TestPattern::~TestPattern() = default;

Color TestPattern::patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const {
    Tuple objectPoint = inverse(s->getTransform()) * p;
    Tuple patternPoint = inverse(this->getPatternTransform()) * objectPoint;
    return this->patternAt(patternPoint);
}

Color TestPattern::patternAt(const Tuple &p) const {
    return Color(p.x_, p.y_, p.z_);
}

// Stripe pattern

StripePattern::StripePattern()
    : Pattern()
{
    this->hasPattern = true;
}

StripePattern::~StripePattern() = default;

StripePattern::StripePattern(const Color &c1, const Color& c2)
    : Pattern(c1, c2)
{
    this->hasPattern = true;
}

Color StripePattern::patternAt(const Tuple &p) const {
    return (int)floor(p.x_) % 2 == 0 ? this->c1 : this->c2;
}

Color StripePattern::patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const {
    Tuple objectPoint = inverse(s->getTransform()) * p;
    Tuple patternPoint = inverse(this->getPatternTransform()) * objectPoint;
    return this->patternAt(patternPoint);
}

// Gradient pattern

GradientPattern::GradientPattern()
    : Pattern()
{
    this->hasPattern = true;
}

GradientPattern::~GradientPattern() = default;

GradientPattern::GradientPattern(const Color &c1, const Color& c2)
    : Pattern(c1, c2)
{
    this->hasPattern = true;
}

Color GradientPattern::patternAt(const Tuple &p) const {
    Color distance = this->c2 - this->c1;
    double fraction = p.x_ - floor(p.x_);
    return this->c1 + distance * fraction;
}

Color GradientPattern::patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const {
    Tuple objectPoint = inverse(s->getTransform()) * p;
    Tuple patternPoint = inverse(this->getPatternTransform()) * objectPoint;
    return this->patternAt(patternPoint);
}

// Ring pattern

RingPattern::RingPattern()
    : Pattern()
{
    this->hasPattern = true;
}

RingPattern::~RingPattern() = default;

RingPattern::RingPattern(const Color &c1, const Color& c2)
    : Pattern(c1, c2)
{
    this->hasPattern = true;
}

Color RingPattern::patternAt(const Tuple &p) const {
    return (int)floor(sqrt(pow(p.x_, 2) + pow(p.z_, 2))) % 2 == 0 ? this->c1 : this->c2;
}

Color RingPattern::patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const {
    Tuple objectPoint = inverse(s->getTransform()) * p;
    Tuple patternPoint = inverse(this->getPatternTransform()) * objectPoint;
    return this->patternAt(patternPoint);
}

// Checker pattern

CheckerPattern::CheckerPattern()
    : Pattern()
{
    this->hasPattern = true;
}

CheckerPattern::~CheckerPattern() = default;

CheckerPattern::CheckerPattern(const Color &c1, const Color &c2)
    : Pattern(c1, c2)
{
    this->hasPattern = true;
}

Color CheckerPattern::patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const {
    Tuple objectPoint = inverse(s->getTransform()) * p;
    Tuple patternPoint = inverse(this->getPatternTransform()) * objectPoint;
    return this->patternAt(patternPoint);
}

Color CheckerPattern::patternAt(const Tuple &p) const {
    return (int)floor(p.x_) + (int)floor(p.y_) + (int)floor(p.z_) % 2 == 0 ? this->c1 : this->c2;
}
} // namespace raytracer

