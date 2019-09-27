#include "ray.h"
#include "sphere.h"

#include "gtest/gtest.h"

class SphereFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        ray = new raytracer::Ray();
        transformation = new raytracer::Transform();
        translate = new raytracer::Transform();
        scale = new raytracer::Transform();
    }

    virtual void TearDown() {
        delete ray;
        delete transformation;
        delete translate;
        delete scale;
    }

    raytracer::Ray * ray;
    std::shared_ptr<raytracer::Shape> sphere = std::make_shared<raytracer::Sphere>();
    std::vector<raytracer::Intersection> xs;
    raytracer::Transform * transformation;
    raytracer::Transform * translate;
    raytracer::Transform * scale;
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