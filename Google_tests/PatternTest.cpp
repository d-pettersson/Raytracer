#include "include/pattern.h"
#include "include/sphere.h"

#include "gtest/gtest.h"

class PatternFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        transform = new raytracer::Transform();
        scaling = new raytracer::Transform();
        translate = new raytracer::Transform();
        color = new raytracer::Color();
    }

    virtual void TearDown() {
        delete transform;
        delete scaling;
        delete translate;
        delete color;
    }

    std::shared_ptr<raytracer::Pattern> pattern;
    std::shared_ptr<raytracer::Shape> sphere = std::make_shared<raytracer::Sphere>();
    raytracer::Transform * transform;
    raytracer::Transform * scaling;
    raytracer::Transform * translate;
    raytracer::Color * color;
};

TEST_F(PatternFixture, createStripePattern) {
    pattern = std::make_shared<raytracer::StripePattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->c1, raytracer::Color(1, 1, 1));
    ASSERT_EQ(pattern->c2, raytracer::Color(0, 0, 0));
}

TEST_F(PatternFixture, StripePatternConstantInY) {
    pattern = std::make_shared<raytracer::StripePattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 1, 0)), raytracer::Color(1, 1, 1));
    ASSERT_EQ(pattern->patternAt(raytracer::Point(0, 2, 0)), raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripePatternConstantInZ) {
    pattern = std::make_shared<raytracer::StripePattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 0, 1)), raytracer::Color(1, 1, 1));
    ASSERT_EQ(pattern->patternAt(raytracer::Point(0, 0, 2)), raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripePatternAlternatesX) {
    pattern = std::make_shared<raytracer::StripePattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0.9, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(1, 0, 0)), raytracer::Color(0, 0, 0));
    ASSERT_EQ(pattern->patternAt(raytracer::Point(-0.1, 0, 0)), raytracer::Color(0, 0, 0));
    ASSERT_EQ(pattern->patternAt(raytracer::Point(-1, 0, 0)), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(-1.1, 0, 0)), raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripesWithObjectTransformation) {
    sphere->setTransform(scaling->scale(2, 2, 2));
    pattern = std::make_shared<raytracer::StripePattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    * color = pattern->patternAtShape(sphere, raytracer::Point(1.5, 0, 0));
    ASSERT_EQ(* color, raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripesWithPatternTransformation) {
    sphere->setTransform(scaling->scale(2, 2, 2));
    pattern = std::make_shared<raytracer::StripePattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    pattern->setPatternTransform(scaling->scale(2, 2, 2));
    * color = pattern->patternAtShape(sphere, raytracer::Point(1.5, 0, 0));
    ASSERT_EQ(* color, raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, StripesWithObjectAndPatternTransformation) {
    sphere->setTransform(scaling->scale(2, 2, 2));
    pattern = std::make_shared<raytracer::StripePattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    pattern->setPatternTransform(translate->translate(0.5, 0, 0));
    * color = pattern->patternAtShape(sphere, raytracer::Point(2.5, 0, 0));
    ASSERT_EQ(* color, raytracer::Color(1, 1, 1));
}

TEST_F(PatternFixture, DefaultPatternTransformation) {
    pattern = std::make_shared<raytracer::TestPattern>();
    auto identity = raytracer::generateIdentity(4, 4);
    ASSERT_EQ(identity, pattern->getPatternTransform());
}

TEST_F(PatternFixture, PatternWithObjectTransformation) {
    pattern = std::make_shared<raytracer::TestPattern>();
    pattern->setPatternTransform(translate->translate(1, 2, 3));
    ASSERT_EQ(pattern->getPatternTransform(), translate->translate(1, 2, 3));
}

TEST_F(PatternFixture, ObjectTransformation) {
    sphere->setTransform(scaling->scale(2, 2, 2));
    pattern = std::make_shared<raytracer::TestPattern>();
    * color = pattern->patternAtShape(sphere, raytracer::Point(2, 3, 4));
    ASSERT_EQ(* color, raytracer::Color(1, 1.5, 2));
}

TEST_F(PatternFixture, PatternTransformation) {
    pattern = std::make_shared<raytracer::TestPattern>();
    pattern->setPatternTransform(scaling->scale(2, 2, 2));
    * color = pattern->patternAtShape(sphere, raytracer::Point(2, 3, 4));
    ASSERT_EQ(* color, raytracer::Color(1, 1.5, 2));
}

TEST_F(PatternFixture, ObjectAndPatternTransformation) {
    sphere->setTransform(scaling->scale(2, 2, 2));
    pattern = std::make_shared<raytracer::TestPattern>();
    pattern->setPatternTransform(translate->translate(0.5, 1, 1.5));
    * color = pattern->patternAtShape(sphere, raytracer::Point(2.5, 3, 3.5));
    ASSERT_EQ(* color, raytracer::Color(0.75, 0.5, 0.25));
}

TEST_F(PatternFixture, GradientPattern) {
    pattern = std::make_shared<raytracer::GradientPattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0.25, 0, 0)), raytracer::Color(0.75, 0.75, 0.75));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0.5, 0, 0)), raytracer::Color(0.5, 0.5, 0.5));
    ASSERT_EQ(pattern->patternAt(raytracer::Point(0.75, 0, 0)), raytracer::Color(0.25, 0.25, 0.25));
}

TEST_F(PatternFixture, RingPattern) {
    pattern = std::make_shared<raytracer::RingPattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(1, 0, 0)), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 0, 1)), raytracer::Color(0, 0, 0));
    ASSERT_EQ(pattern->patternAt(raytracer::Point(0.708, 0, 0.708)), raytracer::Color(0, 0, 0));
}

TEST_F(PatternFixture, CheckerPatternRepeatX) {
    pattern = std::make_shared<raytracer::CheckerPattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0.99, 0, 0)), raytracer::Color(1, 1, 1));
    ASSERT_EQ(pattern->patternAt(raytracer::Point(1.01, 0, 0)), raytracer::Color(0, 0, 0));
}

TEST_F(PatternFixture, CheckerPatternRepeatY) {
    pattern = std::make_shared<raytracer::CheckerPattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 0.99, 0)), raytracer::Color(1, 1, 1));
    ASSERT_EQ(pattern->patternAt(raytracer::Point(0, 1.01, 0)), raytracer::Color(0, 0, 0));
}

TEST_F(PatternFixture, CheckerPatternRepeatZ) {
    pattern = std::make_shared<raytracer::CheckerPattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 0, 0)), raytracer::Color(1, 1, 1));
    EXPECT_EQ(pattern->patternAt(raytracer::Point(0, 0, 0.99)), raytracer::Color(1, 1, 1));
    ASSERT_EQ(pattern->patternAt(raytracer::Point(0, 0, 1.01)), raytracer::Color(0, 0, 0));
}