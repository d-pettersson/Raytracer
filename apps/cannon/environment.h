#ifndef RTC_ENVIRONMENT_H
#define RTC_ENVIRONMENT_H

#include "tuple.h"

class Environment {
    public:
        Environment(raytracer::Tuple gravity, raytracer::Tuple wind);
        Environment();

        raytracer::Tuple gravity;
        raytracer::Tuple wind;
};


#endif //RTC_ENVIRONMENT_H
