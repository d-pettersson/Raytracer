#include "canvas.h"
#include "tuple.h"
#include "constants.h"

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

Color Canvas::scaleColor(const Color& color, const int& colorDepth) {
    auto * outputCol = new Color;
    outputCol->r = std::clamp((int)ceil(color.r * colorDepth), 0, colorDepth);
    outputCol->g = std::clamp((int)ceil(color.g * colorDepth), 0, colorDepth);
    outputCol->b = std::clamp((int)ceil(color.b * colorDepth), 0, colorDepth);
    return * outputCol;
}

int Canvas::scaleColor(const double& d, const int& colorDepth) {
    return std::clamp((int)ceil(d * colorDepth), 0, colorDepth);
}

std::string Canvas::createPPMHeader() {
    std::stringstream ss;
    ss << "P3\n" << this->width << ' ' << this->height << "\n255\n";
    std::string header = ss.str();
    ss.clear();
    return header;
}

// TODO: test ostream version of canvasToPPM
//  - remove stringstream (only there for testing purposes)

std::string Canvas::canvasToPPM() {
    int counter = 0;
    std::stringstream ss;
    std::ofstream os("image.ppm", std::ofstream::binary);
//    ss << createPPMHeader();
    bool first = true;
    for (int py = 0; py < this->height; py++) {
        first ? ss << "" : ss << '\n';
        counter = 0;
        for (int px = 0; px < this->width; px++) {
            auto pixelVal = this->pixelAt(px, py);
            for (int rgb = 0; rgb < 3; rgb++) {
                counter += 4;
                if (counter <= 70) {
                    ss << ' ';
                } else {
                    ss << '\n';
                    counter = 0;
                }
                ss << scaleColor(pixelVal(rgb), colorDepth);
            }
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