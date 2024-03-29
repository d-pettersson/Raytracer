#include "include/canvas.h"
#include "include/ray.h"
#include "include/tuple.h"
#include "include/sphere.h"
#include "include/intersection.h"

double wallZ = 10;
double wallSize = 7.0;

int canvasPixels = 100;
double pixelSize = wallSize / canvasPixels;
double half = wallSize / 2;

int main() {
    auto rayOrigin = raytracer::Point(0, 0, -5);

    auto * canvas = new raytracer::Canvas(canvasPixels, canvasPixels);
    auto * color = new raytracer::Color(1, 0, 0);
    std::shared_ptr<raytracer::Shape> sphere = std::make_shared<raytracer::Sphere>();
    auto * intersection = new raytracer::Intersection();

    for (int y = 0; y < canvasPixels; y++) {
        double worldY = half - pixelSize * y;
        for (int x = 0; x < canvasPixels; x++) {
            double worldX = -half + pixelSize * x;
            raytracer::Point position = raytracer::Point(worldX, worldY, wallZ);
            raytracer::Vector normalized = normalize(position - rayOrigin);
            raytracer::Ray ray = raytracer::Ray(rayOrigin, normalized);
            std::vector<raytracer::Intersection> xs;
            sphere->intersect(ray, xs);
            * intersection = hit(xs);
            if(intersection->getDistance() > 0) {
                canvas->writePixel(x, y, * color);
                canvas->saveToFile();
            }
        }
    }
    return 0;
}