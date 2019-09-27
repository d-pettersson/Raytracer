#include "ray.h"
#include "sphere.h"
#include "intersection.h"

#include <memory>

#include "gtest/gtest.h"

class IntersectionFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        ray = new raytracer::Ray();
        intersection = new raytracer::Intersection();
        intersection2 = new raytracer::Intersection();
    }

    virtual void TearDown() {
        delete ray;
        delete intersection;
        delete intersection2;
    }

    raytracer::Ray * ray;
    std::shared_ptr<raytracer::Shape> sphere = std::make_shared<raytracer::Sphere>();
    raytracer::Point origin;
    raytracer::Vector direction;
    raytracer::Intersection * intersection;
    raytracer::Intersection * intersection2;
};

TEST_F(IntersectionFixture, EncapsulationTest) {
    * intersection = raytracer::Intersection(3.5, sphere);
    ASSERT_EQ(3.5, intersection->getDistance());
    ASSERT_EQ(sphere, intersection->getObject());
}

TEST_F(IntersectionFixture, AggregationTest) {
    * intersection = raytracer::Intersection(1, sphere);
    * intersection2 = raytracer::Intersection(2, sphere);
    std::vector<raytracer::Intersection> xs = intersections(* intersection, * intersection2);
    ASSERT_EQ(2, xs.size());
    ASSERT_EQ(xs[0].getDistance(), 1);
    ASSERT_EQ(xs[1].getDistance(), 2);
}

