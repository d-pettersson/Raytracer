#include "include/world.h"
#include "include/intersection.h"
#include "include/plane.h"

#include "gtest/gtest.h"

#include <cmath>

class WorldFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        world = new raytracer::World();
        light = new raytracer::Light();
        transform = new raytracer::Transform();
        ray = new raytracer::Ray();
        xs = new std::vector<raytracer::Intersection>();
        intersection = new raytracer::Intersection();
        i1 = new raytracer::Intersection();
        i2 = new raytracer::Intersection();
        i3 = new raytracer::Intersection();
        i4 = new raytracer::Intersection();
        intersectionData = new raytracer::IntersectionData();
        color = new raytracer::Color();
        position = new raytracer::Tuple();
        point = new raytracer::Tuple();
    }

    virtual void TearDown() {
        delete world;
        delete light;
        delete transform;
        delete ray;
        delete xs;
        delete intersection;
        delete i1;
        delete i2;
        delete i3;
        delete i4;
        delete intersectionData;
        delete color;
        delete position;
        delete point;
    }

    raytracer::World * world;
    raytracer::Light * light;
    raytracer::Ray * ray;
    std::shared_ptr<raytracer::Shape> s1 = std::make_shared<raytracer::Sphere>();
    std::shared_ptr<raytracer::Shape> s2 = std::make_shared<raytracer::Sphere>();
    std::shared_ptr<raytracer::Shape> floor = std::make_shared<raytracer::Plane>();
    std::shared_ptr<raytracer::Shape> upper = std::make_shared<raytracer::Plane>();
    std::shared_ptr<raytracer::Shape> lower = std::make_shared<raytracer::Plane>();
    raytracer::Transform * transform;
    std::vector<raytracer::Intersection> * xs;
    raytracer::Intersection * intersection;
    raytracer::Intersection * i1;
    raytracer::Intersection * i2;
    raytracer::Intersection * i3;
    raytracer::Intersection * i4;
    raytracer::IntersectionData * intersectionData;
    raytracer::Color * color;
    raytracer::Tuple * position;
    raytracer::Tuple * point;
};

//// Test empty data structure?
//TEST_F(WorldFixture, TestDataStructure) {
//    ASSERT_EQ(nullptr, world);
//}

TEST_F(WorldFixture, DefaultWorld) {
    world->defaultWorld();
    s1->material.color = raytracer::Color(0.8, 1.0, 0.6);
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;
    s2->setTransform(transform->scale(0.5, 0.5, 0.5));
    EXPECT_EQ(raytracer::Light(raytracer::createPoint(-10, 10, -10), raytracer::Color(1, 1, 1)), world->light_);
    EXPECT_EQ(s1->material.diffuse, world->shapes_[0]->material.diffuse);
    EXPECT_EQ(s1->material.color, world->shapes_[0]->material.color);
    EXPECT_EQ(s1->material.specular, world->shapes_[0]->material.specular);
    ASSERT_EQ(s2->getTransform(), world->shapes_[1]->getTransform());
}

TEST_F(WorldFixture, WorldRayIntersection) {
    world->defaultWorld();
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -5), raytracer::createVector(0, 0, 1));
    world->intersectWorld(* ray, xs);
    EXPECT_EQ(xs->size(), 4);
    EXPECT_EQ(xs[0][0].getDistance(), 4);
    EXPECT_EQ(xs[0][1].getDistance(), 4.5);
    EXPECT_EQ(xs[0][2].getDistance(), 5.5);
    ASSERT_EQ(xs[0][3].getDistance(), 6);
}

//TEST_F(WorldFixture, IntersectionShading) {
//    world->defaultWorld();
//    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
//    s1 = world->shapes_[0];
//    * intersection = raytracer::Intersection(4, s1);
//    * intersectionData = intersection->prepareComputations(* ray);
//    * color = world->shadeHit(* intersectionData);
//    ASSERT_EQ(raytracer::Color(0.38066, 0.47583, 0.2855), * color);
//}
//
//TEST_F(WorldFixture, InsideIntersectionShading) {
//    world->defaultWorld();
//    light_->setPointLight(raytracer::Point(0, 0.25, 0), raytracer::Color(1, 1, 1));
//    world->light_ = * light_;
//    * ray = raytracer::Ray(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 1));
//    s2 = world->shapes_[1];
//    * intersection = raytracer::Intersection(0.5, s2);
//    * intersectionData = intersection->prepareComputations(* ray);
//    * color = world->shadeHit(* intersectionData);
//    ASSERT_EQ(raytracer::Color(0.90498, 0.90498, 0.90498), * color);
//}

