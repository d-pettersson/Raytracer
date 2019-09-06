#include "../RTC_lib/Tuple.h"

#include "gtest/gtest.h"

#include <cmath>

class TupleFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        tuple = new raytracer::Tuple();
    }

    virtual void TearDown() {
        delete tuple;
    }

    raytracer::Tuple * tuple;
    raytracer::Tuple point;
    raytracer::Tuple vector;
    raytracer::Tuple t1;
    raytracer::Tuple t2;
    raytracer::Tuple result;
    raytracer::Tuple difference;
    double scalar;
    double doubleResult;
};

TEST_F(TupleFixture, IsPoint) {
    ASSERT_FALSE(tuple->isPoint());
}

TEST_F(TupleFixture, IsVector) {
    ASSERT_TRUE(tuple->isVector());
}

TEST_F(TupleFixture, CreatePoint) {
    point = raytracer::createPoint(1.0, 1.0, 1.0);
    ASSERT_TRUE(point.isPoint());
}

TEST_F(TupleFixture, CreateVector) {
    vector = raytracer::createVector(1.0, 1.0, 1.0);
    ASSERT_TRUE(vector.isVector());
}

TEST_F(TupleFixture, VerifyEquality) {
    point = raytracer::createPoint(1.0, 1.0, 1.0);
    ASSERT_TRUE(isEqual(point, point));
}

TEST_F(TupleFixture, TupleAddition) {
    t1 = {3, -2, 5, 1};
    t2 = {-2, 3, 1, 0};
    result = {1, 1, 6, 1};
    ASSERT_EQ(result, t1 + t2);
}

TEST_F(TupleFixture, PointSubstraction) {
    t1 = raytracer::createPoint(3, 2, 1);
    t2 = raytracer::createPoint(5, 6, 7);
    difference = t1 - t2;
    ASSERT_TRUE(difference.isVector());
}

TEST_F(TupleFixture, VectorPointSubstraction) {
    t1 = raytracer::createPoint(3, 2, 1);
    t2 = raytracer::createVector(5, 6, 7);
    difference = t1 - t2;
    ASSERT_TRUE(difference.isPoint());
}

TEST_F(TupleFixture, VectorSubstraction) {
    t1 = raytracer::createVector(3, 2, 1);
    t2 = raytracer::createVector(5, 6, 7);
    difference = t1 - t2;
    ASSERT_TRUE(difference.isVector());
}

TEST_F(TupleFixture, ZeroVectorSubstraction) {
    t1 = raytracer::createVector(0, 0, 0);
    t2 = raytracer::createVector(1, -2, 3);
    difference = t1 - t2;
    result = raytracer::createVector(-1, 2, -3);
    ASSERT_EQ(result, difference);
}

TEST_F(TupleFixture, TupleNegation) {
    t1 = {1, -2, 3, -4};
    result = {-1, 2, -3, 4};
    ASSERT_EQ(result, -t1);
}

TEST_F(TupleFixture, ScalarMultiplication) {
    t1 = {1, -2, 3, -4};
    scalar = 3.5;
    result = {3.5, -7, 10.5, -14};
    ASSERT_EQ(result, t1 * scalar);
}

TEST_F(TupleFixture, ScalarFractionMultiplication) {
    t1 = {1, -2, 3, -4};
    scalar = 0.5;
    result = {0.5, -1, 1.5, -2};
    ASSERT_EQ(result, t1 * scalar);
}

TEST_F(TupleFixture, ScalarDivision) {
    t1 = {1, -2, 3, -4};
    scalar = 2;
    result = {0.5, -1, 1.5, -2};
    ASSERT_EQ(result, t1 / scalar);
}

TEST_F(TupleFixture, Magnitude1) {
    t1 = raytracer::createVector(1, 0, 0);
    doubleResult = 1;
    ASSERT_EQ(doubleResult, magnitude(t1));
}

TEST_F(TupleFixture, Magnitude2) {
    t1 = raytracer::createVector(0, 1, 0);
    doubleResult = 1;
    ASSERT_EQ(doubleResult, magnitude(t1));
}

TEST_F(TupleFixture, Magnitude3) {
    t1 = raytracer::createVector(0, 0, 1);
    doubleResult = 1;
    ASSERT_EQ(doubleResult, magnitude(t1));
}

TEST_F(TupleFixture, Magnitude4) {
    t1 = raytracer::createVector(1, 2, 3);
    doubleResult = sqrt(14);
    ASSERT_EQ(doubleResult, magnitude(t1));
}

TEST_F(TupleFixture, Magnitude5) {
    t1 = raytracer::createVector(-1, -2,-3);
    doubleResult = sqrt(14);
    ASSERT_EQ(doubleResult, magnitude(t1));
}

TEST_F(TupleFixture, Normalize) {
    t1 = raytracer::createVector(4, 0, 0);
    result = raytracer::createVector(1, 0, 0);
    ASSERT_EQ(result, normalize(t1));
}

TEST_F(TupleFixture, DotProduct) {
    t1 = raytracer::createVector(1, 2, 3);
    t2 = raytracer::createVector(2, 3, 4);
    doubleResult = 20;
    ASSERT_EQ(doubleResult, dot(t1, t2));
}

TEST_F(TupleFixture, CrossProduct1) {
    t1 = raytracer::createVector(1, 2, 3);
    t2 = raytracer::createVector(2, 3, 4);
    result = raytracer::createVector(-1, 2, -1);
    ASSERT_EQ(result, cross(t1, t2));
}

TEST_F(TupleFixture, CrossProduct2) {
    t1 = raytracer::createVector(1, 2, 3);
    t2 = raytracer::createVector(2, 3, 4);
    result = raytracer::createVector(1, -2, 1);
    ASSERT_EQ(result, cross(t2, t1));
}