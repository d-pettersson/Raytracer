#include "include/ray.h"
#include "include/sphere.h"
#include "include/intersection.h"
#include "include/transform.h"

#include "gtest/gtest.h"

class RayFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        ray = new raytracer::Ray();
        r2 = new raytracer::Ray();
        origin = new raytracer::Tuple();
        direction = new raytracer::Tuple();
        xs = new std::vector<raytracer::Intersection>(2);
        transformation = new raytracer::Transform();
        translate = new raytracer::Transform();
        scale = new raytracer::Transform();
    }

    virtual void TearDown() {
        delete ray;
        delete r2;
        delete origin;
        delete direction;
        delete xs;
        delete transformation;
        delete translate;
        delete scale;
    }

    raytracer::Ray * ray;
    raytracer::Ray * r2;
    std::shared_ptr<raytracer::Shape> sphere = std::make_shared<raytracer::Sphere>();
    std::shared_ptr<raytracer::Shape> s1 = std::make_shared<raytracer::Sphere>();
    std::shared_ptr<raytracer::Shape> s2 = std::make_shared<raytracer::Sphere>();
    raytracer::Tuple * origin;
    raytracer::Tuple * direction;
    std::vector<raytracer::Intersection> * xs;
    raytracer::Transform * transformation;
    raytracer::Transform * translate;
    raytracer::Transform * scale;
};

TEST_F(RayFixture, RayCreationAndQuery) {
    * origin = raytracer::createPoint(1, 2, 3);
    * direction = raytracer::createVector(4, 5, 6);
    * ray = raytracer::Ray(* origin, * direction);
    EXPECT_EQ(ray->getOrigin(), * origin);
    ASSERT_EQ(ray->getDirection(), * direction);
}

TEST_F(RayFixture, PointComputing) {
    * origin = raytracer::createPoint(2, 3, 4);
    * direction = raytracer::createVector(1, 0, 0);
    * ray = raytracer::Ray(* origin, * direction);
    EXPECT_EQ(raytracer::createPoint(2, 3, 4), ray->position(0.0));
    EXPECT_EQ(raytracer::createPoint(3, 3, 4), ray->position(1));
    EXPECT_EQ(raytracer::createPoint(1, 3, 4), ray->position(-1));
    ASSERT_EQ(raytracer::createPoint(4.5, 3, 4), ray->position(2.5));
}

TEST_F(RayFixture, UniqueID) {
    ASSERT_NE(s1->id, s2->id);
}

TEST_F(RayFixture, Intersection1) {
    * origin = raytracer::createPoint(0, 0, -5);
    * direction = raytracer::createVector(0, 0, 1);
    * ray = raytracer::Ray(* origin, * direction);
    sphere->intersect(* ray, * xs);
    EXPECT_EQ(2, xs->size());
//    EXPECT_EQ(4.0, sphere->getIntersects(0));
//    ASSERT_EQ(6.0, sphere->getIntersects(1));
}

TEST_F(RayFixture, Intersection2) {
    * origin = raytracer::createPoint(0, 1, -5);
    * direction = raytracer::createVector(0, 0, 1);
    * ray = raytracer::Ray(* origin, * direction);
    sphere->intersect(* ray, * xs);
    EXPECT_EQ(2, xs->size());
    EXPECT_EQ(5.0, xs[0][0].getDistance());
    ASSERT_EQ(5.0, xs[0][1].getDistance());
}

TEST_F(RayFixture, Intersection3) {
    * origin = raytracer::createPoint(0, 2, -5);
    * direction = raytracer::createVector(0, 0, 1);
    * ray = raytracer::Ray(* origin, * direction);
    sphere->intersect(* ray, * xs);
    ASSERT_EQ(0, xs->size());
}

TEST_F(RayFixture, Intersection4) {
    * origin = raytracer::createPoint(0, 0, 0);
    * direction = raytracer::createVector(0, 0, 1);
    * ray = raytracer::Ray(* origin, * direction);
    sphere->intersect(* ray, * xs);
    EXPECT_EQ(2, xs->size());
    EXPECT_EQ(-1.0, xs[0][0].getDistance());
    ASSERT_EQ(1.0, xs[1][0].getDistance());
}

TEST_F(RayFixture, Intersection5) {
    * origin = raytracer::createPoint(0, 0, 5);
    * direction = raytracer::createVector(0, 0, 1);
    * ray = raytracer::Ray(* origin, * direction);
    sphere->intersect(* ray, * xs);
    EXPECT_EQ(2, xs->size());
    EXPECT_EQ(-6.0, xs[0][0].getDistance());
    ASSERT_EQ(-4.0, xs[1][0].getDistance());
}

TEST_F(RayFixture, IntersectObject) {
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -5), raytracer::createVector(0, 0, 1));
    sphere->intersect(* ray, * xs);
    EXPECT_EQ(2, xs->size());
    EXPECT_EQ(sphere, xs[0][0].getObject());
    ASSERT_EQ(sphere, xs[1][0].getObject());
}

TEST_F(RayFixture, RayTranslation) {
    * ray = raytracer::Ray(raytracer::createPoint(1, 2, 3), raytracer::createVector(0, 1, 0));
    translate->translate(3, 4, 5);
    * r2 = transform(* ray, * translate);
    EXPECT_EQ(r2->getOrigin(), raytracer::createPoint(4, 6, 8));
    ASSERT_EQ(r2->getDirection(), raytracer::createVector(0, 1, 0));
}

TEST_F(RayFixture, RayScaling) {
    * ray = raytracer::Ray(raytracer::createPoint(1, 2, 3), raytracer::createVector(0, 1, 0));
    scale->scale(2, 3, 4);
    * r2 = transform(* ray, * scale);
    ASSERT_EQ(r2->getOrigin(), raytracer::createPoint(2, 6, 12));
    ASSERT_EQ(r2->getDirection(), raytracer::createVector(0, 3, 0));
}