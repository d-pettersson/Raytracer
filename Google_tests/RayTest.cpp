#include "ray.h"
#include "shape.h"

#include "gtest/gtest.h"

class RayFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        ray = new raytracer::Ray();
        sphere = new raytracer::Sphere();
    }

    virtual void TearDown() {
        delete ray;
        delete sphere;
    }

    raytracer::Ray * ray;
    raytracer::Sphere * sphere;
    raytracer::Point origin;
    raytracer::Vector direction;
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
    * sphere = raytracer::Sphere();
    sphere->intersect(* ray);
    ASSERT_EQ(2, sphere->count());
//    ASSERT_EQ(4.0, sphere->getIntersects(0));
//    ASSERT_EQ(6.0, sphere->getIntersects(1));
}

TEST_F(RayFixture, Intersection2) {
    origin = raytracer::Point(0, 1, -5);
    direction = raytracer::Vector(0, 0, 1);
    * ray = raytracer::Ray(origin, direction);
    * sphere = raytracer::Sphere();
    sphere->intersect(* ray);
    ASSERT_EQ(2, sphere->count());
    ASSERT_EQ(5.0, sphere->getIntersects(0));
    ASSERT_EQ(5.0, sphere->getIntersects(1));
}

TEST_F(RayFixture, Intersection3) {
    origin = raytracer::Point(0, 2, -5);
    direction = raytracer::Vector(0, 0, 1);
    * ray = raytracer::Ray(origin, direction);
    * sphere = raytracer::Sphere();
    sphere->intersect(* ray);
    ASSERT_EQ(0, sphere->count());
}

TEST_F(RayFixture, Intersection4) {
    origin = raytracer::Point(0, 0, 0);
    direction = raytracer::Vector(0, 0, 1);
    * ray = raytracer::Ray(origin, direction);
    * sphere = raytracer::Sphere();
    sphere->intersect(* ray);
    ASSERT_EQ(2, sphere->count());
    ASSERT_EQ(-1.0, sphere->getIntersects(0));
    ASSERT_EQ(1.0, sphere->getIntersects(1));
}

TEST_F(RayFixture, Intersection5) {
    origin = raytracer::Point(0, 0, 5);
    direction = raytracer::Vector(0, 0, 1);
    * ray = raytracer::Ray(origin, direction);
    * sphere = raytracer::Sphere();
    sphere->intersect(* ray);
    ASSERT_EQ(2, sphere->count());
    ASSERT_EQ(-6.0, sphere->getIntersects(0));
    ASSERT_EQ(-4.0, sphere->getIntersects(1));

}