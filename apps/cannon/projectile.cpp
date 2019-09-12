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
    Projectile output = Projectile(proj.position, proj.velocity);
    output.position = output.position + output.velocity;
    output.velocity = output.velocity + env.gravity + env.wind;
    return output;
}

std::ostream& operator<<(std::ostream& out, const Projectile& proj) {
    out << proj.position;
    return out;
}



