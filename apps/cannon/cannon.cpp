#include "environment.h"
#include "projectile.h"

#include <iostream>

void tick(const Environment& env, Projectile& proj) {
    raytracer::Tuple position = proj.position + proj.velocity;
    raytracer::Tuple velocity = proj.velocity + env.gravity + env.wind;
    proj.position = position;
    proj.velocity = velocity;
}


int main() {
    // Environment setup
    raytracer::Tuple gravity = raytracer::createVector(0., -0.1, 0);
    raytracer::Tuple wind = raytracer::createVector(-0.01, 0, 0);
    Environment env = Environment(gravity, wind);

    // Projectile setup
    raytracer::Tuple position = raytracer::createPoint(0, 1, 0);
    raytracer::Tuple velocity = raytracer::normalize(raytracer::createVector(1, 1, 0));
    Projectile proj = Projectile(position, velocity);

    for (float y = 0; y < 1; y+=0.01) {
        position.y = y;
        tick(env, proj);
        std::cout << proj << '\n';
    }

    return 0;
}
