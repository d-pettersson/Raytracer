#include "Canvas.h"
#include "Tuple.h"

#include <vector>
#include <iostream>

namespace raytracer {

Canvas::Canvas(int w, int h)
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

void canvasToPpm() {

}


}