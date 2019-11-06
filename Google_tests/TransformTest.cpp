#include "include/transform.h"

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
        fullQuarterRot = new raytracer::Transform();
        halfQuarterRot = new raytracer::Transform();
        point = new raytracer::Tuple();
        p1 = new raytracer::Tuple();
        p2 = new raytracer::Tuple();
        p3 = new raytracer::Tuple();
        p4 = new raytracer::Tuple();
        from = new raytracer::Tuple();
        to = new raytracer::Tuple();
        result = new raytracer::Tuple();
        vector = new raytracer::Tuple();
        up = new raytracer::Tuple();
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
        delete fullQuarterRot;
        delete halfQuarterRot;
        delete point;
        delete p1;
        delete p2;
        delete p3;
        delete p4;
        delete from;
        delete to;
        delete result;
        delete vector;
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
    raytracer::Transform * halfQuarterRot;
    raytracer::Transform * fullQuarterRot;

    raytracer::Tuple * point;
    raytracer::Tuple * p1;
    raytracer::Tuple * p2;
    raytracer::Tuple * p3;
    raytracer::Tuple * p4;
    raytracer::Tuple * from;
    raytracer::Tuple * to;
    raytracer::Tuple * result;

    raytracer::Tuple * vector;
    raytracer::Tuple * up;

    raytracer::Matrix * identity;
    raytracer::Matrix * matrix;
};

TEST_F(TransformFixture, PointTranslationTest) {
    trans->translate(5, -3, 2);
    * point = raytracer::createPoint(-3, 4, 5);
    * result = raytracer::createPoint(2, 1, 7);
    ASSERT_EQ(* result, * trans * * point);
}

TEST_F(TransformFixture, InvTranslationTest) {
    trans->translate(5, -3, 2);
    * inv = inverse(* trans);
    * point = raytracer::createPoint(-3, 4, 5);
    * result = raytracer::createPoint(-8, 7, 3);
    ASSERT_EQ(* result, * inv * * point);
}

TEST_F(TransformFixture, VectorTranslationTest) {
    trans->translate(5, -3, 2);
    * vector = raytracer::createVector(-3, 4, 5);
    * result = raytracer::createVector(-3, 4, 5);
    ASSERT_EQ(* result, * trans * * vector);
}

TEST_F(TransformFixture, PointScaleTest) {
    trans->scale(2, 3, 4);
    * point = raytracer::createPoint(-4, 6, 8);
    * result = raytracer::createPoint(-8, 18, 32);
    ASSERT_EQ(* result, * trans * * point);
}

TEST_F(TransformFixture, VectorScaleTest) {
    trans->scale(2, 3, 4);
    * vector = raytracer::createVector(-4, 6, 8);
    * result = raytracer::createVector(-8, 18, 32);
    ASSERT_EQ(* result, * trans * * vector);
}

TEST_F(TransformFixture, InvScalingTest) {
    trans->scale(2, 3, 4);
    * inv = inverse(* trans);
    * vector = raytracer::createVector(-4, 6, 8);
    * result = raytracer::createVector(-2, 2, 2);
    ASSERT_EQ(* result, * inv * * vector);
}

TEST_F(TransformFixture, ReflectionTest) {
    trans->scale(-1, 1, 1);
    * point = raytracer::createPoint(2, 3, 4);
    * result = raytracer::createPoint(-2, 3, 4);
    ASSERT_EQ(* result, * trans * * point);
}

TEST_F(TransformFixture, RotationXTest) {
    * halfQuarterRot = trans->rotateX(PI / 4);
    * fullQuarterRot = trans->rotateX(PI / 2);
    * point = raytracer::createPoint(0, 1, 0);
    EXPECT_EQ(raytracer::createPoint(0, sqrt(2)/2, sqrt(2)/2), * halfQuarterRot * * point);
    ASSERT_EQ(raytracer::createPoint(0, 0, 1), * fullQuarterRot * * point);
}

TEST_F(TransformFixture, InverseRotationXTest) {
    * halfQuarterRot = trans->rotateX(PI / 4);
    * point = raytracer::createPoint(0, 1, 0);
    ASSERT_EQ(raytracer::createPoint(0, sqrt(2)/2, -sqrt(2)/2), inverse(* halfQuarterRot) * * point);
}

TEST_F(TransformFixture, RotationYTest) {
    * halfQuarterRot = trans->rotateY(PI / 4);
    * fullQuarterRot = trans->rotateY(PI / 2);
    * point = raytracer::createPoint(0, 0, 1);
    ASSERT_EQ(raytracer::createPoint(sqrt(2)/2, 0, sqrt(2)/2), * halfQuarterRot * * point);
    ASSERT_EQ(raytracer::createPoint(1, 0, 0), * fullQuarterRot * * point);
}

