#include "include/world.h"
#include "include/intersection.h"

#include "gtest/gtest.h"

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
        intersectionData = new raytracer::IntersectionData();
        color = new raytracer::Color();
        position = new raytracer::Point();
    }

    virtual void TearDown() {
        delete world;
        delete light;
        delete transform;
        delete ray;
        delete xs;
        delete intersection;
        delete intersectionData;
        delete color;
        delete position;
    }

    raytracer::World * world;
    raytracer::Light * light;
    raytracer::Ray * ray;
    std::shared_ptr<raytracer::Shape> s1 = std::make_shared<raytracer::Sphere>();
    std::shared_ptr<raytracer::Shape> s2 = std::make_shared<raytracer::Sphere>();
    raytracer::Transform * transform;
    std::vector<raytracer::Intersection> * xs;
    raytracer::Intersection * intersection;
    raytracer::IntersectionData * intersectionData;
    raytracer::Color * color;
    raytracer::Point * position;
};

// Test empty data structure?
//TEST_F(WorldFixture, TestDataStructure) {
//    ASSERT_EQ(nullptr, world);
//}

TEST_F(WorldFixture, DefaultWorld) {
    world->defaultWorld();
    s1->material.color = raytracer::Color(0.8, 1.0, 0.6);
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;
    s2->setTransform(transform->scale(0.5, 0.5, 0.5));
    ASSERT_EQ(raytracer::Light(raytracer::Point(-10, 10, -10), raytracer::Color(1, 1, 1)), world->light);
    ASSERT_EQ(s1->material.diffuse, world->shapes[0]->material.diffuse);
    ASSERT_EQ(s1->material.color, world->shapes[0]->material.color);
    ASSERT_EQ(s1->material.specular, world->shapes[0]->material.specular);
    ASSERT_EQ(s2->getTransform(), world->shapes[1]->getTransform());
}

TEST_F(WorldFixture, WorldRayIntersection) {
    world->defaultWorld();
    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    world->intersectWorld(* ray, xs);
    ASSERT_EQ(xs->size(), 4);
    ASSERT_EQ(xs[0][0].getDistance(), 4);
    ASSERT_EQ(xs[0][1].getDistance(), 4.5);
    ASSERT_EQ(xs[0][2].getDistance(), 5.5);
    ASSERT_EQ(xs[0][3].getDistance(), 6);
}

TEST_F(WorldFixture, IntersectionShading) {
    world->defaultWorld();
    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    s1 = world->shapes[0];
    * intersection = raytracer::Intersection(4, s1);
    * intersectionData = intersection->prepareComputations(* ray);
    * color = world->shadeHit(* intersectionData);
    ASSERT_EQ(raytracer::Color(0.38066, 0.47583, 0.2855), * color);
}

TEST_F(WorldFixture, InsideIntersectionShading) {
    world->defaultWorld();
    light->setPointLight(raytracer::Point(0, 0.25, 0), raytracer::Color(1, 1, 1));
    world->light = * light;
    * ray = raytracer::Ray(raytracer::Point(0, 0, 0), raytracer::Vector(0, 0, 1));
    s2 = world->shapes[1];
    * intersection = raytracer::Intersection(0.5, s2);
    * intersectionData = intersection->prepareComputations(* ray);
    * color = world->shadeHit(* intersectionData);
    ASSERT_EQ(raytracer::Color(0.90498, 0.90498, 0.90498), * color);
}

TEST_F(WorldFixture, ColorWhenRayMisses) {
    world->defaultWorld();
    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 1, 0));
    * color = world->colorAt(* ray);
    ASSERT_EQ(raytracer::Color(0, 0, 0), * color);
}

TEST_F(WorldFixture, ColorWhenRayHits) {
    world->defaultWorld();
    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    * color = world->colorAt(* ray);
    ASSERT_EQ(raytracer::Color(0.38066, 0.47583, 0.2855), * color);
}

TEST_F(WorldFixture, ColorWithIntersectionBehindRay) {
    world->defaultWorld();
    * ray = raytracer::Ray(raytracer::Point(0, 0, 0.75), raytracer::Vector(0, 0, -1));
    s1 = world->shapes[0];
    s1->material.ambient = 1;
    s2 = world->shapes[1];
    s2->material.ambient = 1;
    * color = world->colorAt(* ray);
    ASSERT_EQ(s2->material.color, * color);
}


// change to world isShadowed methods
// for soft shadow implementation breaks tests
// functionality stays the same with new variable

//TEST_F(WorldFixture, NoShadowNothingColinearPointLight) {
//    world->defaultWorld();
//    raytracer::Point point = raytracer::Point(0, 10, 0);
//    ASSERT_FALSE(world->isShadowed(point));
//}
//
//TEST_F(WorldFixture, ShadowObjectBetweenPointLight) {
//    world->defaultWorld();
//    raytracer::Point point = raytracer::Point(10, -10, 10);
//    ASSERT_TRUE(world->isShadowed(point));
//}
//
//TEST_F(WorldFixture, NoShadowObjectBehindLight) {
//    world->defaultWorld();
//    raytracer::Point point = raytracer::Point(-20, 20, -20);
//    ASSERT_FALSE(world->isShadowed(point));
//}
//
//TEST_F(WorldFixture, NoShadowObjectBehindThePoint) {
//    world->defaultWorld();
//    raytracer::Point point = raytracer::Point(-2, 2, -2);
//    ASSERT_FALSE(world->isShadowed(point));
//}

TEST_F(WorldFixture, IntersectionInShadow) {
    light->setPointLight(raytracer::Point(0, 0, -10), raytracer::Color(1, 1, 1));
    world->light = * light;
    world->addObject(s1);
    transform->translate(0, 0, 10);
    s2->setTransform(* transform);
    world->addObject(s2);
    * ray = raytracer::Ray(raytracer::Point(0, 0, 5), raytracer::Vector(0, 0, 1));
    auto i = raytracer::Intersection(4, s2);
    * intersectionData = i.prepareComputations(* ray);
    * color = world->shadeHit(* intersectionData);
    ASSERT_EQ(* color, raytracer::Color(0.1, 0.1, 0.1));
}

TEST_F(WorldFixture, OcclusionTestBetweenTwoPoints1) {
    world->defaultWorld();
    auto lightPosition = raytracer::Point(-10, -10, -10);
    auto point = raytracer::Point(-10, -10, 10);
    ASSERT_FALSE(world->isShadowed(lightPosition, point));
}

TEST_F(WorldFixture, OcclusionTestBetweenTwoPoints2) {
    world->defaultWorld();
    auto lightPosition = raytracer::Point(-10, -10, -10);
    auto point = raytracer::Point(10, 10, 10);
    ASSERT_TRUE(world->isShadowed(lightPosition, point));
}

TEST_F(WorldFixture, OcclusionTestBetweenTwoPoints3) {
    world->defaultWorld();
    auto lightPosition = raytracer::Point(-10, -10, -10);
    auto point = raytracer::Point(-20, -20, -20);
    ASSERT_FALSE(world->isShadowed(lightPosition, point));
}

TEST_F(WorldFixture, OcclusionTestBetweenTwoPoints4) {
    world->defaultWorld();
    auto lightPosition = raytracer::Point(-10, -10, -10);
    auto point = raytracer::Point(-5, -5, -5);
    ASSERT_FALSE(world->isShadowed(lightPosition, point));
}

