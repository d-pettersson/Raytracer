#include "material.h"
#include "light.h"

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
    }

    virtual void TearDown() {
        delete material;
        delete position;
        delete eye;
        delete normal;
        delete light;
        delete result;
    }

    raytracer::Material * material;
    raytracer::Point * position;
    raytracer::Vector * eye;
    raytracer::Vector * normal;
    raytracer::Light * light;
    raytracer::Color * result;
};

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
    * result = material->setPhongLighting(* light, * position, * eye, * normal);
    ASSERT_EQ(* result, raytracer::Color(1.9, 1.9, 1.9));
}

TEST_F(MaterialFixture, EyeBetweenLightAndSurfaceOffset) {
    * position = raytracer::Point(0, 0, 0);
    * eye = raytracer::Vector(0, sqrt(2)/2, -sqrt(2)/2);
    * normal = raytracer::Vector(0, 0, -1);
    light->setPointLight(raytracer::Point(0, 0, -10), raytracer::Color(1, 1, 1));
    * result = material->setPhongLighting(* light, * position, * eye, * normal);
    ASSERT_EQ(* result, raytracer::Color(1.0, 1.0, 1.0));
}

TEST_F(MaterialFixture, EyeOppositeSurfaceOffset) {
    * position = raytracer::Point(0, 0, 0);
    * eye = raytracer::Vector(0, 0, -1);
    * normal = raytracer::Vector(0, 0, -1);
    light->setPointLight(raytracer::Point(0, 10, -10), raytracer::Color(1, 1, 1));
    * result = material->setPhongLighting(* light, * position, * eye, * normal);
    ASSERT_EQ(* result, raytracer::Color(0.7364, 0.7364, 0.7364));
}

TEST_F(MaterialFixture, EyeInPathReflection) {
    * position = raytracer::Point(0, 0, 0);
    * eye = raytracer::Vector(0, -sqrt(2)/2, -sqrt(2)/2);
    * normal = raytracer::Vector(0, 0, -1);
    light->setPointLight(raytracer::Point(0, 10, -10), raytracer::Color(1, 1, 1));
    * result = material->setPhongLighting(* light, * position, * eye, * normal);
    ASSERT_EQ(* result, raytracer::Color(1.63644, 1.6364, 1.6364));
}

TEST_F(MaterialFixture, LightingBehindSurface) {
    * position = raytracer::Point(0, 0, 0);
    * eye = raytracer::Vector(0, 0, -1);
    * normal = raytracer::Vector(0, 0, -1);
    light->setPointLight(raytracer::Point(0, 0, 10), raytracer::Color(1, 1, 1));
    * result = material->setPhongLighting(* light, * position, * eye, * normal);
    ASSERT_EQ(* result, raytracer::Color(0.1, 0.1, 0.1));
}