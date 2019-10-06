#include "transform.h"

#include <cmath>

#include "gtest/gtest.h"


class TransformFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        trans = new raytracer::Transform();
        inv = new raytracer::Transform();
        transA = new raytracer::Transform();
        transB = new raytracer::Transform();
        transC = new raytracer::Transform();
        transT = new raytracer::Transform();
        p1 = new raytracer::Point();
        p2 = new raytracer::Point();
        p3 = new raytracer::Point();
        p4 = new raytracer::Point();
        from = new raytracer::Point();
        to = new raytracer::Point();
        up = new raytracer::Vector();
        identity = new raytracer::Matrix();
        matrix = new raytracer::Matrix(4, 4);
    }

    virtual void TearDown() {
        delete trans;
        delete inv;
        delete transA;
        delete transB;
        delete transC;
        delete transT;
        delete from;
        delete to;
        delete up;
        delete identity;
        delete matrix;
    }

    raytracer::Transform * trans;
    raytracer::Transform * transA;
    raytracer::Transform * transB;
    raytracer::Transform * transC;
    raytracer::Transform * transT;
    raytracer::Transform * inv;

    raytracer::Point point;
    raytracer::Point * p1;
    raytracer::Point * p2;
    raytracer::Point * p3;
    raytracer::Point * p4;
    raytracer::Point * from;
    raytracer::Point * to;
    raytracer::Point pointMultResult;
    raytracer::Point pointResult;

    raytracer::Vector vector;
    raytracer::Vector * up;
    raytracer::Vector vecMultResult;
    raytracer::Vector vectorResult;

    raytracer::Matrix * identity;
    raytracer::Matrix * matrix;
};

TEST_F(TransformFixture, PointTranslationTest) {
    trans->translate(5, -3, 2);
    point = raytracer::Point(-3, 4, 5);
    pointMultResult = * trans * point;
    pointResult = raytracer::Point(2, 1, 7);
    ASSERT_EQ(pointResult, pointMultResult);
}

TEST_F(TransformFixture, InvTranslationTest) {
    trans->translate(5, -3, 2);
    * inv = inverse(* trans);
    point = raytracer::Point(-3, 4, 5);
    pointMultResult = * inv * point;
    pointResult = raytracer::Point(-8, 7, 3);
    ASSERT_EQ(pointResult, pointMultResult);
}

TEST_F(TransformFixture, VectorTranslationTest) {
    trans->translate(5, -3, 2);
    vector = raytracer::Vector(-3, 4, 5);
    vecMultResult = * trans * vector;
    vectorResult = raytracer::Vector(-3, 4, 5);
    ASSERT_EQ(vectorResult, vecMultResult);
}

TEST_F(TransformFixture, PointScaleTest) {
    trans->scale(2, 3, 4);
    point = raytracer::Point(-4, 6, 8);
    pointMultResult = * trans * point;
    pointResult = raytracer::Point(-8, 18, 32);
    ASSERT_EQ(pointResult, pointMultResult);
}

TEST_F(TransformFixture, VectorScaleTest) {
    trans->scale(2, 3, 4);
    vector = raytracer::Vector(-4, 6, 8);
    vecMultResult = * trans * vector;
    vectorResult = raytracer::Vector(-8, 18, 32);
    ASSERT_EQ(vectorResult, vecMultResult);
}

TEST_F(TransformFixture, InvScalingTest) {
    trans->scale(2, 3, 4);
    * inv = inverse(* trans);
    vector = raytracer::Vector(-4, 6, 8);
    vecMultResult = * inv * vector;
    vectorResult = raytracer::Vector(-2, 2, 2);
    ASSERT_EQ(vectorResult, vecMultResult);
}

TEST_F(TransformFixture, ReflectionTest) {
    trans->scale(-1, 1, 1);
    point = raytracer::Point(2, 3, 4);
    pointMultResult = * trans * point;
    pointResult = raytracer::Point(-2, 3, 4);
    ASSERT_EQ(pointResult, pointMultResult);
}

TEST_F(TransformFixture, RotationXTest) {
    raytracer::Transform halfQuarterRot = trans->rotateX(PI / 4);
    raytracer::Transform fullQuarterRot = trans->rotateX(PI / 2);
    point = raytracer::Point(0, 1, 0);
    ASSERT_EQ(raytracer::Point(0, sqrt(2)/2, sqrt(2)/2), halfQuarterRot * point);
    ASSERT_EQ(raytracer::Point(0, 0, 1), fullQuarterRot * point);
}

TEST_F(TransformFixture, InverseRotationXTest) {
    raytracer::Transform halfQuarterRot = trans->rotateX(PI / 4);
    point = raytracer::Point(0, 1, 0);
    ASSERT_EQ(raytracer::Point(0, sqrt(2)/2, -sqrt(2)/2), inverse(halfQuarterRot) * point);
}

TEST_F(TransformFixture, RotationYTest) {
    raytracer::Transform halfQuarterRot = trans->rotateY(PI / 4);
    raytracer::Transform fullQuarterRot = trans->rotateY(PI / 2);
    point = raytracer::Point(0, 0, 1);
    ASSERT_EQ(raytracer::Point(sqrt(2)/2, 0, sqrt(2)/2), halfQuarterRot * point);
    ASSERT_EQ(raytracer::Point(1, 0, 0), fullQuarterRot * point);
}

