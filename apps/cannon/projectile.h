#ifndef RTC_PROJECTILE_H
#define RTC_PROJECTILE_H

#include "tuple.h"
#include "environment.h"

#include <sstream>

class Projectile {
    public:
        Projectile(raytracer::Tuple position, raytracer::Tuple velocity);
        Projectile();

        raytracer::Tuple position;
        raytracer::Tuple velocity;
};

std::ostream& operator<<(std::ostream& out, const Projectile& proj);

Projectile tick(const Environment& env, Projectile& proj);


#endif //RTC_PROJECTILE_H
