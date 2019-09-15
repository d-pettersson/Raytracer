#ifndef RTC_TRANSFORM_H
#define RTC_TRANSFORM_H

#include "tuple.h"
#include "matrix.h"

namespace raytracer {
class Transform {
    public:
        Transform();

        Transform(double x, double y, double z);

        Matrix translation(const double& x, const double& y, const double& z);
        Matrix translation(const Transform& t);

        Tuple operator*(const Tuple& tup);
        Point operator*(const Transform& trans);

        double x, y, z;

    private:
    };

    std::ostream& operator<<(std::ostream& out, const Transform& t1);

} // namespace raytracer


#endif //RTC_TRANSFORM_H
