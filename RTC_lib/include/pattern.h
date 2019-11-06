#ifndef RTC_PATTERN_H
#define RTC_PATTERN_H

#include "include/tuple.h"
#include "include/transform.h"

#include <memory>

// TODO: create radial gradient / nested / blended / perlin patterns

namespace raytracer {
class Shape;

class Pattern : public std::enable_shared_from_this<Pattern>{
    public:
        Pattern();
        virtual ~Pattern();
        Pattern(Color c1, Color  c2);

        virtual Color patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const = 0;
        virtual Color patternAt(const Tuple &p) const = 0;

        void setPatternTransform(const Transform &t);
        Transform getPatternTransform() const;

        bool hasPattern;

        Color c1;
        Color c2;

    private:
        Transform transformMat;
        std::shared_ptr<Pattern> patternPtr;
};

class TestPattern : public Pattern {
    public:
        TestPattern();
        ~TestPattern() override;

        Color patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const override;
        Color patternAt(const Tuple &p) const override;
};

class NoPattern : public Pattern {
    public:
        NoPattern();
        ~NoPattern() override;

        Color patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const override;
        Color patternAt(const Tuple &p) const override;
};

class StripePattern : public Pattern {
    public:
        StripePattern();
        ~StripePattern() override;
        StripePattern(const Color &c1, const Color& c2);

        Color patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const override;
        Color patternAt(const Tuple &p) const override;
};

class GradientPattern : public Pattern {
    public:
        GradientPattern();
        ~GradientPattern() override;
        GradientPattern(const Color &c1, const Color& c2);

        Color patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const override;
        Color patternAt(const Tuple &p) const override;
};

class RingPattern : public Pattern {
    public:
        RingPattern();
        ~RingPattern() override;
        RingPattern(const Color &c1, const Color& c2);

        Color patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const override;
        Color patternAt(const Tuple &p) const override;
};

class CheckerPattern : public Pattern {
    public:
        CheckerPattern();
        ~CheckerPattern() override;
        CheckerPattern(const Color &c1, const Color &c2);

        Color patternAtShape(const std::shared_ptr<Shape const> &s, const Tuple &p) const override;
        Color patternAt(const Tuple &p) const override;
};

} // namespace raytracer




#endif //RTC_PATTERN_H
