#include "pattern.h"
#include "sphere.h"

#include "gtest/gtest.h"

class PatternFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        stripePattern = new raytracer::StripePattern();
        gradientPattern = new raytracer::GradientPattern();
        transform = new raytracer::Transform();
        scaling = new raytracer::Transform();
        translate = new raytracer::Transform();
        color = new raytracer::Color();
    }

    virtual void TearDown() {
        delete stripePattern;
        delete gradientPattern;
        delete transform;
        delete scaling;
        delete translate;
        delete color;
    }

    raytracer::StripePattern * stripePattern;
    raytracer::GradientPattern * gradientPattern;
    std::shared_ptr<raytracer::Shape> sphere = std::make_shared<raytracer::Sphere>();
    raytracer::Transform * transform;
    raytracer::Transform * scaling;
    raytracer::Transform * translate;
    raytracer::Color * color;
};

TEST_F(PatternFixture, createStripePattern) {
    * stripePattern = raytracer::StripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(stripePattern->c1, raytracer::Color(1, 1, 1));
    ASSERT_EQ(stripePattern->c2, raytracer::Color(0, 0, 0));
}

TEST_F(PatternFixture, StripePatternConstantInY) {
    * stripePattern = raytracer::StripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(stripePattern->patternAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(stripePattern->patternAt(raytracer::Point(0, 1, 0)), raytracer::Color(1, 1, 1));
    ASSERT_EQ(stripePattern->patternAt(raytracer::Point(0, 2, 0)), raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripePatternConstantInZ) {
    * stripePattern = raytracer::StripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(stripePattern->patternAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(stripePattern->patternAt(raytracer::Point(0, 0, 1)), raytracer::Color(1, 1, 1));
    ASSERT_EQ(stripePattern->patternAt(raytracer::Point(0, 0, 2)), raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripePatternAlternatesX) {
    * stripePattern = raytracer::StripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(stripePattern->patternAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(stripePattern->patternAt(raytracer::Point(0.9, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(stripePattern->patternAt(raytracer::Point(1, 0, 0)), raytracer::Color(0, 0, 0));
    ASSERT_EQ(stripePattern->patternAt(raytracer::Point(-0.1, 0, 0)), raytracer::Color(0, 0, 0));
    ASSERT_EQ(stripePattern->patternAt(raytracer::Point(-1, 0, 0)), raytracer::Color(0, 0, 0));
    EXPECT_EQ(stripePattern->patternAt(raytracer::Point(-1.1, 0, 0)), raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripesWithObjectTransformation) {
    sphere->setTransform(scaling->scale(2, 2, 2));
    * stripePattern = raytracer::StripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    * color = stripePattern->patternAtShape(sphere, raytracer::Point(1.5, 0, 0));
    ASSERT_EQ(* color, raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripesWithPatternTransformation) {
    sphere->setTransform(scaling->scale(2, 2, 2));
    * stripePattern = raytracer::StripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    stripePattern->setPatternTransform(scaling->scale(2, 2, 2));
    * color = stripePattern->patternAtShape(sphere, raytracer::Point(1.5, 0, 0));
    ASSERT_EQ(* color, raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripesWithObjectAndPatternTransformation) {
    sphere->setTransform(scaling->scale(2, 2, 2));
    * stripePattern = raytracer::StripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    stripePattern->setPatternTransform(translate->translate(0.5, 0, 0));
    * color = stripePattern->patternAtShape(sphere, raytracer::Point(2.5, 0, 0));
    ASSERT_EQ(* color, raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, GradientPattern) {
    * gradientPattern = raytracer::GradientPattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(gradientPattern->patternAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(gradientPattern->patternAt(raytracer::Point(0.25, 0, 0)), raytracer::Color(0.75, 0.75, 0.75));
    EXPECT_EQ(gradientPattern->patternAt(raytracer::Point(0.5, 0, 0)), raytracer::Color(0.5, 0.5, 0.5));
    ASSERT_EQ(gradientPattern->patternAt(raytracer::Point(0.75, 0, 0)), raytracer::Color(0.25, 0.25, 0.25));
}