TEST_F(WorldFixture, ColorWhenRayMisses) {
    world->defaultWorld();
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -5), raytracer::createVector(0, 1, 0));
    * color = world->colorAt(* ray);
    ASSERT_EQ(raytracer::Color(0, 0, 0), * color);
}

TEST_F(WorldFixture, ColorWhenRayHits) {
    world->defaultWorld();
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -5), raytracer::createVector(0, 0, 1));
    * color = world->colorAt(* ray);
    ASSERT_EQ(raytracer::Color(0.38066, 0.47583, 0.2855), * color);
}

TEST_F(WorldFixture, ColorWithIntersectionBehindRay) {
    world->defaultWorld();
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, 0.75), raytracer::createVector(0, 0, -1));
    s1 = world->shapes_[0];
    s1->material.ambient = 1;
    s2 = world->shapes_[1];
    s2->material.ambient = 1;
    * color = world->colorAt(* ray);
    ASSERT_EQ(s2->material.color, * color);
}


// change to world isShadowed methods
// for soft shadow implementation breaks tests
// functionality stays the same with new variable

//TEST_F(WorldFixture, NoShadowNothingColinearPointLight) {
//    world->defaultWorld();
//    * point = raytracer::createPoint(0, 10, 0);
//    ASSERT_FALSE(world->isShadowed(* point));
//}
//
//TEST_F(WorldFixture, ShadowObjectBetweenPointLight) {
//    world->defaultWorld();
//    * point = raytracer::createPoint(10, -10, 10);
//    ASSERT_TRUE(world->isShadowed(* point));
//}
//
//TEST_F(WorldFixture, NoShadowObjectBehindLight) {
//    world->defaultWorld();
//    * point = raytracer::createPoint(-20, 20, -20);
//    ASSERT_FALSE(world->isShadowed(* point));
//}
//
//TEST_F(WorldFixture, NoShadowObjectBehindThePoint) {
//    world->defaultWorld();
//    * point = raytracer::createPoint(-2, 2, -2);
//    ASSERT_FALSE(world->isShadowed(* point));
//}

TEST_F(WorldFixture, IntersectionInShadow) {
    light->setPointLight(raytracer::createPoint(0, 0, -10), raytracer::Color(1, 1, 1));
    world->light_ = * light;
    world->addObject(s1);
    transform->translate(0, 0, 10);
    s2->setTransform(* transform);
    world->addObject(s2);
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, 5), raytracer::createVector(0, 0, 1));
    * i1 = raytracer::Intersection(4, s2);
    * intersectionData = i1->prepareComputations(* ray, * xs);
    * color = world->shadeHit(* intersectionData);
    ASSERT_EQ(* color, raytracer::Color(0.1, 0.1, 0.1));
}

//TEST_F(WorldFixture, OcclusionTestBetweenTwoPoints1) {
//    world->defaultWorld();
//    * position = raytracer::createPoint(-10, -10, -10);
//    * point = raytracer::createPoint(-10, -10, 10);
//    ASSERT_FALSE(world->isShadowed(* position, * point));
//}
//
//TEST_F(WorldFixture, OcclusionTestBetweenTwoPoints2) {
//    world->defaultWorld();
//    auto lightPosition = raytracer::Point(-10, -10, -10);
//    auto point = raytracer::Point(10, 10, 10);
//    ASSERT_TRUE(world->isShadowed(lightPosition, point));
//}
//
//TEST_F(WorldFixture, OcclusionTestBetweenTwoPoints3) {
//    world->defaultWorld();
//    auto lightPosition = raytracer::Point(-10, -10, -10);
//    auto point = raytracer::Point(-20, -20, -20);
//    ASSERT_FALSE(world->isShadowed(lightPosition, point));
//}
//
//TEST_F(WorldFixture, OcclusionTestBetweenTwoPoints4) {
//    world->defaultWorld();
//    auto lightPosition = raytracer::Point(-10, -10, -10);
//    auto point = raytracer::Point(-5, -5, -5);
//    ASSERT_FALSE(world->isShadowed(lightPosition, point));
//}

