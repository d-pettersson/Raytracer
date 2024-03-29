/**
 * The <code>Canvas</code> class allows visual representation of our calculations.
 * It outputs a PPM file (width, height) with <code>colorDepth</code> color depth.
 *
 * @param[in] size_t width
 * @param[in] size_t height
 */

#ifndef RTC_CANVAS_H
#define RTC_CANVAS_H

#include "tuple.h"

#include <vector>

namespace raytracer {
class Canvas {
    public:
        /**
         * Creates a <code>Canvas</code> built with width and height components.
         *
         * @param[in] width
         * @param[in] height
         */
        Canvas(size_t width, size_t height);
        Canvas();

        /**
         * Writes a pixel to the <code>Canvas</code>
         *
         * @param[in] const int& x
         * @param[in] const int& y
         * @param[in] Color color
         */
        void writePixel(const int& x, const int& y, const Color &color);

        /**
         * Get the value of the pixel situated at x and y coordinates.
         *
         * @param[in] const int& x
         * @param[in] const int& y
         * @return Color
         */
        Color pixelAt(const int& x, const int& y) const;

        /**
         * Scales the <code>Color</code> values from range(0, 1) to (0, colorDepth)
         *
         * @param[in] const Color& color
         * @param[in] const int& colorDepth
         * @return Color
         */
        Color scaleColor(const Color& color, const int& colorDepth);

        /**
        * Scales the <code>Color</code> value from range(0, 1) to (0, colorDepth)
        *
        * @param[in] const double& d
        * @param[in] const int& colorDepth
        * @return int
        */
        int scaleColor(const double& d, const int& colorDepth);

        /**
         * Creates the header for the PPM file.
         *
         * @return std::string
         */
        std::string createPPMHeader();

        /**
         * Creates a PPM file from the canvas.
         */
        void saveToFile();

        size_t width, height;

        std::vector<std::vector<Color> > colors;
};

std::ostream& operator<<(std::ostream& out, const Canvas& canvas);

} // namespace raytracer

#endif //RTC_CANVAS_H
