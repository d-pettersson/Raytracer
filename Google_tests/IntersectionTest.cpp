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
        intersection3 = new raytracer::Intersection();
        intersection4 = new raytracer::Intersection();
        hitIntersection = new raytracer::Intersection();
        xs = new std::vector<raytracer::Intersection>;
        intersectionData = new raytracer::IntersectionData();
        transform = new raytracer::Transform();
    }

    virtual void TearDown() {
        delete ray;
        delete intersection;
        delete intersection2;
        delete intersection3;
        delete intersection4;
        delete hitIntersection;
        delete xs;
        delete intersectionData;
        delete transform;
    }

    raytracer::Ray * ray;
    std::shared_ptr<raytracer::Shape> sphere = std::make_shared<raytracer::Sphere>();
    raytracer::Point origin;
    raytracer::Vector direction;
    raytracer::Intersection * intersection;
    raytracer::Intersection * intersection2;
    raytracer::Intersection * intersection3;
    raytracer::Intersection * intersection4;
    raytracer::Intersection * hitIntersection;
    std::vector<raytracer::Intersection> * xs;
    raytracer::IntersectionData * intersectionData;
    raytracer::Transform * transform;
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

TEST_F(IntersectionFixture, Hit1) {
    * intersection = raytracer::Intersection(1, sphere);
    * intersection2 = raytracer::Intersection(2, sphere);
    std::vector<raytracer::Intersection> xs = intersections(* intersection2, * intersection);
    * hitIntersection = hit(xs);
    ASSERT_EQ(hitIntersection->getDistance(), intersection->getDistance());
    ASSERT_EQ(hitIntersection->getObject(), intersection->getObject());
}

TEST_F(IntersectionFixture, Hit2) {
    * intersection = raytracer::Intersection(-1, sphere);
    * intersection2 = raytracer::Intersection(1, sphere);
    std::vector<raytracer::Intersection> xs = intersections(* intersection2, * intersection);
    * hitIntersection = hit(xs);
    ASSERT_EQ(hitIntersection->getDistance(), intersection2->getDistance());
    ASSERT_EQ(hitIntersection->getObject(), intersection2->getObject());
}

TEST_F(IntersectionFixture, Hit3) {
    * intersection = raytracer::Intersection(-2, sphere);
    * intersection2 = raytracer::Intersection(-1, sphere);
    std::vector<raytracer::Intersection> xs = intersections(* intersection2, * intersection);
    * hitIntersection = hit(xs);
    ASSERT_EQ(hitIntersection->getDistance(), 0);
    ASSERT_EQ(hitIntersection->getObject(), nullptr);
}

TEST_F(IntersectionFixture, Hit4) {
    * intersection = raytracer::Intersection(5, sphere);
    * intersection2 = raytracer::Intersection(7, sphere);
    * intersection3 = raytracer::Intersection(-3, sphere);
    * intersection4 = raytracer::Intersection(2, sphere);
    std::vector<raytracer::Intersection> xs = intersections(* intersection, * intersection2, * intersection3, * intersection4);
    * hitIntersection = hit(xs);
    ASSERT_EQ(hitIntersection->getDistance(), intersection4->getDistance());
    ASSERT_EQ(hitIntersection->getObject(), intersection4->getObject());
}

TEST_F(IntersectionFixture, PrecomputingIntersectionState) {
    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    * intersection = raytracer::Intersection(4, sphere);
    * intersectionData = intersection->prepareComputations(* ray);
    ASSERT_EQ(intersectionData->distance, intersection->getDistance());
    ASSERT_EQ(intersectionData->object, intersection->getObject());
    ASSERT_EQ(intersectionData->point, raytracer::Point(0, 0, -1));
    ASSERT_EQ(intersectionData->eye, raytracer::Vector(0, 0, -1));
    ASSERT_EQ(intersectionData->normal, raytracer::Vector(0, 0, -1));
}

TEST_F(IntersectionFixture, TestOutside) {
    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    * intersection = raytracer::Intersection(4, sphere);
    * intersectionData = intersection->prepareComputations(* ray);
    ASSERT_FALSE(intersectionData->inside);
}

TEST_F(IntersectionFixture, TestInside) {
    * ray = raytracer::Ray(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 1));
    * intersection = raytracer::Intersection(1, sphere);
    * intersectionData = intersection->prepareComputations(* ray);
    ASSERT_EQ(intersectionData->point, raytracer::Point(0, 0, 1));
    ASSERT_EQ(intersectionData->eye, raytracer::Vector(0, 0, -1));
    ASSERT_TRUE(intersectionData->inside);
    ASSERT_EQ(intersectionData->normal, raytracer::Vector(0, 0, -1));
}

TEST_F(IntersectionFixture, PointOffset) {
    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    sphere->setTransform(transform->translate(0, 0, 1));
    * intersection = raytracer::Intersection(5, sphere);
    raytracer::IntersectionData intersectionData = intersection->prepareComputations(* ray);
    ASSERT_TRUE(intersectionData.overPoint.z < -EPSILON / 2);
    ASSERT_TRUE(intersectionData.point.z > intersectionData.overPoint.z);
}



