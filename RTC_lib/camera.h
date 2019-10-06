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

    Ray rayForPixel(const int &x, const int &y);
    Canvas render(World& world);

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

