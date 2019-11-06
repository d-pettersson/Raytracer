#include "include/camera.h"

#include <utility>
#include <cmath>
#include <omp.h>

namespace raytracer {
Camera::Camera()
    : hsize(0), vsize(0), fieldOfView(0.0), transform(Transform()), pixelSize(0.0)
{

}


Camera::Camera(int hsize, int vsize, double fieldOfView)
    : hsize(hsize), vsize(vsize), fieldOfView(fieldOfView), transform(Transform())
{
    double halfView = tan(this->fieldOfView / 2);
    double aspect = (double)this->hsize / (double)this->vsize;
    if (aspect >= 1) {
        this->halfWidth = halfView;
        this->halfHeight = halfView / aspect;
    } else {
        this->halfWidth = halfView * aspect;
        this->halfHeight = halfView;
    }
    this->pixelSize = (this->halfWidth * 2) / (double)this->hsize;
}

Ray Camera::rayForPixel(const int &x, const int &y) {
    double xOffset = (x + 0.5) * this->pixelSize;
    double yOffset = (y + 0.5) * this->pixelSize;

    double worldX = this->halfWidth - xOffset;
    double worldY = this->halfHeight - yOffset;

    auto inverseTransform = inverse(this->transform);

    Point pixel = inverseTransform * Point(worldX, worldY, -1);
    Point origin = inverseTransform * Point(0, 0, 0);
    Vector direction = normalize(pixel - origin);
    
    return Ray(origin, direction);

}

Canvas Camera::render(World& world) {
    Ray ray;
    Color color;
    Canvas image(this->hsize, this->vsize);

    for (int y = 0; y < this->vsize; y++) {
        for (int x = 0; x < this->hsize; x++) {
            ray = this->rayForPixel(x, y);
            color = world.colorAt(ray);
            image.writePixel(x, y, color);
        }
    }
    
    return image;
}
} // namespace raytracer
