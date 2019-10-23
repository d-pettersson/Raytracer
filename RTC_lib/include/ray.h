#ifndef RTC_RAY_H
#define RTC_RAY_H

//#include "tuple.h"
#include "transform.h"

#include <vector>
#include <ostream>

namespace raytracer {
class Ray {
    public:
        Ray();
        Ray(const Point &_origin, const Vector &_direction);

        void setDirection(const Vector& vector);
        Vector getDirection() const;
        Vector& getDirection();

        void setOrigin(const Point& point);
        Point getOrigin() const;
        Point& getOrigin();

        Point position(const double& t) const;

    private:
        Point origin;
        Vector direction;
};

Ray transform(const Ray& ray, Transform& t);

} // namespace raytracer



#endif //RTC_RAY_H