TEST_F(TransformFixture, RotationZTest) {
    raytracer::Transform halfQuarterRot = trans->rotateZ(PI / 4);
    raytracer::Transform fullQuarterRot = trans->rotateZ(PI / 2);
    point = raytracer::Point(0, 1, 0);
    ASSERT_EQ(raytracer::Point(-sqrt(2)/2, sqrt(2)/2, 0), halfQuarterRot * point);
    ASSERT_EQ(raytracer::Point(-1, 0, 0), fullQuarterRot * point);
}

TEST_F(TransformFixture, Shearing1) {
    trans->shear(1, 0, 0, 0, 0, 0);
    point = raytracer::Point(2, 3, 4);
    pointMultResult = * trans * point;
    pointResult = raytracer::Point(5, 3, 4);
    ASSERT_EQ(pointResult, pointMultResult);
}

TEST_F(TransformFixture, Shearing2) {
    trans->shear(0, 1, 0, 0, 0, 0);
    point = raytracer::Point(2, 3, 4);
    pointMultResult = * trans * point;
    pointResult = raytracer::Point(6, 3, 4);
    ASSERT_EQ(pointResult, pointMultResult);
}

TEST_F(TransformFixture, Shearing3) {
    trans->shear(0, 0, 1, 0, 0, 0);
    point = raytracer::Point(2, 3, 4);
    pointMultResult = * trans * point;
    pointResult = raytracer::Point(2, 5, 4);
    ASSERT_EQ(pointResult, pointMultResult);
}

TEST_F(TransformFixture, Shearing4) {
    trans->shear(0, 0, 0, 1, 0, 0);
    point = raytracer::Point(2, 3, 4);
    pointMultResult = * trans * point;
    pointResult = raytracer::Point(2, 7, 4);
    ASSERT_EQ(pointResult, pointMultResult);
}

TEST_F(TransformFixture, Shearing5) {
    trans->shear(0, 0, 0, 0, 1, 0);
    point = raytracer::Point(2, 3, 4);
    pointMultResult = * trans * point;
    pointResult = raytracer::Point(2, 3, 6);
    ASSERT_EQ(pointResult, pointMultResult);
}

TEST_F(TransformFixture, Shearing6) {
    trans->shear(0, 0, 0, 0, 0, 1);
    point = raytracer::Point(2, 3, 4);
    pointMultResult = * trans * point;
    pointResult = raytracer::Point(2, 3, 7);
    ASSERT_EQ(pointResult, pointMultResult);
}

TEST_F(TransformFixture, ChainingTransforms) {
    point = raytracer::Point(1, 0, 1);
    transA->rotateX(PI / 2);
    transB->scale(5, 5, 5);
    transC->translate(10, 5, 7);
    * p2 = * transA * point;
    ASSERT_EQ(raytracer::Point(1, -1, 0), * p2);
    * p3 = * transB * * p2;
    ASSERT_EQ(raytracer::Point(5, -5, 0), * p3);
    * p4 = * transC * * p3;
    ASSERT_EQ(raytracer::Point(15, 0, 7), * p4);
}

TEST_F(TransformFixture, ReverseChainedTransforms) {
    point = raytracer::Point(1, 0, 1);
    transA->rotateX(PI / 2);
    transB->scale(5, 5, 5);
    transC->translate(10, 5, 7);
    * transT = * transC * * transB * * transA;
    ASSERT_EQ(raytracer::Point(15, 0, 7), * transT * point);
}

TEST_F(TransformFixture, DefaultOrientation) {
    * from = raytracer::Point(0, 0, 0);
    * to = raytracer::Point(0, 0, -1);
    * up = raytracer::Vector(0, 1, 0);
    * trans = viewTransform(* from, * to, * up);
    * identity = raytracer::generateIdentity(4, 4);
    ASSERT_EQ(* identity, * trans);
}

TEST_F(TransformFixture, ViewTransformPositiveZDirection) {
    * from = raytracer::Point(0, 0, 0);
    * to = raytracer::Point(0, 0, 1);
    * up = raytracer::Vector(0, 1, 0);
    * trans = viewTransform(* from, * to, * up);
    ASSERT_EQ(* trans, trans->scale(-1, 1, -1));
}

TEST_F(TransformFixture, ViewTransformationMovesWorld) {
    * from = raytracer::Point(0, 0, 8);
    * to = raytracer::Point(0, 0, 1);
    * up = raytracer::Vector(0, 1, 0);
    * trans = viewTransform(* from, * to, * up);
    ASSERT_EQ(* trans, trans->translate(0, 0, -8));
}

TEST_F(TransformFixture, ArbitraryViewTransformation) {
    * from = raytracer::Point(1, 3, 2);
    * to = raytracer::Point(4, -2, 8);
    * up = raytracer::Vector(1, 1, 0);
    * trans = viewTransform(* from, * to, * up);
    std::vector<double> data{-0.50709, 0.50709, 0.67612, -2.36643, 0.76772, 0.60609, 0.12122, -2.82843, -0.35857, 0.59761, -0.71714, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000};
    matrix->setMatrixData(data);
    transA = new raytracer::Transform(* matrix);
    ASSERT_EQ(* trans, * transA);
}

