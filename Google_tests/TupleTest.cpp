#include "include/tuple.h"

#include "gtest/gtest.h"

#include <cmath>

class TupleFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        tuple = new raytracer::Tuple();
        t1 = new raytracer::Tuple();
        t2 = new raytracer::Tuple();
        v1 = new raytracer::Tuple();
        v2 = new raytracer::Tuple();
        c1 = new raytracer::Color();
        c2 = new raytracer::Color();
        p1 = new raytracer::Tuple();
        p2 = new raytracer::Tuple();
        result = new raytracer::Tuple();
        point = new raytracer::Tuple();
        vector = new raytracer::Tuple();
        color = new raytracer::Color();
        scalar = new double;
    }

    virtual void TearDown() {
        delete tuple;
        delete t1;
        delete t2;
        delete v1;
        delete v2;
        delete c1;
        delete c2;
        delete p1;
        delete p2;
        delete result;
        delete point;
        delete vector;
        delete color;
        delete scalar;
    }

    raytracer::Tuple * tuple;
    raytracer::Tuple * t1;
    raytracer::Tuple * t2;
    raytracer::Tuple * result;

    raytracer::Tuple * point;
    raytracer::Tuple * p1;
    raytracer::Tuple * p2;

    raytracer::Tuple * vector;
    raytracer::Tuple * v1;
    raytracer::Tuple * v2;

    raytracer::Color * color;
    raytracer::Color * c1;
    raytracer::Color * c2;

    double * scalar;
};

TEST_F(TupleFixture, IsPoint) {
    ASSERT_FALSE(point->isPoint());
}

TEST_F(TupleFixture, IsVector) {
    ASSERT_TRUE(vector->isVector());
}

TEST_F(TupleFixture, CreatePoint) {
    * point = raytracer::createPoint(1.0, 1.0, 1.0);
    ASSERT_TRUE(point->isPoint());
}

TEST_F(TupleFixture, CreateVector) {
    * vector = raytracer::createVector(1.0, 1.0, 1.0);
    ASSERT_TRUE(vector->isVector());
}

TEST_F(TupleFixture, VerifyEquality) {
    * point = raytracer::createPoint(1.0, 1.0, 1.0);
    ASSERT_TRUE(* point == * point);
}

TEST_F(TupleFixture, TupleAddition) {
    * t1 = {3, -2, 5, 1};
    * t2 = {-2, 3, 1, 0};
    * result = {1, 1, 6, 1};
    ASSERT_EQ(* result, * t1 + * t2);
}

TEST_F(TupleFixture, PointSubstraction) {
    * p1 = raytracer::createPoint(3, 2, 1);
    * p2 = raytracer::createPoint(5, 6, 7);
    * result = * p1 - * p2;
    ASSERT_TRUE(result->isVector());
}

TEST_F(TupleFixture, VectorPointSubstraction1) {
    * point = raytracer::createPoint(3, 2, 1);
    * vector = raytracer::createVector(5, 6, 7);
    * result = * point - * vector;
    ASSERT_TRUE(result->isPoint());
}

TEST_F(TupleFixture, VectorSubstraction) {
    * v1 = raytracer::createVector(3, 2, 1);
    * v2 = raytracer::createVector(5, 6, 7);
    * result = * v1 - * v2;
    ASSERT_TRUE(result->isVector());
}

TEST_F(TupleFixture, ZeroVectorSubstraction1) {
    * v1 = raytracer::createVector(0, 0, 0);
    * v2 = raytracer::createVector(1, -2, 3);
    * result = * v1 - * v2;
    ASSERT_EQ(raytracer::createVector(-1, 2, -3), * result);
}

TEST_F(TupleFixture, TupleNegation) {
    * tuple = {1, -2, 3, -4};
    * result = {-1, 2, -3, 4};
    ASSERT_EQ( * result, - * tuple);
}

TEST_F(TupleFixture, ScalarMultiplication1) {
    * tuple = {1, -2, 3, -4};
    * result = {3.5, -7, 10.5, -14};
    ASSERT_EQ(* result, * tuple * 3.5);
}

TEST_F(TupleFixture, ScalarMultiplication2) {
    * t1 = {1, -2, 3, -4};
    * t2 = {3.5, 3.5, 3.5, 0};
    * result = {3.5, -7, 10.5, 0};
    ASSERT_EQ(* result, * t1 * * t2);
}

TEST_F(TupleFixture, ScalarFractionMultiplication) {
    * tuple = {1, -2, 3, -4};
    * result = {0.5, -1, 1.5, -2};
    ASSERT_EQ(* result, * tuple * 0.5);
}

