#include "environment.h"
#include "projectile.h"
#include "include/canvas.h"

#include <iostream>

int main() {
    // Environment setup
    raytracer::Tuple gravity = raytracer::createVector(0., -0.1, 0);
    raytracer::Tuple wind = raytracer::createVector(-0.01, 0, 0);
    Environment env = Environment(gravity, wind);

    // Projectile setup
    raytracer::Tuple position = raytracer::createPoint(0, 1, 0);
    raytracer::Tuple velocity = raytracer::normalize(raytracer::createVector(1, 1.8, 0)) * 11.25;
    Projectile proj = Projectile(position, velocity);

    // Canvas setup
    auto * canvas = new raytracer::Canvas(900, 500);
    auto color = raytracer::Color(1.0, 0.0, 0.0);

    double counter = 0.0;
    for (int y = 0; y < 197; y++) {
        counter += 0.01;
        position.y = counter;
        Projectile out = tick(env, proj);
        for (int i = 0; i < canvas->width; i++) {
            for (int j = 0; j < canvas->height; j++) {
                canvas->writePixel((int)out.position.x, (int)(canvas->height - out.position.y), color);
            }
        }
    }
    canvas->canvasToPPM();

    return 0;
}