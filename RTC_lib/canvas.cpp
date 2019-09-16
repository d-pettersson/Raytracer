#include "canvas.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>

namespace raytracer {

Canvas::Canvas(size_t w, size_t h)
    :width{w}, height{h}, colors{std::vector<std::vector<Color>>(width, std::vector<Color>(height, Color(0., 0., 0.)))}
{
}

Canvas::Canvas()
    :width{0}, height{0}
{
}

void Canvas::writePixel(const int& x, const int& y, Color& color) {
    if (x < 0 || y < 0) {
        std::cerr << "x and y have to be positive";
    }
    color.r < 0 ? color.r = 0 : color.r;
    color.g < 0 ? color.g = 0 : color.g;
    color.b < 0 ? color.b = 0 : color.b;

    this->colors[x][y] = color;
}

Color Canvas::pixelAt(const int& x, const int& y) {
    if (x < 0 || y < 0) {
        std::cerr << "x and y have to be positive";
    }
    return this->colors[x][y];
}

Color Canvas::scaleColor(const Color& color, const int& maxValue) {
    auto * outputCol = new Color;
    outputCol->r = std::clamp((int)ceil(color.r * maxValue), 0, maxValue);
    outputCol->g = std::clamp((int)ceil(color.g * maxValue), 0, maxValue);
    outputCol->b = std::clamp((int)ceil(color.b * maxValue), 0, maxValue);
    return * outputCol;
}

std::string Canvas::createPPMHeader() {
    std::stringstream ss;
    ss << "P3\n" << this->width << ' ' << this->height << "\n255\n";
    std::string header = ss.str();
    ss.clear();
    return header;
}

// TODO: test ostream version of canvasToPPM
//  - limit string size to 70 chars per line
//  - remove stringstream (only there for testing purposes)

std::string Canvas::canvasToPPM() {
    std::stringstream ss;
    std::ofstream os("image.ppm", std::ofstream::binary);
    ss << createPPMHeader();
    bool first = true;
    for (int py = 0; py < this->height; py++) {
        first ? ss << "" : ss << '\n';
        for (int px = 0; px < this->width; px++) {
            auto clampedVal = this->pixelAt(px, py);
            ss << scaleColor(clampedVal, 255);
            px < this->width - 1 ? ss << " " : ss << "";
        }
        first = false;
    }
    ss << '\n';
    os << ss.rdbuf();
    os.close();
    std::string output = ss.str();
    ss.clear();
    return output;
}


}