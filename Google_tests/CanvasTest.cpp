#include "canvas.h"

#include "gtest/gtest.h"

#include <cmath>

class CanvasFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        canvas = new raytracer::Canvas();
    }

    virtual void TearDown() {
        delete canvas;
    }

    raytracer::Canvas * canvas;

    raytracer::Color * color;
    raytracer::Color c1;
    raytracer::Color c2;

    double scalar;
    double doubleResult;
};

TEST_F(CanvasFixture, TestCanvasCreation) {
    canvas = new raytracer::Canvas(10, 20);
    ASSERT_EQ(canvas->width, 10);
    ASSERT_EQ(canvas->height, 20);
    for (int i = 0; i < canvas->width; i++) {
        for (int j = 0; j < canvas->height; j++) {
            ASSERT_EQ(raytracer::Color(0.0, 0.0, 0.0), canvas->colors[i][j]);
        }
    }
}

TEST_F(CanvasFixture, WritingPixelCanvas) {
    canvas = new raytracer::Canvas(10, 20);
    c1 = raytracer::Color(1, 0, 0);
    canvas->writePixel(2, 3, c1);
    ASSERT_EQ(c1, canvas->pixelAt(2, 3));
}

TEST_F(CanvasFixture, PPMHeaderCheck) {
    canvas = new raytracer::Canvas(5, 3);
    std::string header = canvas->canvasToPpm();
    ASSERT_EQ("P3\n5 3\n255", header);
}



