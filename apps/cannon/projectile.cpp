#include "projectile.h"
#include "environment.h"
#include "tuple.h"

#include <sstream>

Projectile::Projectile(raytracer::Tuple pos, raytracer::Tuple vel)
    :position{pos}, velocity{vel}
{
}

Projectile::Projectile()
{
}

Projectile tick(const Environment& env, Projectile& proj) {
    proj.position = proj.position + proj.velocity;
    proj.velocity = proj.velocity + env.gravity + env.wind;
    return proj;
}

std::ostream& operator<<(std::ostream& out, const Projectile& proj) {
    out << proj.position;
    return out;
}



