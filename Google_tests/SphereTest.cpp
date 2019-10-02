#include "ray.h"
#include "sphere.h"
#include "tuple.h"
#include "transform.h"

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
        normal = new raytracer::Vector();
        material = new raytracer::Material();
    }

    virtual void TearDown() {
        delete ray;
        delete transformation;
        delete translate;
        delete rotate;
        delete scale;
        delete normal;
        delete material;
    }

    raytracer::Ray * ray;
    std::shared_ptr<raytracer::Shape> sphere = std::make_shared<raytracer::Sphere>();
    std::vector<raytracer::Intersection> xs;
    raytracer::Transform * transformation;
    raytracer::Transform * translate;
    raytracer::Transform * rotate;
    raytracer::Transform * scale;
    raytracer::Vector * normal;
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
    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    scale->scale(2, 2, 2);
    sphere->setTransform(* scale);
    sphere->intersect(* ray, xs);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].getDistance(), 3);
    ASSERT_EQ(xs[1].getDistance(), 7);
}

TEST_F(SphereFixture, IntersectingTranslatedSphere) {
    * ray = raytracer::Ray(raytracer::Point(0, 0, -5), raytracer::Vector(0, 0, 1));
    translate->translate(5, 0, 0);
    sphere->setTransform(* translate);
    sphere->intersect(* ray, xs);
    ASSERT_EQ(xs.size(), 0);
}

TEST_F(SphereFixture, NormalSphereX) {
    * normal = sphere->getNormal(raytracer::Point(1, 0, 0));
    ASSERT_EQ(* normal, raytracer::Vector(1, 0, 0));
}

TEST_F(SphereFixture, NormalSphereY) {
    * normal = sphere->getNormal(raytracer::Point(0, 1, 0));
    ASSERT_EQ(* normal, raytracer::Vector(0, 1, 0));
}

TEST_F(SphereFixture, NormalSphereZ) {
    * normal = sphere->getNormal(raytracer::Point(0, 0, 1));
    ASSERT_EQ(* normal, raytracer::Vector(0, 0, 1));
}

TEST_F(SphereFixture, NormalSphereNonAxial) {
    * normal = sphere->getNormal(raytracer::Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    ASSERT_EQ(* normal, raytracer::Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
}

TEST_F(SphereFixture, NormalSphereAlwaysNormalized) {
    * normal = sphere->getNormal(raytracer::Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
    ASSERT_EQ(* normal, normalize(* normal));
}

TEST_F(SphereFixture, NormalTranslatedSphere) {
    translate->translate(0, 1, 0);
    sphere->setTransform(* translate);
    * normal = sphere->getNormal(raytracer::Point(0, 1.70711, -0.70711));
    ASSERT_EQ(* normal, raytracer::Vector(0, 0.70711, -0.70711));
}

TEST_F(SphereFixture, NormalTransformedSphere) {
    scale->scale(1, 0.5, 1);
    rotate->rotateZ(PI / 5);
    * transformation = * scale * * rotate;
    sphere->setTransform(* transformation);
    * normal = sphere->getNormal(raytracer::Point(0, sqrt(2) / 2, -sqrt(2) / 2));
    ASSERT_EQ(* normal, raytracer::Vector(0, 0.97014, -0.24254));
}

TEST_F(SphereFixture, DefaultMaterialSphere) {
    ASSERT_EQ(sphere->material, raytracer::Material());
}

TEST_F(SphereFixture, AssignMaterialSphere) {
    material->ambient = 1;
    sphere->material = * material;
    ASSERT_EQ(sphere->material, * material);
}

