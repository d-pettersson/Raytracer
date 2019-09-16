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
        Transform shear(const double& xy, const double& xz,
                        const double& yx, const double& yz,
                        const double& zx, const double& zy);
};

} // namespace raytracer


#endif //RTC_TRANSFORM_H
