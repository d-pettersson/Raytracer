#ifndef RTC_PATTERN_H
#define RTC_PATTERN_H

#include "tuple.h"
#include "transform.h"

#include <memory>

namespace raytracer {
class Shape;

class Pattern {
    public:
        Pattern();
        Pattern(const Color &c1, const Color &c2);

        Pattern createStripePattern(const Color &stripeC1, const Color &stripeC2);
        Color stripeAt(const Point &p) const;
        Color stripeAtObject(const std::shared_ptr<Shape const> &s, const Point &p) const;
        void setPatternTransform(const Transform &t);
        Transform getPatternTransform() const;

        Color c1;
        Color c2;
        bool hasPattern;
        Transform transformMat;
};

class StripePattern : public Pattern {

};
} // namespace raytracer



#endif //RTC_PATTERN_H
