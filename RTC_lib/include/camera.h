#ifndef RTC_CAMERA_H
#define RTC_CAMERA_H

#include "transform.h"
#include "ray.h"
#include "world.h"
#include "canvas.h"

namespace raytracer {
class Camera {
public:
    Camera();
    Camera(int hsize, int vsize, double fieldOfView);

    /**
    * Returns a new Ray, starting at the camera
    * passing through the indicated (x, y) pixels on the canvas
    *
    * @param[in] const int &x
    * @param[in] const int &y
    * @return Ray
    */
    Ray rayForPixel(const int &x, const int &y);

    /**
    * Renders the <code>World</class> into a Canvas
    *
    * @param[in] World &world
    * @return Canvas
    */
    Canvas render(World &world);

    int hsize;
    int vsize;

    double fieldOfView;

    Transform transform;

    double pixelSize;
    double halfWidth;
    double halfHeight;
};
} // namespace raytracer


#endif //RTC_CAMERA_H

