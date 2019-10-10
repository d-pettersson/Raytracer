#include "light.h"
#include "world.h"
#include "utils.h"

#include "gtest/gtest.h"

class LightFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        light = new raytracer::Light();
        intensity = new raytracer::Color();
        position = new raytracer::Point();
        point = new raytracer::Point();
        world = new raytracer::World();
        gen = new raytracer::Gen();
    }

    virtual void TearDown() {
        delete light;
        delete intensity;
        delete position;
        delete point;
        delete world;
        delete gen;
    }

    raytracer::Light * light;
    raytracer::Color * intensity;
    raytracer::Point * position;
    raytracer::Point * point;
    raytracer::World * world;
    raytracer::Gen * gen;

};

// the following tests work with an fixed offset in the light position of 0.5 instead of a random pos

TEST_F(LightFixture, PointLight) {
    * intensity = raytracer::Color(1, 1, 1);
    * position = raytracer::Point(0, 0, 0);
    light->setPointLight(* position, * intensity);
    ASSERT_EQ(light->intensity, raytracer::Color(1, 1, 1));
    ASSERT_EQ(light->position, raytracer::Point(0, 0, 0));
}

TEST_F(LightFixture, PointLightEvaluationAtGivenPoint) {
    world->defaultWorld();
    * point = raytracer::Point(0, 1.0001, 0);
    float intens = world->light.intensityAt(* point, * world);
    ASSERT_EQ(1.0, intens);
}

TEST_F(LightFixture, PointLightEvaluationAtGivenPoint1) {
    world->defaultWorld();
    * point = raytracer::Point(-1.0001, 0, 0);
    float intens = world->light.intensityAt(* point, * world);
    ASSERT_EQ(1.0, intens);
}

TEST_F(LightFixture, PointLightEvaluationAtGivenPoint2) {
    world->defaultWorld();
    *point = raytracer::Point(0, 0, -1.0001);
    float intens = world->light.intensityAt(* point, * world);
    ASSERT_EQ(1.0, intens);
}

TEST_F(LightFixture, PointLightEvaluationAtGivenPoint3) {
    world->defaultWorld();
    *point = raytracer::Point(0, 0, 1.0001);
    float intens = world->light.intensityAt(* point, * world);
    ASSERT_EQ(0.0, intens);
}

TEST_F(LightFixture, PointLightEvaluationAtGivenPoint4) {
    world->defaultWorld();
    *point = raytracer::Point(1.0001, 0, 0);
    float intens = world->light.intensityAt(* point, * world);
    ASSERT_EQ(0.0, intens);
}

TEST_F(LightFixture, PointLightEvaluationAtGivenPoint5) {
    world->defaultWorld();
    *point = raytracer::Point(0, -1.0001, 0);
    float intens = world->light.intensityAt(* point, * world);
    ASSERT_EQ(0.0, intens);
}

TEST_F(LightFixture, PointLightEvaluationAtGivenPoint6) {
    world->defaultWorld();
    *point = raytracer::Point(0, 0, 0);
    float intens = world->light.intensityAt(* point, * world);
    ASSERT_EQ(0.0, intens);
}

// Area light test (random position)

TEST_F(LightFixture, CreatingAreaLight) {
    * point = raytracer::Point(0, 0, 0);
    auto v1 = raytracer::Vector(2, 0, 0);
    auto v2 = raytracer::Vector(0, 0, 1);
    light->setAreaLight(* point, v1, 4, v2, 2, * intensity);
    ASSERT_EQ(light->corner, * point);
    ASSERT_EQ(light->uVec, raytracer::Vector(0.5, 0, 0));
    ASSERT_EQ(light->uSteps, 4);
    ASSERT_EQ(light->vVec, raytracer::Vector(0, 0, 0.5));
    ASSERT_EQ(light->vSteps, 2);
    ASSERT_EQ(light->samples, 8);
    ASSERT_EQ(light->position, raytracer::Point(1, 0, 0.5));
}

TEST_F(LightFixture, SinglePointOnAreaLight) {
    * point = raytracer::Point(0, 0, 0);
    auto v1 = raytracer::Vector(2, 0, 0);
    auto v2 = raytracer::Vector(0, 0, 1);
    light->setAreaLight(* point, v1, 4, v2, 2, * intensity);
    auto pt = light->pointOnLight(0, 0);
    ASSERT_EQ(pt, raytracer::Point(0.25, 0, 0.25));
    pt = light->pointOnLight(1, 0);
    ASSERT_EQ(pt, raytracer::Point(0.75, 0, 0.25));
    pt = light->pointOnLight(0, 1);
    ASSERT_EQ(pt, raytracer::Point(0.25, 0, 0.75));
    pt = light->pointOnLight(2, 0);
    ASSERT_EQ(pt, raytracer::Point(1.25, 0, 0.25));
    pt = light->pointOnLight(3, 1);
    ASSERT_EQ(pt, raytracer::Point(1.75, 0, 0.75));
}

TEST_F(LightFixture, AreaLightIntensityAt) {
    world->defaultWorld();
    * point = raytracer::Point(-0.5, -0.5, -5);
    auto v1 = raytracer::Vector(1, 0, 0);
    auto v2 = raytracer::Vector(0, 1, 0);
    light->setAreaLight(* point, v1, 2, v2, 2, raytracer::Color(1, 1, 1));
    auto pt = raytracer::Point(0, 0, 2);
    float intensity = light->intensityAt(pt, * world);
    EXPECT_EQ(0.0, intensity);
    pt = raytracer::Point(1, -1, 2);
    intensity = light->intensityAt(pt, * world);
    EXPECT_EQ(0.25, intensity);
    pt = raytracer::Point(1.5, 0, 2);
    intensity = light->intensityAt(pt, * world);
    EXPECT_EQ(0.5, intensity);
    pt = raytracer::Point(1.25, 1.25, 3);
    intensity = light->intensityAt(pt, * world);
    EXPECT_EQ(0.75, intensity);
    pt = raytracer::Point(0, 0, -2);
    intensity = light->intensityAt(pt, * world);
    ASSERT_EQ(1.0, intensity);
}

// this test works with this->uVec * (u + 0.3), and this->vVec * (v + 0.7)
// actual function works with a random number generator

TEST_F(LightFixture, AreaLightNoiseDistribution) {
    world->defaultWorld();
    * point = raytracer::Point(0, 0, 0);
    auto v1 = raytracer::Vector(2, 0, 0);
    auto v2 = raytracer::Vector(0, 0, 1);
    light->setAreaLight(* point, v1, 4, v2, 2, raytracer::Color(1, 1, 1));

    auto pt = light->pointOnLight(0, 0);
    EXPECT_EQ(raytracer::Point(0.15, 0, 0.35), pt);

    pt = light->pointOnLight(1, 0);
    EXPECT_EQ(raytracer::Point(0.65, 0, 0.35), pt);

    pt = light->pointOnLight(0, 1);
    EXPECT_EQ(raytracer::Point(0.15, 0, 0.85), pt);

    pt = light->pointOnLight(2, 0);
    EXPECT_EQ(raytracer::Point(1.15, 0, 0.35), pt);

    pt = light->pointOnLight(3, 1);
    EXPECT_EQ(raytracer::Point(1.65, 0, 0.85), pt);
}