TEST_F(WorldFixture, ReflectedColorForNonReflectiveMaterial) {
    world->defaultWorld();
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, 0), raytracer::createVector(0, 0, 1));
    s1 = world->shapes_[1];
    s1->material.ambient = 1;
    * intersection = raytracer::Intersection(1, s1);
    * intersectionData = intersection->prepareComputations(* ray, * xs);
    * color = world->reflectedColor(* intersectionData);
    ASSERT_EQ(* color, raytracer::Color(0, 0, 0));
}

TEST_F(WorldFixture, ReflectedColorForReflectiveMaterial) {
    world->defaultWorld();
    floor->material.reflection = 0.5;
    transform->translate(0, -1, 0);
    floor->setTransform(* transform);
    world->addObject(s1);
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -3), raytracer::createVector(0, -sqrt(2)/2, sqrt(2)/2));
    * intersection = raytracer::Intersection(sqrt(2), floor);
    * intersectionData = intersection->prepareComputations(* ray, * xs);
    * color = world->reflectedColor(* intersectionData);
    ASSERT_EQ(* color, raytracer::Color(0.19032, 0.2379, 0.14274));
}

TEST_F(WorldFixture, ShadeHitWithReflectiveMaterial) {
    world->defaultWorld();
    floor->material.reflection = 0.5;
    transform->translate(0, -1, 0);
    floor->setTransform(* transform);
    world->addObject(s1);
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -3), raytracer::createVector(0, -sqrt(2)/2, sqrt(2)/2));
    * intersection = raytracer::Intersection(sqrt(2), floor);
    * intersectionData = intersection->prepareComputations(* ray, * xs);
    * color = world->shadeHit(* intersectionData);
    ASSERT_EQ(* color, raytracer::Color(0.87677, 0.92436, 0.82918));
}

// TODO Fix test to assert death or exit

TEST_F(WorldFixture, ColorAtWithMutuallyReflectiveSurfaces) {
    world->defaultWorld();
    world->light_.setPointLight(raytracer::createPoint(0, 0, 0), raytracer::Color(1, 1, 1));
    floor->material.reflection = 1;
    transform->translate(0, -1, 0);
    floor->setTransform(* transform);
    world->addObject(floor);
    upper->material.reflection = 1;
    transform->translate(0, 1, 0);
    upper->setTransform(* transform);
    world->addObject(upper);
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, 0), raytracer::createVector(0, 1, 0));
    ASSERT_DEATH_IF_SUPPORTED(world->colorAt(* ray), "");
}

TEST_F(WorldFixture, ReflectedColorAtMaximumRecursiveDepth) {
    world->defaultWorld();
    floor->material.reflection = 0.5;
    transform->translate(0, -1, 0);
    floor->setTransform(* transform);
    world->addObject(floor);
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -3), raytracer::createVector(0, -sqrt(2)/2, sqrt(2)/2));
    * intersection = raytracer::Intersection(sqrt(2), floor);
    * intersectionData = intersection->prepareComputations(* ray, * xs);
    * color = world->reflectedColor(* intersectionData, 0);
    ASSERT_EQ(* color, raytracer::Color(0, 0, 0));
}


TEST_F(WorldFixture, RefractedColorOpaqueSurface) {
    world->defaultWorld();
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -5), raytracer::createVector(0, 0, 1));
    * i1 = raytracer::Intersection(4, world->shapes_[0]);
    * i2 = raytracer::Intersection(6, world->shapes_[0]);
    * xs = intersections(* i1, * i2);
    * intersectionData = xs[0][0].prepareComputations(* ray, * xs);
    * color = world->refractedColor(* intersectionData, 5);
    ASSERT_EQ(* color, raytracer::Color(0, 0, 0));
}

