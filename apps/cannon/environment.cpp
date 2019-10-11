#include "environment.h"
#include "include/tuple.h"

Environment::Environment(raytracer::Tuple grav, raytracer::Tuple wi)
    :gravity{grav}, wind{wi}
{
}

Environment::Environment()
{
}
