#include "ray.h"
#include "shape.h"
#include "intersection.h"

#include "gtest/gtest.h"

class IntersectionFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        ray = new raytracer::Ray();
        sphere = new raytracer::Sphere();
        intersection = new raytracer::Intersection();
        intersection2 = new raytracer::Intersection();
        inters = new raytracer::Intersections();
    }

    virtual void TearDown() {
        delete ray;
        delete sphere;
        delete intersection;
        delete intersection2;
        delete inters;
    }

    raytracer::Ray * ray;
    raytracer::Sphere * sphere;
    raytracer::Point origin;
    raytracer::Vector direction;
    raytracer::Intersection * intersection;
    raytracer::Intersection * intersection2;
    raytracer::Intersections * inters;
};

TEST_F(IntersectionFixture, EncapsulationTest) {
    * sphere = raytracer::Sphere();
    * intersection = raytracer::Intersection(3.5, sphere);
    ASSERT_EQ(3.5, intersection->t);
    ASSERT_EQ(* sphere, intersection->shape);
}

TEST_F(IntersectionFixture, AggregationTest) {
    * sphere = raytracer::Sphere();
    * intersection = raytracer::Intersection(1, sphere);
    * intersection2 = raytracer::Intersection(2, sphere);
    * inters = raytracer::Intersections();
    inters->intersections(* intersection, * intersection2);
//    ASSERT_EQ(3.5, intersection->t);
//    ASSERT_EQ(* sphere, intersection->shape);
}