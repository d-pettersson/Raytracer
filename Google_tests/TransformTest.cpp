#include "transform.h"
#include "common.h"
#include "tuple.h"

#include "gtest/gtest.h"


class TransformFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        trans = new raytracer::Transform();
    }

    virtual void TearDown() {
        delete trans;
    }

    raytracer::Transform * trans;
    raytracer::Transform trans1;
    raytracer::Transform inv;

    raytracer::Point point;
    raytracer::Point * pointResult;
};

TEST_F(TransformFixture, TranslationTest) {
    trans = new raytracer::Transform();
    trans->translation(5, -3, 2);
    point = raytracer::Point(-3, 4, 5);
    pointResult = new raytracer::Point(2, 1, 7);
    ASSERT_EQ(* pointResult, * trans * point);
}

TEST_F(TransformFixture, TranslationTest2) {
    trans = new raytracer::Transform();
    trans->translation(5, -3, 2);
    inv = inverse(trans);
    point = raytracer::Point(-3, 4, 5);
    pointResult = new raytracer::Point(2, 1, 7);
    ASSERT_EQ(* pointResult, * trans * point);
}

