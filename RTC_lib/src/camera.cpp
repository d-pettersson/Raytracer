#include "include/camera.h"

#include <cmath>

namespace raytracer {
Camera::Camera()
    : hsize_(0), vsize_(0), fieldOfView_(0.0), transform_(Transform()), pixelSize_(0.0)
{

}


Camera::Camera(int hsize, int vsize, double fieldOfView)
    : hsize_(hsize), vsize_(vsize), fieldOfView_(fieldOfView), transform_(Transform())
{
    double halfView = tan(this->fieldOfView_ / 2);
    double aspect = (double)this->hsize_ / (double)this->vsize_;
    if (aspect >= 1) {
        this->halfWidth_ = halfView;
        this->halfHeight_ = halfView / aspect;
    } else {
        this->halfWidth_ = halfView * aspect;
        this->halfHeight_ = halfView;
    }
    this->pixelSize_ = (this->halfWidth_ * 2) / (double)this->hsize_;
}

Ray Camera::rayForPixel(const int &x, const int &y) {
    double xOffset = (x + 0.5) * this->pixelSize_;
    double yOffset = (y + 0.5) * this->pixelSize_;

    double worldX = this->halfWidth_ - xOffset;
    double worldY = this->halfHeight_ - yOffset;

    auto inverseTransform = inverse(this->transform_);

    auto pixel = inverseTransform * createPoint(worldX, worldY, -1);
    auto origin = inverseTransform * createPoint(0, 0, 0);
    auto direction = normalize(pixel - origin);
    
    return Ray(origin, direction);

}

Canvas Camera::render(World * world) {
    Ray ray;
    Color color;
    Canvas image(this->hsize_, this->vsize_);

    for (int y = 0; y < this->vsize_; y++) {
        for (int x = 0; x < this->hsize_; x++) {
            ray = this->rayForPixel(x, y);
            color = world->colorAt(ray);
            image.writePixel(x, y, color);
        }
    }
    
    return image;
}
} // namespace raytracer
