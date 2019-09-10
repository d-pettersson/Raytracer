#ifndef RTC_PROJECTILE_H
#define RTC_PROJECTILE_H

#include "tuple.h"

class Projectile {
    public:
        Projectile(raytracer::Tuple position, raytracer::Tuple velocity);
        Projectile();

        raytracer::Tuple position;
        raytracer::Tuple velocity;
};


#endif //RTC_PROJECTILE_H
