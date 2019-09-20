#include "canvas.h"
#include "common.h"

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
    raytracer::Color c3;

    double scalar;
    double doubleResult;
};

TEST_F(CanvasFixture, TestCanvasSize) {
    canvas = new raytracer::Canvas(10, 20);
    ASSERT_EQ(canvas->width, 10);
    ASSERT_EQ(canvas->height, 20);
}

// bool operator== had to be created first, else test passes with any value

TEST_F(CanvasFixture, TestCanvasColor) {
    canvas = new raytracer::Canvas(10, 20);
    for (size_t w = 0; w < canvas->width; w++) {
        for (size_t h = 0; h < canvas->height; h++) {
            ASSERT_EQ(raytracer::Color(0., 0., 0.), canvas->colors[w][h]);
        }
    }
}

TEST_F(CanvasFixture, WritingPixelCanvas1) {
    canvas = new raytracer::Canvas(10, 20);
    c1 = raytracer::Color(1, 0, 0);
    canvas->writePixel(2, 3, c1);
    ASSERT_EQ(c1, canvas->pixelAt(2, 3));
}

TEST_F(CanvasFixture, WritingPixelCanvas2) {
    canvas = new raytracer::Canvas(5, 3);
    c1 = raytracer::Color(1.5, 0, 0);
    canvas->writePixel(0, 0, c1);
    ASSERT_EQ(c1, canvas->pixelAt(0, 0));
}

TEST_F(CanvasFixture, WritingPixelCanvas3) {
    canvas = new raytracer::Canvas(5, 3);
    c1 = raytracer::Color(0, 0.5, 0);
    canvas->writePixel(2, 1, c1);
    ASSERT_EQ(c1, canvas->pixelAt(2, 1));
}

TEST_F(CanvasFixture, PPMHeaderCheck) {
    canvas = new raytracer::Canvas(5, 3);
    std::string header = canvas->createPPMHeader();
    ASSERT_EQ("P3\n5 3\n255", header);
}

TEST_F(CanvasFixture, ScaleColorTest) {
    std::stringstream ss;
    canvas = new raytracer::Canvas(5, 3);
    c1 = raytracer::Color(1.5, 0.0, 0.0);
    canvas->writePixel(0, 0, c1);
    c2 = canvas->scaleColor(c1, 255);
    ss << c2;
    std::string output = ss.str();
    ASSERT_EQ(("255 0 0"), output);
}
//
//TEST_F(CanvasFixture, PPMPixelData) {
//    canvas = new raytracer::Canvas(5, 3);
//    c1 = raytracer::Color(1.5, 0.0, 0.0);
//    c2 = raytracer::Color(0, 0.5, 0);
//    c3 = raytracer::Color(-0.5, 0, 1);
//    canvas->writePixel(0, 0, c1);
//    canvas->writePixel(2, 1, c2);
//    canvas->writePixel(4, 2, c3);
//    std::string output = canvas->saveToFile();
//    ASSERT_EQ(("P3\n5 3\n255\n"
//                    "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
//                    "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
//                    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"), output);
//}

//TEST_F(CanvasFixture, PPMLineLength) {
//    canvas = new raytracer::Canvas(10, 2);
//    c1 = raytracer::Color(1.0, 0.8, 0.6);
//    for (size_t x = 0; x < canvas->width; x++) {
//        for (size_t y = 0; y < canvas->height; y++) {
//            canvas->writePixel(x, y, c1);
//        }
//    }
//    std::string output = canvas->saveToFile();
//    ASSERT_EQ(("255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
//                    "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
//                    "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
//                    "153 255 204 153 255 204 153 255 204 153 255 204 153\n"), output);
//}
//
//TEST_F(CanvasFixture, NewLineEOF) {
//    canvas = new raytracer::Canvas(10, 2);
//    c1 = raytracer::Color(1.0, 0.8, 0.6);
//    for (size_t x = 0; x < canvas->width; x++) {
//        for (size_t y = 0; y < canvas->height; y++) {
//            canvas->writePixel(x, y, c1);
//        }
//    }
//    std::string output = canvas->saveToFile();
//    std::string endStr = "\n";
//    bool ending = endsWith(output, endStr);
//    ASSERT_TRUE(ending);
//}


