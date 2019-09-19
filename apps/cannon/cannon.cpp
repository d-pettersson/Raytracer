#include "environment.h"
#include "projectile.h"

#include <iostream>

int main() {
    // Environment setup
    raytracer::Tuple gravity = raytracer::createVector(0., -0.1, 0);
    raytracer::Tuple wind = raytracer::createVector(-0.01, 0, 0);
    Environment env = Environment(gravity, wind);

    // Projectile setup
    raytracer::Tuple velocity = raytracer::normalize(raytracer::createVector(1, 1, 0));
    raytracer::Tuple position = raytracer::createPoint(0, 1, 0);
    Projectile proj{position, velocity};

    for (float y = 0; y < 1; y += 0.01) {
        position.y = y;
        Projectile out = tick(env, proj);
        std::cout << out << '\n';
    }


    return 0;
}
