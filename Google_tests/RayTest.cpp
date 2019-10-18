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
        ray2 = new raytracer::Ray();
        transformation = new raytracer::Transform();
        translate = new raytracer::Transform();
        scale = new raytracer::Transform();
    }

    virtual void TearDown() {
        delete ray;
        delete ray2;
        delete transformation;
        delete translate;
        delete scale;
    }

    raytracer::Ray * ray;
    raytracer::Ray * ray2;
    std::shared_ptr<raytracer::Shape> sphere = std::make_shared<raytracer::Sphere>();
    raytracer::Point origin;
    raytracer::Vector direction;
    std::vector<raytracer::Intersection> xs;
    raytracer::Transform * transformation;
    raytracer::Transform * translate;
    raytracer::Transform * scale;
};

TEST_F(RayFixture, RayCreationAndQuery) {
    origin = raytracer::Point(1, 2, 3);
    direction = raytracer::Vector(4, 5, 6);
    * ray = raytracer::Ray(origin, direction);
    ASSERT_EQ(ray->getOrigin(), origin);
    ASSERT_EQ(ray->getDirection(), direction);
}

TEST_F(RayFixture, PointComputing) {
    origin = raytracer::Point(2, 3, 4);
    direction = raytracer::Vector(1, 0, 0);
    * ray = raytracer::Ray(origin, direction);
    ASSERT_EQ(raytracer::Point(2, 3, 4), ray->position(0.0));
    ASSERT_EQ(raytracer::Point(3, 3, 4), ray->position(1));
    ASSERT_EQ(raytracer::Point(1, 3, 4), ray->position(-1));
    ASSERT_EQ(raytracer::Point(4.5, 3, 4), ray->position(2.5));
}

TEST_F(RayFixture, UniqueID) {
    raytracer::Sphere s1 = raytracer::Sphere();
    raytracer::Sphere s2 = raytracer::Sphere();
    ASSERT_NE(s1.id, s2.id);
}

TEST_F(RayFixture, Intersection1) {
    origin = raytracer::Point(0, 0, -5);
    direction = raytracer::Vector(0, 0, 1);
    * ray = raytracer::Ray(origin, direction);
//    * sphere = raytracer::Sphere();
    sphere->intersect(* ray, xs);
    ASSERT_EQ(2, xs.size());
//    ASSERT_EQ(4.0, sphere->getIntersects(0));
//    ASSERT_EQ(6.0, sphere->getIntersects(1));
}

TEST_F(RayFixture, Intersection2) {
    origin = raytracer::Point(0, 1, -5);
    direction = raytracer::Vector(0, 0, 1);
    * ray = raytracer::Ray(origin, direction);
    * sphere = raytracer::Sphere();
    sphere->intersect(* ray, xs);
    ASSERT_EQ(2, xs.size());
    ASSERT_EQ(5.0, xs[0].getDistance());
    ASSERT_EQ(5.0, xs[1].getDistance());
}

TEST_F(RayFixture, Intersection3) {
    origin = raytracer::Point(0, 2, -5);
    direction = raytracer::Vector(0, 0, 1);
    * ray = raytracer::Ray(origin, direction);
//    * sphere = raytracer::Sphere();
    sphere->intersect(* ray, xs);
    ASSERT_EQ(0, xs.size());
}

TEST_F(RayFixture, Intersection4) {
    origin = raytracer::Point(0, 0, 0);
    direction = raytracer::Vector(0, 0, 1);
    * ray = raytracer::Ray(origin, direction);
//    * sphere = raytracer::Sphere();
    sphere->intersect(* ray, xs);
    ASSERT_EQ(2, xs.size());
    ASSERT_EQ(-1.0, xs[0].getDistance());
    ASSERT_EQ(1.0, xs[1].getDistance());
}

TEST_F(RayFixture, Intersection5) {
    origin = raytracer::Point(0, 0, 5);
    direction = raytracer::Vector(0, 0, 1);
    * ray = raytracer::Ray(origin, direction);
//    * sphere = raytracer::Sphere();
    sphere->intersect(* ray, xs);
    ASSERT_EQ(2, xs.size());
    ASSERT_EQ(-6.0, xs[0].getDistance());
    ASSERT_EQ(-4.0, xs[1].getDistance());
}

TEST_F(RayFixture, IntersectObject) {
    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    sphere->intersect(* ray, xs);
    ASSERT_EQ(2, xs.size());
    ASSERT_EQ(sphere, xs[0].getObject());
    ASSERT_EQ(sphere, xs[1].getObject());
}

TEST_F(RayFixture, RayTranslation) {
    * ray = raytracer::Ray(raytracer::Point(1, 2, 3), raytracer::Vector(0, 1, 0));
    translate->translate(3, 4, 5);
    * ray2 = transform(* ray, * translate);
    ASSERT_EQ(ray2->getOrigin(), raytracer::Point(4, 6, 8));
    ASSERT_EQ(ray2->getDirection(), raytracer::Vector(0, 1, 0));
}

TEST_F(RayFixture, RayScaling) {
    * ray = raytracer::Ray(raytracer::Point(1, 2, 3), raytracer::Vector(0, 1, 0));
    scale->scale(2, 3, 4);
    * ray2 = transform(* ray, * scale);
    ASSERT_EQ(ray2->getOrigin(), raytracer::Point(2, 6, 12));
    ASSERT_EQ(ray2->getDirection(), raytracer::Vector(0, 3, 0));
}