TEST_F(TransformFixture, RotationZTest) {
    * halfQuarterRot = trans->rotateZ(PI / 4);
    * fullQuarterRot = trans->rotateZ(PI / 2);
    * point = raytracer::createPoint(0, 1, 0);
    ASSERT_EQ(raytracer::createPoint(-sqrt(2)/2, sqrt(2)/2, 0), * halfQuarterRot * * point);
    ASSERT_EQ(raytracer::createPoint(-1, 0, 0), * fullQuarterRot * * point);
}

TEST_F(TransformFixture, Shearing1) {
    trans->shear(1, 0, 0, 0, 0, 0);
    * point = raytracer::createPoint(2, 3, 4);
    ASSERT_EQ(raytracer::createPoint(5, 3, 4), * trans * * point);
}

TEST_F(TransformFixture, Shearing2) {
    trans->shear(0, 1, 0, 0, 0, 0);
    * point = raytracer::createPoint(2, 3, 4);
    ASSERT_EQ(raytracer::createPoint(6, 3, 4), * trans * * point);
}

TEST_F(TransformFixture, Shearing3) {
    trans->shear(0, 0, 1, 0, 0, 0);
    * point = raytracer::createPoint(2, 3, 4);
    ASSERT_EQ(raytracer::createPoint(2, 5, 4), * trans * * point);
}

TEST_F(TransformFixture, Shearing4) {
    trans->shear(0, 0, 0, 1, 0, 0);
    * point = raytracer::createPoint(2, 3, 4);
    ASSERT_EQ(raytracer::createPoint(2, 7, 4), * trans * * point);
}

TEST_F(TransformFixture, Shearing5) {
    trans->shear(0, 0, 0, 0, 1, 0);
    * point = raytracer::createPoint(2, 3, 4);
    ASSERT_EQ(raytracer::createPoint(2, 3, 6), * trans * * point);
}

TEST_F(TransformFixture, Shearing6) {
    trans->shear(0, 0, 0, 0, 0, 1);
    * point = raytracer::createPoint(2, 3, 4);
    ASSERT_EQ(raytracer::createPoint(2, 3, 7), * trans * * point);
}

TEST_F(TransformFixture, ChainingTransforms) {
    * point = raytracer::createPoint(1, 0, 1);
    transA->rotateX(PI / 2);
    transB->scale(5, 5, 5);
    transC->translate(10, 5, 7);
    * p2 = * transA * * point;
    ASSERT_EQ(raytracer::createPoint(1, -1, 0), * p2);
    * p3 = * transB * * p2;
    ASSERT_EQ(raytracer::createPoint(5, -5, 0), * p3);
    * p4 = * transC * * p3;
    ASSERT_EQ(raytracer::createPoint(15, 0, 7), * p4);
}

TEST_F(TransformFixture, ReverseChainedTransforms) {
    * point = raytracer::createPoint(1, 0, 1);
    transA->rotateX(PI / 2);
    transB->scale(5, 5, 5);
    transC->translate(10, 5, 7);
    * transT = * transC * * transB * * transA;
    ASSERT_EQ(raytracer::createPoint(15, 0, 7), * transT * * point);
}

TEST_F(TransformFixture, DefaultOrientation) {
    * from = raytracer::createPoint(0, 0, 0);
    * to = raytracer::createPoint(0, 0, -1);
    * up = raytracer::createVector(0, 1, 0);
    * trans = viewTransform(* from, * to, * up);
    * identity = raytracer::generateIdentity(4, 4);
    ASSERT_EQ(* identity, * trans);
}

TEST_F(TransformFixture, ViewTransformPositiveZDirection) {
    * from = raytracer::createPoint(0, 0, 0);
    * to = raytracer::createPoint(0, 0, 1);
    * up = raytracer::createVector(0, 1, 0);
    * trans = viewTransform(* from, * to, * up);
    ASSERT_EQ(* trans, trans->scale(-1, 1, -1));
}

TEST_F(TransformFixture, ViewTransformationMovesWorld) {
    * from = raytracer::createPoint(0, 0, 8);
    * to = raytracer::createPoint(0, 0, 1);
    * up = raytracer::createVector(0, 1, 0);
    * trans = viewTransform(* from, * to, * up);
    ASSERT_EQ(* trans, trans->translate(0, 0, -8));
}

TEST_F(TransformFixture, ArbitraryViewTransformation) {
    * from = raytracer::createPoint(1, 3, 2);
    * to = raytracer::createPoint(4, -2, 8);
    * up = raytracer::createVector(1, 1, 0);
    * trans = viewTransform(* from, * to, * up);
    std::vector<double> data{-0.50709, 0.50709, 0.67612, -2.36643, 0.76772, 0.60609, 0.12122, -2.82843, -0.35857, 0.59761, -0.71714, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000};
    matrix->setMatrixData(data);
    transA = new raytracer::Transform(* matrix);
    ASSERT_EQ(* trans, * transA);
}

