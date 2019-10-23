#include "include/tuple.h"

#include "gtest/gtest.h"

#include <cmath>

class TupleFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        tuple = new raytracer::Tuple();
        color = new raytracer::Color();
    }

    virtual void TearDown() {
        delete tuple;
    }

    raytracer::Tuple * tuple;
    raytracer::Tuple tuplePoint;
    raytracer::Tuple tupleVector;

    raytracer::Point point;
    raytracer::Point p1;
    raytracer::Point p2;

    raytracer::Vector vector;
    raytracer::Vector v1;
    raytracer::Vector v2;

    raytracer::Tuple t1;
    raytracer::Tuple t2;
    raytracer::Tuple result;
    raytracer::Tuple difference;

    raytracer::Color * color;
    raytracer::Color c1;
    raytracer::Color c2;
    raytracer::Color colorResult;
    raytracer::Color colorDif;

    double scalar;
    double doubleResult;
};

TEST_F(TupleFixture, IsPoint) {
    ASSERT_FALSE(tuple->isPoint());
}

TEST_F(TupleFixture, IsVector) {
    ASSERT_TRUE(tuple->isVector());
}

TEST_F(TupleFixture, CreatePoint1) {
    tuplePoint = raytracer::createPoint(1.0, 1.0, 1.0);
    ASSERT_TRUE(tuplePoint.isPoint());
}

TEST_F(TupleFixture, CreatePoint2) {
    point = raytracer::Point(1.0, 1.0, 1.0);
    ASSERT_TRUE(point.isPoint());
}

TEST_F(TupleFixture, CreateVector1) {
    tupleVector = raytracer::createVector(1.0, 1.0, 1.0);
    ASSERT_TRUE(tupleVector.isVector());
}

TEST_F(TupleFixture, CreateVector2) {
    vector = raytracer::Vector(1.0, 1.0, 1.0);
    ASSERT_TRUE(vector.isVector());
}

//TEST_F(TupleFixture, VerifyEquality1) {
//    tuplePoint = raytracer::createPoint(1.0, 1.0, 1.0);
//    ASSERT_TRUE(isEqual(tuplePoint, tuplePoint));
//}
//
//TEST_F(TupleFixture, VerifyEquality2) {
//    point = raytracer::Point(1.0, 1.0, 1.0);
//    ASSERT_TRUE(isEqual(point, point));
//}

TEST_F(TupleFixture, VerifyEquality1) {
    tuplePoint = raytracer::createPoint(1.0, 1.0, 1.0);
    ASSERT_TRUE(tuplePoint == tuplePoint);
}

TEST_F(TupleFixture, VerifyEquality2) {
    point = raytracer::Point(1.0, 1.0, 1.0);
    ASSERT_TRUE(tuplePoint == tuplePoint);
}

TEST_F(TupleFixture, TupleAddition) {
    t1 = {3, -2, 5, 1};
    t2 = {-2, 3, 1, 0};
    result = {1, 1, 6, 1};
    ASSERT_EQ(result, t1 + t2);
}

TEST_F(TupleFixture, PointSubstraction1) {
    t1 = raytracer::createPoint(3, 2, 1);
    t2 = raytracer::createPoint(5, 6, 7);
    difference = t1 - t2;
    ASSERT_TRUE(difference.isVector());
}

TEST_F(TupleFixture, PointSubstraction2) {
    p1 = raytracer::Point(3, 2, 1);
    p2 = raytracer::Point(5, 6, 7);
    difference = p1 - p2;
    std::cout << difference;
    ASSERT_TRUE(difference.isVector());
}

TEST_F(TupleFixture, VectorPointSubstraction1) {
    t1 = raytracer::createPoint(3, 2, 1);
    t2 = raytracer::createVector(5, 6, 7);
    difference = t1 - t2;
    ASSERT_TRUE(difference.isPoint());
}

TEST_F(TupleFixture, VectorPointSubstraction2) {
    p1 = raytracer::Point(3, 2, 1);
    v2 = raytracer::Vector(5, 6, 7);
    difference = p1 - v2;
    ASSERT_TRUE(difference.isPoint());
}

TEST_F(TupleFixture, VectorSubstraction1) {
    t1 = raytracer::createVector(3, 2, 1);
    t2 = raytracer::createVector(5, 6, 7);
    difference = t1 - t2;
    ASSERT_TRUE(difference.isVector());
}

TEST_F(TupleFixture, VectorSubstraction2) {
    v1 = raytracer::Vector(3, 2, 1);
    v2 = raytracer::Vector(5, 6, 7);
    difference = v1 - v2;
    ASSERT_TRUE(difference.isVector());
}

TEST_F(TupleFixture, ZeroVectorSubstraction1) {
    t1 = raytracer::createVector(0, 0, 0);
    t2 = raytracer::createVector(1, -2, 3);
    difference = t1 - t2;
    result = raytracer::createVector(-1, 2, -3);
    ASSERT_EQ(result, difference);
}

TEST_F(TupleFixture, ZeroVectorSubstraction2) {
    v1 = raytracer::Vector(0, 0, 0);
    v2 = raytracer::Vector(1, -2, 3);
    difference = v1 - v2;
    result = raytracer::createVector(-1, 2, -3);
    ASSERT_EQ(result, difference);
}

TEST_F(TupleFixture, TupleNegation) {
    t1 = {1, -2, 3, -4};
    result = {-1, 2, -3, 4};
    ASSERT_EQ(result, -t1);
}

TEST_F(TupleFixture, ScalarMultiplication1) {
    t1 = {1, -2, 3, -4};
    scalar = 3.5;
    result = {3.5, -7, 10.5, -14};
    ASSERT_EQ(result, t1 * scalar);
}