TEST_F(TupleFixture, ScalarDivision) {
    * tuple = {1, -2, 3, -4};
    * result = {0.5, -1, 1.5, -2};
    ASSERT_EQ(* result, * tuple / 2.0);
}

TEST_F(TupleFixture, Magnitude1) {
    * vector = raytracer::createVector(1, 0, 0);
    ASSERT_EQ(1.0, magnitude(* vector));
}

TEST_F(TupleFixture, Magnitude2) {
    * vector = raytracer::createVector(0, 1, 0);
    ASSERT_EQ(1.0, magnitude(* vector));
}

TEST_F(TupleFixture, Magnitude3) {
    * vector = raytracer::createVector(0, 0, 1);
    ASSERT_EQ(1.0, magnitude(* vector));
}

TEST_F(TupleFixture, Magnitude4) {
    * vector = raytracer::createVector(1, 2, 3);
    ASSERT_EQ(sqrt(14), magnitude(* vector));
}

TEST_F(TupleFixture, Magnitude5) {
    * vector = raytracer::createVector(-1, -2,-3);
    ASSERT_EQ(sqrt(14), magnitude(* vector));
}

TEST_F(TupleFixture, Normalize) {
    * vector = raytracer::createVector(4, 0, 0);
    * result = raytracer::createVector(1, 0, 0);
    ASSERT_EQ(* result, normalize(* vector));
}

TEST_F(TupleFixture, DotProduct1) {
    * v1 = raytracer::createVector(1, 2, 3);
    * v2 = raytracer::createVector(2, 3, 4);
    ASSERT_EQ(20.0, dot(* v1, * v2));
}

TEST_F(TupleFixture, CrossProduct1) {
    * v1 = raytracer::createVector(1, 2, 3);
    * v2 = raytracer::createVector(2, 3, 4);
    * result = raytracer::createVector(-1, 2, -1);
    ASSERT_EQ(* result, cross(* v1, * v2));
}

TEST_F(TupleFixture, CrossProduct2) {
    * v1 = raytracer::createVector(1, 2, 3);
    * v2 = raytracer::createVector(2, 3, 4);
    * result = raytracer::createVector(1, -2, 1);
    ASSERT_EQ(* result, cross(* v2, * v1));
}

TEST_F(TupleFixture, SimpleColorTest) {
    * color = raytracer::Color(-0.5, 0.4, 1.7);
    ASSERT_EQ(-0.5, color->r);
    ASSERT_EQ(0.4, color->g);
    ASSERT_EQ(1.7, color->b);
}

TEST_F(TupleFixture, ColorEquality) {
    * c1 = raytracer::Color(0.9, 0.6, 0.75);
    * c2 = raytracer::Color(0.9, 0.6, 0.75);
    ASSERT_EQ(* c1, * c2);
}

TEST_F(TupleFixture, AddingColors) {
    * c1 = raytracer::Color(0.9, 0.6, 0.75);
    * c2 = raytracer::Color(0.7, 0.1, 0.25);
    ASSERT_EQ(raytracer::Color(1.6, 0.7, 1.0), * c1 + * c2);
}

TEST_F(TupleFixture, SubtractingColor) {
    * c1 = raytracer::Color(0.9, 0.6, 0.75);
    * c2 = raytracer::Color(0.7, 0.1, 0.25);
    EXPECT_EQ(raytracer::Color(0.2, 0.5, 0.5), * c1 - * c2);
}

TEST_F(TupleFixture, MultiplyingScalarColors) {
    * c1 = raytracer::Color(0.2, 0.3, 0.4);
    ASSERT_EQ(raytracer::Color(0.4, 0.6, 0.8), * c1 * 2.0);
}


TEST_F(TupleFixture, MultiplyingColors) {
    * c1 = raytracer::Color(1.0, 0.2, 0.4);
    * c2 = raytracer::Color(0.9, 1.0, 0.1);
    ASSERT_EQ(raytracer::Color(0.9, 0.2, 0.04), * c1 * * c2);
}

TEST_F(TupleFixture, ReflectingVector45) {
    * v1 = raytracer::createVector(1, -1, 0);
    * v2 = raytracer::createVector(0, 1, 0);
    * result = raytracer::createVector(1, 1, 0);
    ASSERT_EQ(* result, reflect(* v1, * v2));
}

TEST_F(TupleFixture, ReflectingVectorSlanted) {
    * v1 = raytracer::createVector(0, -1, 0);
    * v2 = raytracer::createVector(sqrt(2) / 2, sqrt(2) / 2, 0);
    * result = raytracer::createVector(1, 0, 0);
    ASSERT_EQ(* result, reflect(* v1, * v2));
}
