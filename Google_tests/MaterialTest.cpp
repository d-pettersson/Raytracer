#include "include/material.h"
#include "include/light.h"
#include "include/world.h"
#include "include/shape.h"

#include <cmath>

#include "gtest/gtest.h"

class MaterialFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        material = new raytracer::Material();
        position = new raytracer::Point();
        eye = new raytracer::Vector();
        normal = new raytracer::Vector();
        light = new raytracer::Light();
        result = new raytracer::Color();
        world = new raytracer::World();
    }

    virtual void TearDown() {
        delete material;
        delete position;
        delete eye;
        delete normal;
        delete light;
        delete result;
        delete world;
    }

    raytracer::Material * material;
    raytracer::Point * position;
    raytracer::Vector * eye;
    raytracer::Vector * normal;
    raytracer::Light * light;
    raytracer::Color * result;
    float intensity = false;
    raytracer::World * world;
    std::shared_ptr<raytracer::Shape> shape = std::make_shared<raytracer::Sphere>();
    std::shared_ptr<raytracer::Pattern> pattern;
};

// TODO: fix the test, pass a sphere to the phong lighting function

TEST_F(MaterialFixture, MemberAccess) {
    ASSERT_EQ(material->color, raytracer::Color(1, 1, 1));
    ASSERT_EQ(material->ambient, 0.1);
    ASSERT_EQ(material->diffuse, 0.9);
    ASSERT_EQ(material->specular, 0.9);
    ASSERT_EQ(material->shininess, 200.0);
}

TEST_F(MaterialFixture, EyeBetweenLightAndSurface) {
    * position = raytracer::Point(0, 0, 0);
    * eye = raytracer::Vector(0, 0, -1);
    * normal = raytracer::Vector(0, 0, -1);
    light->setPointLight(raytracer::Point(0, 0, -10), raytracer::Color(1, 1, 1));
    * result = material->setPhongLighting(shape, * light, * position, * eye, * normal, intensity);
    ASSERT_EQ(* result, raytracer::Color(1.9, 1.9, 1.9));
}

TEST_F(MaterialFixture, EyeBetweenLightAndSurfaceOffset) {
    * position = raytracer::Point(0, 0, 0);
    * eye = raytracer::Vector(0, sqrt(2)/2, -sqrt(2)/2);
    * normal = raytracer::Vector(0, 0, -1);
    light->setPointLight(raytracer::Point(0, 0, -10), raytracer::Color(1, 1, 1));
    * result = material->setPhongLighting(shape, * light, * position, * eye, * normal, intensity);
    ASSERT_EQ(* result, raytracer::Color(1.0, 1.0, 1.0));
}

TEST_F(MaterialFixture, EyeOppositeSurfaceOffset) {
    * position = raytracer::Point(0, 0, 0);
    * eye = raytracer::Vector(0, 0, -1);
    * normal = raytracer::Vector(0, 0, -1);
    light->setPointLight(raytracer::Point(0, 10, -10), raytracer::Color(1, 1, 1));
    * result = material->setPhongLighting(shape, * light, * position, * eye, * normal, intensity);
    ASSERT_EQ(* result, raytracer::Color(0.7364, 0.7364, 0.7364));
}

TEST_F(MaterialFixture, EyeInPathReflection) {
    * position = raytracer::Point(0, 0, 0);
    * eye = raytracer::Vector(0, -sqrt(2)/2, -sqrt(2)/2);
    * normal = raytracer::Vector(0, 0, -1);
    light->setPointLight(raytracer::Point(0, 10, -10), raytracer::Color(1, 1, 1));
    * result = material->setPhongLighting(shape, * light, * position, * eye, * normal, intensity);
    ASSERT_EQ(* result, raytracer::Color(1.63644, 1.6364, 1.6364));
}

TEST_F(MaterialFixture, LightingBehindSurface) {
    * position = raytracer::Point(0, 0, 0);
    * eye = raytracer::Vector(0, 0, -1);
    * normal = raytracer::Vector(0, 0, -1);
    light->setPointLight(raytracer::Point(0, 0, 10), raytracer::Color(1, 1, 1));
    * result = material->setPhongLighting(shape, * light, * position, * eye, * normal, intensity);
    ASSERT_EQ(* result, raytracer::Color(0.1, 0.1, 0.1));
}

