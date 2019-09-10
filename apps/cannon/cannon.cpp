#include "environment.h"
#include "projectile.h"
#include "tuple.h"

#include <iostream>

Projectile tick(const Environment& env, const Projectile& proj) {
    raytracer::Tuple position = proj.position + proj.velocity;
    raytracer::Tuple velocity = proj.velocity + env.gravity + env.wind;
    Projectile projectile = Projectile(position, velocity);
    return projectile;
}


int main() {
    // Environment setup
    raytracer::Tuple gravity = raytracer::createVector(0., -0.1, 0);
    raytracer::Tuple wind = raytracer::createVector(-0.01, 0, 0);
    Environment env = Environment(gravity, wind);

    // Projectile setup
    raytracer::Tuple velocity = raytracer::normalize(raytracer::createVector(1, 1, 0));

    for (size_t y = 0; y <= 1; y+=0.01) {
        raytracer::Tuple position = raytracer::createPoint(0, y, 0);
        Projectile proj = Projectile(position, velocity);
        tick(env, proj);
    }

    return 0;
}
