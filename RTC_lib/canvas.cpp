#include "canvas.h"
#include "tuple.h"

#include <vector>
#include <iostream>
#include <fstream>

namespace raytracer {

Canvas::Canvas(size_t w, size_t h)
    :width{w}, height{h}
{
    colors = std::vector<std::vector<Color>>(width, std::vector<Color>(height, Color(0., 0., 0.)));
}

Canvas::Canvas()
    :width{0}, height{0}
{

}

void Canvas::writePixel(const int& x, const int& y, const Color& color) {
    if (x < 0 || y < 0) {
        std::cerr << "x and y have to be positive";
    }
    colors[x][y] = color;
}

Color Canvas::pixelAt(const int& x, const int& y) {
    if (x < 0 || y < 0) {
        std::cerr << "x and y have to be positive";
    }
    return colors[x][y];
}


std::string Canvas::canvasToPpm() {
    std::string header = "P3\n5 3\n255";
    unsigned int * ppmContent[width][height];
    for (size_t px = 0; px < width; px++) {
        for (size_t py = 0; py < height; py++) {

        }
    }
    return header;
}


}