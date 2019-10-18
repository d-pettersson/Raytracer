#include "include/ray.h"
#include "include/sphere.h"
#include "include/plane.h"
#include "include/intersection.h"

#include <memory>
#include <cmath>

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
    std::shared_ptr<raytracer::Shape> plane = std::make_shared<raytracer::Plane>();
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

// TODO: fix previously running tests (added parameter to prepareComputations signature)

//TEST_F(IntersectionFixture, PrecomputingIntersectionState) {
//    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
//    * intersection = raytracer::Intersection(4, sphere);
//    * intersectionData = intersection->prepareComputations(* ray);
//    ASSERT_EQ(intersectionData->distance, intersection->getDistance());
//    ASSERT_EQ(intersectionData->object, intersection->getObject());
//    ASSERT_EQ(intersectionData->point, raytracer::Point(0, 0, -1));
//    ASSERT_EQ(intersectionData->eye, raytracer::Vector(0, 0, -1));
//    ASSERT_EQ(intersectionData->normal, raytracer::Vector(0, 0, -1));
//}
//
//TEST_F(IntersectionFixture, TestOutside) {
//    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
//    * intersection = raytracer::Intersection(4, sphere);
//    * intersectionData = intersection->prepareComputations(* ray);
//    ASSERT_FALSE(intersectionData->inside);
//}
//
//TEST_F(IntersectionFixture, TestInside) {
//    * ray = raytracer::Ray(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 1));
//    * intersection = raytracer::Intersection(1, sphere);
//    * intersectionData = intersection->prepareComputations(* ray);
//    ASSERT_EQ(intersectionData->point, raytracer::Point(0, 0, 1));
//    ASSERT_EQ(intersectionData->eye, raytracer::Vector(0, 0, -1));
//    ASSERT_TRUE(intersectionData->inside);
//    ASSERT_EQ(intersectionData->normal, raytracer::Vector(0, 0, -1));
//}
//
//TEST_F(IntersectionFixture, PointOffset) {
//    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
//    sphere->setTransform(transform->translate(0, 0, 1));
//    * intersection = raytracer::Intersection(5, sphere);
//    raytracer::IntersectionData intersectionData = intersection->prepareComputations(* ray);
//    ASSERT_TRUE(intersectionData.overPoint.z < -EPSILON / 2);
//    ASSERT_TRUE(intersectionData.point.z > intersectionData.overPoint.z);
//}
//
//TEST_F(IntersectionFixture, ComputeReflectVector) {
//    * ray = raytracer::Ray(raytracer::Point(0, 1, -1), raytracer::Vector(0, -sqrt(2)/2, sqrt(2)/2));
//    * intersection = raytracer::Intersection(sqrt(2), plane);
//    raytracer::IntersectionData intersectionData = intersection->prepareComputations(* ray);
//    ASSERT_EQ(intersectionData.reflect, raytracer::Vector(0, sqrt(2)/2, sqrt(2)/2));
//}

TEST_F(IntersectionFixture, FindingN1N2VariousIntersections) {
    auto sphereA = std::make_shared<raytracer::Sphere>();
    sphereA->createGlass();
    sphereA->material.refractiveIndex = 1.5;
    transform->scale(2, 2, 2);
    sphereA->setTransform(* transform);
    auto A1 = raytracer::Intersection(2, sphereA);
    auto A2 = raytracer::Intersection(6, sphereA);

    auto sphereB = std::make_shared<raytracer::Sphere>();
    sphereB->createGlass();
    sphereB->material.refractiveIndex = 2.0;
    transform->translate(0, 0, -0.25);
    sphereB->setTransform(* transform);
    auto B1 = raytracer::Intersection(2.75, sphereB);
    auto B2 = raytracer::Intersection(4.75, sphereB);

    auto sphereC = std::make_shared<raytracer::Sphere>();
    sphereC->createGlass();
    sphereC->material.refractiveIndex = 2.5;
    transform->translate(0, 0, 0.25);
    sphereC->setTransform(* transform);
    auto C1 = raytracer::Intersection(3.25, sphereC);
    auto C2 = raytracer::Intersection(5.25, sphereC);


    auto ray = raytracer::Ray(raytracer::Point(0, 0, -4), raytracer::Vector(0, 0, 1));
    auto xs = intersections(A1, B1, C1, B2, C2, A2);

    auto comps = A1.prepareComputations(ray, xs);
    EXPECT_EQ(comps.n1, 1.0);
    EXPECT_EQ(comps.n2, 1.5);

    comps = B1.prepareComputations(ray, xs);
    EXPECT_EQ(comps.n1, 1.5);
    EXPECT_EQ(comps.n2, 2.0);

    comps = C1.prepareComputations(ray, xs);
    EXPECT_EQ(comps.n1, 2.0);
    EXPECT_EQ(comps.n2, 2.5);

    comps = B2.prepareComputations(ray, xs);
    EXPECT_EQ(comps.n1, 2.5);
    EXPECT_EQ(comps.n2, 2.5);

    comps = C2.prepareComputations(ray, xs);
    EXPECT_EQ(comps.n1, 2.5);
    EXPECT_EQ(comps.n2, 1.5);

    comps = A2.prepareComputations(ray, xs);
    EXPECT_EQ(comps.n1, 1.5);
    ASSERT_EQ(comps.n2, 1.0);
}

TEST_F(IntersectionFixture, UnderPointOffset) {
    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    auto sphere = std::make_shared<raytracer::Sphere>();
    sphere->createGlass();
    transform->translate(0, 0, 1);
    sphere->setTransform(* transform);
    * intersection = raytracer::Intersection(5, sphere);
    auto xs = intersections(* intersection);
    * intersectionData = intersection->prepareComputations(* ray, xs);
    EXPECT_TRUE(intersectionData->underPoint.z > EPSILON / 2);
    ASSERT_TRUE(intersectionData->point.z < intersectionData->underPoint.z);
}


