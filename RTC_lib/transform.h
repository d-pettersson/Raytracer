#ifndef RTC_TRANSFORM_H
#define RTC_TRANSFORM_H

#include "matrix.h"

namespace raytracer {

class Transform : public virtual Matrix {
    public:
        Transform();
        Transform(const Matrix& m);

        Transform translate(const double& x, const double& y, const double& z);
        Transform scale(const double& x, const double& y, const double& z);
        Transform rotateX(const double& angle);
        Transform rotateY(const double& angle);
        Transform rotateZ(const double& angle);
};

} // namespace raytracer


#endif //RTC_TRANSFORM_H
