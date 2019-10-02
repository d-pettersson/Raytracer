#include "light.h"

#include "gtest/gtest.h"

class LightFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        light = new raytracer::Light();
        intensity = new raytracer::Color();
        position = new raytracer::Point();
    }

    virtual void TearDown() {
        delete light;
        delete intensity;
        delete position;

    }

    raytracer::Light * light;
    raytracer::Color * intensity;
    raytracer::Point * position;
};

TEST_F(LightFixture, PointLight) {
    * intensity = raytracer::Color(1, 1, 1);
    * position = raytracer::Point(0, 0, 0);
    light->setPointLight(* position, * intensity);
    ASSERT_EQ(light->intensity, raytracer::Color(1, 1, 1));
    ASSERT_EQ(light->position, raytracer::Point(0, 0, 0));
}