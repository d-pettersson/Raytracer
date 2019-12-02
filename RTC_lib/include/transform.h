/**
 * The <code>Transform</code> is the child class for transformations on 3D objects.
 * Its base class is <code>Matrix</code>. It can contain multiple transformations
 * chained together.
 *
 * @param[in] const Matrix& m
 */

#ifndef RTC_TRANSFORM_H
#define RTC_TRANSFORM_H

#include "matrix.h"

namespace raytracer {

class Transform : public virtual Matrix {
    public:
        Transform();

        /**
         * Returns a <code>Transform</code> object containing (chained) transformations
         *
         * @param[in] const Matrix& m
         */
        Transform(const Matrix& m);

        /**
         * Create a translation matrix
         *
         * @param[in] const double& x
         * @param[in] const double& y
         * @param[in] const double& z
         * @return Transform&
         */
        Transform& translate(const double& x, const double& y, const double& z);

        /**
         * Create a scaling matrix
         *
         * @param[in] const double& x
         * @param[in] const double& y
         * @param[in] const double& z
         * @return Transform&
         */
        Transform& scale(const double& x, const double& y, const double& z);

        /**
         * Create a "rotation on X" matrix
         *
         * @param[in] const double& angle
         * @return Transform&
         */
        Transform& rotateX(const double& angle);

        /**
        * Create a "rotation on Y" matrix
        *
        * @param[in] const double& angle
        * @return Transform&
        */
        Transform& rotateY(const double& angle);

        /**
        * Create a "rotation on Z" matrix
        *
        * @param[in] const double& angle
        * @return Transform&
        */
        Transform& rotateZ(const double& angle);

        /**
         * Create a shearing matrix.
         * Each component moves in relation ship to the other.
         * (x in proportion to y, x to z, y to x, ...)
         *
         * @param[in] const double& xy
         * @param[in] const double& xz
         * @param[in] const double& yx
         * @param[in] const double& yz
         * @param[in] const double& zx
         * @param[in] const double& zy
         * @return Transform&
         */
        Transform& shear(const double& xy, const double& xz,
                         const double& yx, const double& yz,
                         const double& zx, const double& zy);

};

Transform viewTransform(const Tuple &from, const Tuple &to, const Tuple &up);

} // namespace raytracer


#endif //RTC_TRANSFORM_H
