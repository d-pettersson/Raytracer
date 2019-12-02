#include "include/camera.h"
#include "include/ray.h"
#include "include/canvas.h"
#include "include/world.h"

#include <cmath>

#include "gtest/gtest.h"

class CameraFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        camera = new raytracer::Camera();
        transform = new raytracer::Transform();
        ray = new raytracer::Ray();
        rotate = new raytracer::Transform();
        translate = new raytracer::Transform();
        from = new raytracer::Tuple();
        to = new raytracer::Tuple();
        up = new raytracer::Tuple();
        image = new raytracer::Canvas();
        world = new raytracer::World();
    }

    virtual void TearDown() {
        delete camera;
        delete transform;
        delete ray;
        delete rotate;
        delete translate;
        delete from;
        delete to;
        delete up;
        delete image;
        delete world;
    }

    raytracer::Camera * camera;
    raytracer::Transform * transform;
    raytracer::Transform * rotate;
    raytracer::Transform * translate;
    raytracer::Ray * ray;
    raytracer::Tuple * from;
    raytracer::Tuple * to;
    raytracer::Tuple * up;
    raytracer::Canvas * image;
    raytracer::World * world;
};

TEST_F(CameraFixture, ConstructingCamera) {
    * camera = raytracer::Camera(160, 120, PI/2);
    ASSERT_EQ(camera->hsize_, 160);
    ASSERT_EQ(camera->vsize_, 120);
    ASSERT_EQ(camera->fieldOfView_, PI/2);
    ASSERT_EQ(camera->transform_, raytracer::Transform());
}

TEST_F(CameraFixture, PixelSizeHorizontalCanvas) {
    * camera = raytracer::Camera(200, 125, PI/2);
    ASSERT_FLOAT_EQ(camera->pixelSize_, 0.01);
}

TEST_F(CameraFixture, PixelSizeVerticalCanvas) {
    * camera = raytracer::Camera(125, 200, PI/2);
    ASSERT_FLOAT_EQ(camera->pixelSize_, 0.01);
}

TEST_F(CameraFixture, RayCenterCanvas) {
    * camera = raytracer::Camera(201, 101, PI/2);
    * ray = camera->rayForPixel(100, 50);
    ASSERT_EQ(ray->getOrigin(), raytracer::createPoint(0, 0, 0));
    ASSERT_EQ(ray->getDirection(), raytracer::createVector(0, 0, -1));
}

TEST_F(CameraFixture, RayCornerCanvas) {
    * camera = raytracer::Camera(201, 101, PI/2);
    * ray = camera->rayForPixel(0, 0);
    ASSERT_EQ(ray->getOrigin(), raytracer::createPoint(0, 0, 0));
    ASSERT_EQ(ray->getDirection(), raytracer::createVector(0.66519, 0.33259, -0.66851));
}

TEST_F(CameraFixture, RayCameraTransformed) {
    * camera = raytracer::Camera(201, 101, PI/2);
    rotate->rotateY(PI/4);
    translate->translate(0, -2, 5);
    * transform = * rotate * * translate;
    camera->transform_ = * transform;
    * ray = camera->rayForPixel(100, 50);
    ASSERT_EQ(ray->getOrigin(), raytracer::createPoint(0, 2, -5));
    ASSERT_EQ(ray->getDirection(), raytracer::createVector(sqrt(2)/2, 0, -sqrt(2)/2));
}

TEST_F(CameraFixture, RenderWorldCamera) {
    world->defaultWorld();
    * camera = raytracer::Camera(11, 11, PI/2);
    * from = raytracer::createPoint(0, 0, -5);
    * to = raytracer::createPoint(0, 0, 0);
    * up = raytracer::createVector(0, 1, 0);
    camera->transform_ = viewTransform(* from, * to, * up);
    * image = camera->render(world);
    ASSERT_EQ(image->pixelAt(5, 5), raytracer::Color(0.38066, 0.47583, 0.2855));
}