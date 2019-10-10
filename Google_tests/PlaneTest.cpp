#include "ray.h"
#include "plane.h"
#include "tuple.h"
#include "transform.h"

#include "gtest/gtest.h"

#include <cmath>

class PlaneFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        ray = new raytracer::Ray();
        transformation = new raytracer::Transform();
        translate = new raytracer::Transform();
        rotate = new raytracer::Transform();
        scale = new raytracer::Transform();
        normal = new raytracer::Vector();
        n1 = new raytracer::Vector();
        n2 = new raytracer::Vector();
        n3 = new raytracer::Vector();
        material = new raytracer::Material();
    }

    virtual void TearDown() {
        delete ray;
        delete transformation;
        delete translate;
        delete rotate;
        delete scale;
        delete normal;
        delete n1;
        delete n2;
        delete n3;
        delete material;
    }

    raytracer::Ray * ray;
    std::shared_ptr<raytracer::Shape> plane = std::make_shared<raytracer::Plane>();
    std::vector<raytracer::Intersection> xs;
    raytracer::Transform * transformation;
    raytracer::Transform * translate;
    raytracer::Transform * rotate;
    raytracer::Transform * scale;
    raytracer::Vector * normal;
    raytracer::Vector * n1;
    raytracer::Vector * n2;
    raytracer::Vector * n3;
    raytracer::Material * material;
};

TEST_F(PlaneFixture, NormalPlaneIsConstantEverywhere) {
    * n1 = plane->getNormal(raytracer::Point(0, 0, 0));
    * n2 = plane->getNormal(raytracer::Point(10, 0, -10));
    * n3 = plane->getNormal(raytracer::Point(-5, 0, 150));
    EXPECT_EQ(* n1, raytracer::Vector(0, 1, 0));
    EXPECT_EQ(* n2, raytracer::Vector(0, 1, 0));
    ASSERT_EQ(* n3, raytracer::Vector(0, 1, 0));
}

TEST_F(PlaneFixture, IntersectRayParallelToPlane) {
    * ray = raytracer::Ray(raytracer::Point(0, 10, 0), raytracer::Vector(0, 0, 1));
    plane->intersect(* ray, xs);
    ASSERT_EQ(xs.size(), 0);
}

TEST_F(PlaneFixture, IntersectRayCoplanar) {
    * ray = raytracer::Ray(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 1));
    plane->intersect(* ray, xs);
    ASSERT_EQ(xs.size(), 0);
}

TEST_F(PlaneFixture, RayIntersectingPlaneFromAbove) {
    * ray = raytracer::Ray(raytracer::Point(0, 1, 0), raytracer::Vector(0, -1, 0));
    plane->intersect(* ray, xs);
    EXPECT_EQ(xs.size(),1);
    EXPECT_EQ(xs[0].getDistance(), 1);
    ASSERT_EQ(xs[0].getObject(), plane);
}

TEST_F(PlaneFixture, RayIntersectingPlaneFromBelow) {
    * ray = raytracer::Ray(raytracer::Point(0, -1, 0), raytracer::Vector(0, 1, 0));
    plane->intersect(* ray, xs);
    EXPECT_EQ(xs.size(),1);
    EXPECT_EQ(xs[0].getDistance(), 1);
    ASSERT_EQ(xs[0].getObject(), plane);
}