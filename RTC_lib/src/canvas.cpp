#include "include/canvas.h"
#include "include/tuple.h"
#include "include/constants.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>

// TODO: rewrite canvas data type to std::vector<Color> for performance

namespace raytracer {

Canvas::Canvas(size_t w, size_t h)
        : width{w}, height{h}, colors{std::vector<std::vector<Color>>(width, std::vector<Color>(height, Color(0., 0., 0.)))}
{
}

Canvas::Canvas()
        : width{0}, height{0}
{
}

Color Canvas::scaleColor(const Color &color, const int &colorDepth) {
    auto * outputCol = new Color();
    
    outputCol->r_ = std::clamp((int) ceil(color.r_ * colorDepth), 0, colorDepth);
    outputCol->g_ = std::clamp((int) ceil(color.g_ * colorDepth), 0, colorDepth);
    outputCol->b_ = std::clamp((int) ceil(color.b_ * colorDepth), 0, colorDepth);
    
    return * outputCol;
}

int Canvas::scaleColor(const double &d, const int &colorDepth) {
    return std::clamp((int) ceil(d * colorDepth), 0, colorDepth);
}

void Canvas::writePixel(const int& x, const int& y, const Color &color) {
    Color temp = color;
    if (x < 0 || y < 0) {
        std::cerr << "x_ and y_ have to be positive";
    }
    temp.r_ < 0 ? temp.r_ = 0 : temp.r_;
    temp.g_ < 0 ? temp.g_ = 0 : temp.g_;
    temp.b_ < 0 ? temp.b_ = 0 : temp.b_;

    this->colors[x][y] = temp;
}

Color Canvas::pixelAt(const int& x, const int& y) const {
    if (x < 0 || y < 0) {
        std::cerr << "x_ and y_ have to be positive";
    }
    
    return this->colors[x][y];
}

std::string Canvas::createPPMHeader() {
    std::stringstream ss;
    ss << "P3\n" << this->width << ' ' << this->height << "\n255\n";
    std::string header = ss.str();
    ss.clear();
    return header;
}

// TODO: test ostream version of saveToFile
//  - remove stringstream (only there for testing purposes)

//std::string Canvas::saveToFile() {
//    int counter = 0;
//    std::stringstream ss;
//    std::ofstream os("image.ppm", std::ofstream::binary);
//    ss << createPPMHeader();
//    bool first = true;
//    for (int py = 0; py < this->height; py++) {
//        first ? ss << "" : ss << '\n';
//        counter = 0;
//        for (int px = 0; px < this->width; px++) {
//            auto pixelVal = this->pixelAt(px, py);
//            for (int rgb = 0; rgb < 3; rgb++) {
//                counter += 4;
//                if (counter <= 70) {
//                    ss << ' ';
//                } else {
//                    ss << '\n';
//                    counter = 0;
//                }
//                ss << scaleColor(pixelVal(rgb), colorDepth);
//            }
//        }
//        first = false;
//    }
//    ss << '\n';
//    os << ss.rdbuf();
//    os.close();
//    std::string output = ss.str();
//    ss.clear();
//    return output;
//}

void Canvas::saveToFile() {
    int counter = 0;
    Color pixelVal;
    std::ofstream os("image.ppm", std::ofstream::binary);
    os << createPPMHeader();
    bool first = true;
    for (size_t py = 0; py < this->height; py++) {
        first ? os << "" : os << '\n';
        counter = 0;
        for (size_t px = 0; px < this->width; px++) {
            pixelVal = this->pixelAt(px, py);
            for (int rgb = 0; rgb < 3; rgb++) {
                counter += 4;
                if (counter <= 70) {
                    os << ' ';
                } else {
                    os << '\n';
                    counter = 0;
                }
                os << scaleColor(pixelVal(rgb), colorDepth);
            }
        }
        first = false;
    }
    os << '\n';
    os.close();
}

std::ostream& operator<<(std::ostream& out, const Canvas& canvas) {
    for (int i = 0; i < canvas.width; i++) {
        for (int j = 0; j < canvas.height; j++) {
            out << "pixel: " << canvas.pixelAt(i, j) << ' ';
        }
        out << '\n';
    }
    
    return out;
}

} // namespace raytracer