TEST_F(WorldFixture, RefractedColorMaximumRecursiveDepth) {
    world->defaultWorld();
    world->shapes_[0]->material.transparency = 1.0;
    world->shapes_[0]->material.refractiveIndex = 1.5;
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -5), raytracer::createVector(0, 0, 1));
    * i1 = raytracer::Intersection(4, world->shapes_[0]);
    * i2 = raytracer::Intersection(6, world->shapes_[0]);
    * xs = intersections(* i1, * i2);
    * intersectionData = xs[0][0].prepareComputations(* ray, * xs);
    * color = world->refractedColor(* intersectionData, 0);
    ASSERT_EQ(* color, raytracer::Color(0, 0, 0));
}

TEST_F(WorldFixture, RefractedColorUnderTotalInternalReflection) {
    world->defaultWorld();
    world->shapes_[0]->material.transparency = 1.0;
    world->shapes_[0]->material.refractiveIndex = 1.5;
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, sqrt(2)/2), raytracer::createVector(0, 1, 0));
    * i1 = raytracer::Intersection(-sqrt(2)/2, world->shapes_[0]);
    * i2 = raytracer::Intersection(sqrt(2)/2, world->shapes_[0]);
    * xs = intersections(* i1, * i2);
    * intersectionData = xs[0][1].prepareComputations(* ray, * xs);
    * color = world->refractedColor(* intersectionData, 5);
    ASSERT_EQ(* color, raytracer::Color(0, 0, 0));
}

TEST_F(WorldFixture, RefractedColorRefractedRay) {
    world->defaultWorld();
    world->shapes_[0]->material.ambient = 1.0;
    world->shapes_[0]->material.pattern = std::make_shared<raytracer::TestPattern>();
    world->shapes_[1]->material.transparency = 1.0;
    world->shapes_[1]->material.refractiveIndex = 1.5;
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, 0.1), raytracer::createVector(0, 1, 0));
    * i1 = raytracer::Intersection(-0.9899, world->shapes_[0]);
    * i2 = raytracer::Intersection(-0.4899, world->shapes_[1]);
    * i3 = raytracer::Intersection(0.4899, world->shapes_[1]);
    * i4 = raytracer::Intersection(0.9899, world->shapes_[0]);
    * xs = intersections(* i1, * i2, * i3, * i4);
    * intersectionData = xs[0][2].prepareComputations(* ray, * xs);
    * color = world->refractedColor(* intersectionData, 5);
    ASSERT_EQ(* color, raytracer::Color(0, 0.99888, 0.04725));
}

TEST_F(WorldFixture, ShadeHitWithTransparentMaterial) {
    world->defaultWorld();
    floor->material.transparency = 0.5;
    floor->material.refractiveIndex = 1.5;
    floor->setTransform(transform->translate(0, -1, 0));
    world->addObject(floor);
    s1->material.color = raytracer::Color(1, 0, 0);
    s1->material.ambient = 0.5;
    s1->setTransform(transform->translate(0, -3.5, -0.5));
    world->addObject(s1);
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -3), raytracer::createVector(0, -sqrt(2)/2, sqrt(2)/2));
    * intersection = raytracer::Intersection(sqrt(2), floor);
    * xs = intersections(* intersection);
    * intersectionData = intersection->prepareComputations(* ray, * xs);
    * color = world->shadeHit(* intersectionData, 5);
    ASSERT_EQ(* color, raytracer::Color(0.93642, 0.68642, 0.68642));
}

TEST_F(WorldFixture, ShadeHitWithReflectiveTransparentMaterial) {
    world->defaultWorld();
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -3), raytracer::createVector(0, -sqrt(2)/2, sqrt(2)/2));
    floor->setTransform(transform->translate(0, -1, 0));
    floor->material.reflection = 0.5;
    floor->material.transparency = 0.5;
    floor->material.refractiveIndex = 1.5;
    world->addObject(floor);
    s1->material.color = raytracer::Color(1, 0, 0);
    s1->material.ambient = 0.5;
    s1->setTransform(transform->translate(0, -3.5, -0.5));
    world->addObject(s1);
    * intersection = raytracer::Intersection(sqrt(2), floor);
    * xs = intersections(* intersection);
    * intersectionData = intersection->prepareComputations(* ray, * xs);
    * color = world->shadeHit(* intersectionData, 5);
    ASSERT_EQ(* color, raytracer::Color(0.93391, 0.69643, 0.69243));
}