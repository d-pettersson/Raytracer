#ifndef RTC_RAY_H
#define RTC_RAY_H

#include "tuple.h"
#include "transform.h"

#include <vector>
#include <ostream>

namespace raytracer {
class Ray {
    public:
        Ray();
        Ray(Tuple origin, Tuple direction);

        void setDirection(const Tuple& vector);
        Tuple getDirection() const;
        Tuple& getDirection();

        void setOrigin(const Tuple& point);
        Tuple getOrigin() const;
        Tuple& getOrigin();

        Tuple position(const double& t) const;

    private:
        Tuple origin_;
        Tuple direction_;
};

Ray transform(const Ray& ray, Transform& transform);

} // namespace raytracer



#endif //RTC_RAY_H
