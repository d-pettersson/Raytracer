#include "pattern.h"
#include "sphere.h"

#include "gtest/gtest.h"

class PatternFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        pattern = new raytracer::Pattern();
        transform = new raytracer::Transform();
        scaling = new raytracer::Transform();
        translate = new raytracer::Transform();
        color = new raytracer::Color();
    }

    virtual void TearDown() {
        delete pattern;
        delete transform;
        delete scaling;
        delete translate;
        delete color;
    }

    raytracer::Pattern * pattern;
    std::shared_ptr<raytracer::Shape> sphere = std::make_shared<raytracer::Sphere>();
    raytracer::Transform * transform;
    raytracer::Transform * scaling;
    raytracer::Transform * translate;
    raytracer::Color * color;
};

TEST_F(PatternFixture, createStripePattern) {
    pattern->createStripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->c1, raytracer::Color(1, 1, 1));
    ASSERT_EQ(pattern->c2, raytracer::Color(0, 0, 0));
}

TEST_F(PatternFixture, StripePatternConstantInY) {
    pattern->createStripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->stripeAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->stripeAt(raytracer::Point(0, 1, 0)), raytracer::Color(1, 1, 1));
    ASSERT_EQ(pattern->stripeAt(raytracer::Point(0, 2, 0)), raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripePatternConstantInZ) {
    pattern->createStripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->stripeAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->stripeAt(raytracer::Point(0, 0, 1)), raytracer::Color(1, 1, 1));
    ASSERT_EQ(pattern->stripeAt(raytracer::Point(0, 0, 2)), raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripePatternAlternatesX) {
    pattern->createStripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->stripeAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->stripeAt(raytracer::Point(0.9, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->stripeAt(raytracer::Point(1, 0, 0)), raytracer::Color(0, 0, 0));
    ASSERT_EQ(pattern->stripeAt(raytracer::Point(-0.1, 0, 0)), raytracer::Color(0, 0, 0));
    ASSERT_EQ(pattern->stripeAt(raytracer::Point(-1, 0, 0)), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->stripeAt(raytracer::Point(-1.1, 0, 0)), raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripesWithObjectTransformation) {
    sphere->setTransform(scaling->scale(2, 2, 2));
    pattern->createStripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    * color = pattern->stripeAtObject(sphere, raytracer::Point(1.5, 0, 0));
    ASSERT_EQ(* color, raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripesWithPatternTransformation) {
    sphere->setTransform(scaling->scale(2, 2, 2));
    pattern->createStripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    pattern->setPatternTransform(scaling->scale(2, 2, 2));
    * color = pattern->stripeAtObject(sphere, raytracer::Point(1.5, 0, 0));
    ASSERT_EQ(* color, raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripesWithObjectAndPatternTransformation) {
    sphere->setTransform(scaling->scale(2, 2, 2));
    pattern->createStripePattern(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    pattern->setPatternTransform(translate->translate(0.5, 0, 0));
    * color = pattern->stripeAtObject(sphere, raytracer::Point(2.5, 0, 0));
    ASSERT_EQ(* color, raytracer::Color(1, 1, 1));
}