#include "projectile.h"
#include "tuple.h"

Projectile::Projectile(raytracer::Tuple pos, raytracer::Tuple vel)
    :position{pos}, velocity{vel}
{
}

Projectile::Projectile()
{
}