TEST_F(MaterialFixture, LightingSurfaceShadow) {
    * position = raytracer::Point(0, 0, 0);
    * eye = raytracer::Vector(0, 0, -1);
    * normal = raytracer::Vector(0, 0, -1);
    light->setPointLight(raytracer::Point(0, 0, -10), raytracer::Color(1, 1, 1));
    intensity = true;
    * result = material->setPhongLighting(shape, * light, * position, * eye, * normal, intensity);
    ASSERT_EQ(* result, raytracer::Color(0.1, 0.1, 0.1));
}

TEST_F(MaterialFixture, LightIntensityShadow) {
    world->defaultWorld();
    world->light = raytracer::Light(raytracer::Point(0, 0, -10), raytracer::Color(1, 1, 1));
    world->shapes[0]->material.ambient = 0.1;
    world->shapes[0]->material.diffuse = 0.9;
    world->shapes[0]->material.specular = 0;
    world->shapes[0]->material.color = raytracer::Color(1, 1, 1);
    raytracer::Point point = raytracer::Point(0, 0, -1);
    raytracer::Vector eye = raytracer::Vector(0, 0, -1);
    raytracer::Vector normal = raytracer::Vector(0, 0, -1);
    * result = world->shapes[0]->material.setPhongLighting(shape, world->light, point, eye, normal, 1.0);
    ASSERT_EQ(raytracer::Color(1, 1, 1), * result);
    * result = world->shapes[0]->material.setPhongLighting(shape, world->light, point, eye, normal, 0.5);
    ASSERT_EQ(raytracer::Color(0.55, 0.55, 0.55), * result);
    * result = world->shapes[0]->material.setPhongLighting(shape, world->light, point, eye, normal, 0.0);
    ASSERT_EQ(raytracer::Color(0.1, 0.1, 0.1), * result);
}

// this test doesn't work as the sampled points for the shadows != sampled points for the lighting

TEST_F(MaterialFixture, NewPhongLighting) {
    auto * corner = new raytracer::Point(-0.5, -0.5, -5);
    auto * v1 = new raytracer::Vector(1, 0, 0);
    auto * v2 = new raytracer::Vector(0, 1, 0);
    light->setAreaLight(* corner, * v1, 2, * v2, 2, raytracer::Color(1, 1, 1));
    shape->material.ambient = 0.1;
    shape->material.diffuse = 0.9;
    shape->material.specular = 0;
    shape->material.color = raytracer::Color(1, 1, 1);
    auto * eye = new raytracer::Point(0, 0, -5);
    auto * pt = new raytracer::Point(0, 0, -1);
    raytracer::Vector eyev = normalize(* eye - * pt);
    raytracer::Vector normalv = raytracer::Vector(pt->x, pt->y, pt->z);

    * result = shape->material.setPhongLighting(shape, * light, * pt, eyev, normalv, 1.0);
    EXPECT_EQ(raytracer::Color(0.9965, 0.9965, 0.9965), * result);

    * pt = raytracer::Point(0, 0.7071, -0.7071);
    eyev = normalize(* eye - * pt);
    normalv = raytracer::Vector(pt->x, pt->y, pt->z);
    * result = shape->material.setPhongLighting(shape, * light, * pt, eyev, normalv, 1.0);
    ASSERT_EQ(raytracer::Color(0.6232, 0.6232, 0.6232), * result);
}

TEST_F(MaterialFixture, LightingWithPattern) {
    material->pattern = std::make_shared<raytracer::StripePattern>(raytracer::Color(1, 1, 1), raytracer::Color(0, 0, 0));
    material->ambient = 1;
    material->diffuse = 0;
    material->specular = 0;
    * eye = raytracer::Vector(0, 0, -1);
    * normal = raytracer::Vector(0, 0, -1);
    light->setPointLight(raytracer::Point(0, 0, -10), raytracer::Color(1, 1, 1));
    raytracer::Color c1 = material->setPhongLighting(shape, * light, raytracer::Point(0.9, 0, 0), * eye, * normal, false);
    raytracer::Color c2 = material->setPhongLighting(shape, * light, raytracer::Point(1.1, 0, 0), * eye, * normal, false);
    EXPECT_EQ(c1, raytracer::Color(1, 1, 1));
    ASSERT_EQ(c2, raytracer::Color(0, 0, 0));
}

TEST_F(MaterialFixture, CheckingForReflectivePar) {
    material->reflection = 0.0;
    ASSERT_EQ(material->reflection, 0.0);
}

