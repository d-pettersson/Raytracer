#ifndef RTC_CANVAS_H
#define RTC_CANVAS_H

#include "Tuple.h"

#include <vector>

namespace raytracer {
class Canvas {
    public:
        Canvas(int width, int height);
        Canvas();

        void writePixel(const int& x, const int& y, const Color& color);
        Color pixelAt(const int& x, const int& y);
        void canvasToPpm();

        int width;
        int height;

        std::vector<std::vector<Color>> colors;
};
} // namespace raytracer

#endif //RTC_CANVAS_H
