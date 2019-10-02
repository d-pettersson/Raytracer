#include "canvas.h"
#include "ray.h"
#include "tuple.h"
#include "sphere.h"
#include "intersection.h"

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
    sphere->material.color = raytracer::Color(1, 0.2, 1);
    auto * lightPosition = new raytracer::Point(-10, 10, -10);
    auto * lightColor = new raytracer::Color(1, 1, 1);
    auto * light = new raytracer::Light(* lightPosition, * lightColor);
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
            if (intersection->getDistance() > 0) {
                raytracer::Point point = ray.position(intersection->getDistance());
                raytracer::Vector normal = sphere->getNormal(point);
                raytracer::Vector eye = -ray.getDirection();
                * color = sphere->material.setPhongLighting(* light, point, eye, normal);
                canvas->writePixel(x, y, * color);
                canvas->saveToFile();
            }
        }
    }
    return 0;
}