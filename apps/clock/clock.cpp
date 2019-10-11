#include "include/tuple.h"
#include "include/transform.h"
#include "include/canvas.h"

#include <iostream>

int main() {
    auto * canvas = new raytracer::Canvas(400, 400);
    auto * color = new raytracer::Color(1.0, 0.0, 0.0);

    auto * radius = new raytracer::Point(3 * canvas->width / 8, 0.0, 0.0);

    auto * rotate = new raytracer::Transform();
    auto * translate = new raytracer::Transform();
    translate->translate(200, 200, 0.0);

    for (int i = 0; i < 12; i++) {
        rotate->rotateZ(TWOPI / 12 * i);
        raytracer::Point resultPoint = * rotate * * radius;
        resultPoint = * translate * resultPoint;
        canvas->writePixel(resultPoint.x, resultPoint.y, * color);
    }

    canvas->saveToFile();

    return 0;
}
