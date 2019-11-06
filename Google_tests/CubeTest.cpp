#include "include/ray.h"
#include "include/cube.h"
#include "include/tuple.h"
#include "include/transform.h"
#include "include/matrix.h"

#include "gtest/gtest.h"

#include <cmath>

class CubeFixture : public ::testing::Test {

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
    std::shared_ptr<raytracer::Shape> cube = std::make_shared<raytracer::Cube>();
    std::vector<raytracer::Intersection> xs;
    raytracer::Transform * transformation;
    raytracer::Transform * translate;
    raytracer::Transform * rotate;
    raytracer::Transform * scale;
    raytracer::Vector * normal;
    raytracer::Material * material;
};

TEST_F(CubeFixture, IntersectingScaledSphere) {
    * ray = raytracer::Ray(raytracer::Point(5, 0.5, 0), raytracer::Vector(-1, 0, 0));
    cube->intersect(* ray, xs);
    EXPECT_EQ(xs.size(), 2);
    EXPECT_EQ(xs[0].getDistance(), 4);
    EXPECT_EQ(xs[1].getDistance(), 6);

    * ray = raytracer::Ray(raytracer::Point(-5, 0.5, 0), raytracer::Vector(1, 0, 0));
    EXPECT_EQ(xs[0].getDistance(), 4);
    EXPECT_EQ(xs[1].getDistance(), 6);

    * ray = raytracer::Ray(raytracer::Point(0.5, 5, 0), raytracer::Vector(0, -1, 0));
    EXPECT_EQ(xs[0].getDistance(), 4);
    EXPECT_EQ(xs[1].getDistance(), 6);

    * ray = raytracer::Ray(raytracer::Point(0.5, -5, 0), raytracer::Vector(0, 1, 0));
    EXPECT_EQ(xs[0].getDistance(), 4);
    EXPECT_EQ(xs[1].getDistance(), 6);

    * ray = raytracer::Ray(raytracer::Point(0.5, 0, 5), raytracer::Vector(0, 0, -1));
    EXPECT_EQ(xs[0].getDistance(), 4);
    EXPECT_EQ(xs[1].getDistance(), 6);

    * ray = raytracer::Ray(raytracer::Point(0.5, 0, -5), raytracer::Vector(0, 0, 1));
    EXPECT_EQ(xs[0].getDistance(), 4);
    EXPECT_EQ(xs[1].getDistance(), 6);

    * ray = raytracer::Ray(raytracer::Point(0, 0.5, 0), raytracer::Vector(0, 0, 1));
    EXPECT_EQ(xs[0].getDistance(), -1);
    ASSERT_EQ(xs[1].getDistance(), 1);
}


