#ifndef RTC_PATTERN_H
#define RTC_PATTERN_H

#include "tuple.h"
#include "transform.h"

#include <memory>

namespace raytracer {
class Shape;

class Pattern : public std::enable_shared_from_this<Shape>{
    public:
        Pattern();

        virtual Color patternAtShape(const std::shared_ptr<Shape const> &s, const Point &p) const = 0;
        virtual Color patternAt(const Point &p) const = 0;

        void setPatternTransform(const Transform &t);
        Transform getPatternTransform() const;

        bool hasPattern;

    private:
        Transform transformMat;
        std::shared_ptr<Pattern> patternPtr;
};

class StripePattern : public Pattern {
    public:
        StripePattern();
        StripePattern(const Color &c1, const Color &c2);

        Color patternAtShape(const std::shared_ptr<Shape const> &s, const Point &p) const override;
        Color patternAt(const Point &p) const override;

        Color c1;
        Color c2;
        bool hasPattern;
};

class GradientPattern : public Pattern {
    public:
        GradientPattern();
        GradientPattern(const Color &c1, const Color &c2);

        Color patternAtShape(const std::shared_ptr<Shape const> &s, const Point &p) const override;
        Color patternAt(const Point &p) const override;

        Color c1;
        Color c2;
        bool hasPattern;
};
} // namespace raytracer



#endif //RTC_PATTERN_H