TEST_F(TupleFixture, ScalarMultiplication2) {
    t1 = {1, -2, 3, -4};
    t2 = {3.5, 3.5, 3.5, 0};
    result = {3.5, -7, 10.5, 0};
    ASSERT_EQ(result, t1 * t2);
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
    v1 = raytracer::Vector(1, 0, 0);
    doubleResult = 1;
    ASSERT_EQ(doubleResult, magnitude(t1));
    ASSERT_EQ(doubleResult, magnitude(v1));
}

TEST_F(TupleFixture, Magnitude2) {
    t1 = raytracer::createVector(0, 1, 0);
    v1 = raytracer::Vector(0, 1, 0);
    doubleResult = 1;
    ASSERT_EQ(doubleResult, magnitude(t1));
    ASSERT_EQ(doubleResult, magnitude(v1));
}

TEST_F(TupleFixture, Magnitude3) {
    t1 = raytracer::createVector(0, 0, 1);
    v1 = raytracer::Vector(0, 0, 1);
    doubleResult = 1;
    ASSERT_EQ(doubleResult, magnitude(t1));
    ASSERT_EQ(doubleResult, magnitude(v1));
}

TEST_F(TupleFixture, Magnitude4) {
    t1 = raytracer::createVector(1, 2, 3);
    v1 = raytracer::Vector(1, 2, 3);
    doubleResult = sqrt(14);
    ASSERT_EQ(doubleResult, magnitude(t1));
    ASSERT_EQ(doubleResult, magnitude(v1));
}

TEST_F(TupleFixture, Magnitude5) {
    t1 = raytracer::createVector(-1, -2,-3);
    v1 = raytracer::Vector(-1, -2, -3);
    doubleResult = sqrt(14);
    ASSERT_EQ(doubleResult, magnitude(t1));
    ASSERT_EQ(doubleResult, magnitude(v1));
}

TEST_F(TupleFixture, Normalize1) {
    t1 = raytracer::createVector(4, 0, 0);
    result = raytracer::createVector(1, 0, 0);
    ASSERT_EQ(result, normalize(t1));
}

TEST_F(TupleFixture, Normalize2) {
    v1 = raytracer::Vector(4, 0, 0);
    result = raytracer::createVector(1, 0, 0);
    ASSERT_EQ(result, normalize(v1));
}

TEST_F(TupleFixture, DotProduct1) {
    t1 = raytracer::createVector(1, 2, 3);
    t2 = raytracer::createVector(2, 3, 4);
    doubleResult = 20;
    ASSERT_EQ(doubleResult, dot(t1, t2));
}

TEST_F(TupleFixture, DotProduct2) {
    v1 = raytracer::Vector(1, 2, 3);
    v2 = raytracer::Vector(2, 3, 4);
    doubleResult = 20;
    ASSERT_EQ(doubleResult, dot(v1, v2));
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

TEST_F(TupleFixture, CrossProduct3) {
    v1 = raytracer::Vector(1, 2, 3);
    v2 = raytracer::Vector(2, 3, 4);
    result = raytracer::createVector(-1, 2, -1);
    ASSERT_EQ(result, cross(v1, v2));
}

TEST_F(TupleFixture, CrossProduct4) {
    v1 = raytracer::Vector(1, 2, 3);
    v2 = raytracer::Vector(2, 3, 4);
    result = raytracer::createVector(1, -2, 1);
    ASSERT_EQ(result, cross(v2, v1));
}

TEST_F(TupleFixture, SimpleColorTest) {
    * color = raytracer::Color(-0.5, 0.4, 1.7);
    ASSERT_EQ(-0.5, * color->r);
    ASSERT_EQ(0.4, * color->g);
    ASSERT_EQ(1.7, * color->b);
}

TEST_F(TupleFixture, ColorEquality) {
    c1 = raytracer::Color(0.9, 0.6, 0.75);
    c2 = raytracer::Color(0.9, 0.6, 0.75);
    ASSERT_EQ(c1, c2);
}

TEST_F(TupleFixture, AddingColors) {
    c1 = raytracer::Color(0.9, 0.6, 0.75);
    c2 = raytracer::Color(0.7, 0.1, 0.25);
    ASSERT_EQ(raytracer::Color(1.6, 0.7, 1.0), c1 + c2);
}

TEST_F(TupleFixture, SubtractingColor) {
    c1 = raytracer::Color(0.9, 0.6, 0.75);
    c2 = raytracer::Color(0.7, 0.1, 0.25);
    EXPECT_EQ(raytracer::Color(0.2, 0.5, 0.5), c1 - c2);
}

TEST_F(TupleFixture, MultiplyingScalarColors) {
    c1 = raytracer::Color(0.2, 0.3, 0.4);
    ASSERT_EQ(raytracer::Color(0.4, 0.6, 0.8), c1 * 2.0);
}


TEST_F(TupleFixture, MultiplyingColors) {
    c1 = raytracer::Color(1.0, 0.2, 0.4);
    c2 = raytracer::Color(0.9, 1.0, 0.1);
    ASSERT_EQ(raytracer::Color(0.9, 0.2, 0.04), c1 * c2);
}

TEST_F(TupleFixture, ReflectingVector45) {
    vector = raytracer::Vector(1, -1, 0);
    v1 = raytracer::Vector(0, 1, 0);
    v2 = reflect(vector, v1);
    ASSERT_EQ(v2, raytracer::Vector(1, 1, 0));
}

TEST_F(TupleFixture, ReflectingVectorSlanted) {
    vector = raytracer::Vector(0, -1, 0);
    v1 = raytracer::Vector(sqrt(2) / 2, sqrt(2) / 2, 0);
    v2 = reflect(vector, v1);
    ASSERT_EQ(v2, raytracer::Vector(1, 0, 0));
}
