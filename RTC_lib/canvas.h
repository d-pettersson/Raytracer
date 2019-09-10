#ifndef RTC_CANVAS_H
#define RTC_CANVAS_H

#include "tuple.h"

#include <vector>

namespace raytracer {
class Canvas {
    public:
        Canvas(size_t width, size_t height);
        Canvas();

        void writePixel(const int& x, const int& y, const Color& color);
        Color pixelAt(const int& x, const int& y);
        std::string canvasToPpm();

        size_t width, height;

        std::vector<std::vector<Color>> colors;
};

} // namespace raytracer

#endif //RTC_CANVAS_H
