#include "projectile.h"
#include "tuple.h"

#include <sstream>

Projectile::Projectile(raytracer::Tuple pos, raytracer::Tuple vel)
    :position{pos}, velocity{vel}
{
}

Projectile::Projectile()
{
}

std::ostream& operator<<(std::ostream& out, const Projectile& proj) {
    out << proj.velocity << " " << proj.position;
    return out;
}



