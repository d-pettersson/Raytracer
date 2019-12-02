#include "include/ray.h"
#include "include/sphere.h"
#include "include/tuple.h"
#include "include/transform.h"
#include "include/matrix.h"

#include "gtest/gtest.h"

#include <cmath>

class SphereFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        ray = new raytracer::Ray();
        transformation = new raytracer::Transform();
        translate = new raytracer::Transform();
        rotate = new raytracer::Transform();
        scale = new raytracer::Transform();
        identity = new raytracer::Matrix();
        normal = new raytracer::Tuple();
        material = new raytracer::Material();
        xs = new std::vector<raytracer::Intersection>();
    }

    virtual void TearDown() {
        delete ray;
        delete transformation;
        delete translate;
        delete rotate;
        delete scale;
        delete identity;
        delete normal;
        delete material;
        delete xs;
    }

    raytracer::Ray * ray;
    std::shared_ptr<raytracer::Shape> sphere = std::make_shared<raytracer::Sphere>();
    std::vector<raytracer::Intersection> * xs;
    raytracer::Transform * transformation;
    raytracer::Transform * translate;
    raytracer::Transform * rotate;
    raytracer::Transform * scale;
    raytracer::Matrix * identity;
    raytracer::Tuple * normal;
    raytracer::Material * material;
};

TEST_F(SphereFixture, DefaultTransformation) {
    ASSERT_EQ(sphere->getTransform(), raytracer::generateIdentity(4, 4));
}

TEST_F(SphereFixture, ChangingTransformation) {
    translate->translate(2, 3, 4);
    sphere->setTransform(* translate);
    ASSERT_EQ(sphere->getTransform(), * translate);
}

TEST_F(SphereFixture, IntersectingScaledSphere) {
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -5), raytracer::createVector(0, 0, 1));
    scale->scale(2, 2, 2);
    sphere->setTransform(* scale);
    sphere->intersect(* ray, * xs);
    EXPECT_EQ(xs->size(), 2);
    EXPECT_EQ(xs[0][0].getDistance(), 3);
    ASSERT_EQ(xs[0][1].getDistance(), 7);
}

TEST_F(SphereFixture, IntersectingTranslatedSphere) {
    * ray = raytracer::Ray(raytracer::createPoint(0, 0, -5), raytracer::createVector(0, 0, 1));
    translate->translate(5, 0, 0);
    sphere->setTransform(* translate);
    sphere->intersect(* ray, * xs);
    ASSERT_EQ(xs->size(), 0);
}

TEST_F(SphereFixture, NormalSphereX) {
    * normal = sphere->getNormal(raytracer::createPoint(1, 0, 0));
    ASSERT_EQ(* normal, raytracer::createVector(1, 0, 0));
}

TEST_F(SphereFixture, NormalSphereY) {
    * normal = sphere->getNormal(raytracer::createPoint(0, 1, 0));
    ASSERT_EQ(* normal, raytracer::createVector(0, 1, 0));
}

TEST_F(SphereFixture, NormalSphereZ) {
    * normal = sphere->getNormal(raytracer::createPoint(0, 0, 1));
    ASSERT_EQ(* normal, raytracer::createVector(0, 0, 1));
}

TEST_F(SphereFixture, NormalSphereNonAxial) {
    * normal = sphere->getNormal(raytracer::createPoint(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    ASSERT_EQ(* normal, raytracer::createVector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
}

TEST_F(SphereFixture, NormalSphereAlwaysNormalized) {
    * normal = sphere->getNormal(raytracer::createPoint(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    ASSERT_EQ(* normal, normalize(* normal));
}

TEST_F(SphereFixture, NormalTranslatedSphere) {
    translate->translate(0, 1, 0);
    sphere->setTransform(* translate);
    * normal = sphere->getNormal(raytracer::createPoint(0, 1.70711, -0.70711));
    ASSERT_EQ(* normal, raytracer::createVector(0, 0.70711, -0.70711));
}

TEST_F(SphereFixture, NormalTransformedSphere) {
    scale->scale(1, 0.5, 1);
    rotate->rotateZ(PI / 5);
    * transformation = * scale * * rotate;
    sphere->setTransform(* transformation);
    * normal = sphere->getNormal(raytracer::createPoint(0, sqrt(2) / 2, -sqrt(2) / 2));
    ASSERT_EQ(* normal, raytracer::createVector(0, 0.97014, -0.24254));
}

TEST_F(SphereFixture, DefaultMaterialSphere) {
    ASSERT_EQ(sphere->material, raytracer::Material());
}

TEST_F(SphereFixture, AssignMaterialSphere) {
    material->ambient = 1;
    sphere->material = * material;
    ASSERT_EQ(sphere->material, * material);
}

TEST_F(SphereFixture, SphereWithGlassyMaterial) {
    sphere->createGlass();
    * identity = raytracer::generateIdentity(4, 4);
    EXPECT_EQ(* identity, sphere->getTransform());
    EXPECT_EQ(sphere->material.transparency, 1.0);
    ASSERT_EQ(sphere->material.refractiveIndex, 1.5);
}

