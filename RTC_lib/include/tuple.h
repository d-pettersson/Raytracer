/**
 * The <code>Tuple</code> class is the base for all calculations inside the engine.
 *
 * @param[in] double x
 * @param[in] double y
 * @param[in] double z
 * @param[in] double w
 */

#ifndef RTC_TUPLE_H
#define RTC_TUPLE_H

#include "include/constants.h"

#include <iostream>

namespace raytracer {

class Tuple {
    public:
        /**
         * Returns a <code>Tuple</code> object from the components
         *
         * @param[in] double x
         * @param[in] double y
         * @param[in] double z
         * @param[in] double w
         */
        Tuple(double x, double y, double z, double w);
        Tuple();

        /**
         * Checks if <code>Tuple</code> is a point
         *
         * @return bool
         */
        bool isPoint();

        /**
         * Checks if <code>Tuple</code> is a vector
         *
         * @return bool
         */
        bool isVector();

        double x_, y_, z_, w_;

        double& operator()(size_t index);
        double operator()(size_t index) const;
        Tuple operator-();
};
//
/**
 * The <code>Color</code> class inherits from the <code>Tuple</code> class.
 * Its @param w is hidden from view
 *
 * @param[in] double r
 * @param[in] double g
 * @param[in] double b
 */
class Color : virtual public Tuple {
    public:
        Color(double r, double g, double b);
        Color();

        double r_, g_, b_;
};

/**
 * Creates a point from coordinates(x, y, z)
 *
 * @param[in] const double &x
 * @param[in] const double &y
 * @param[in] const double &z
 * @return Tuple{x, y, z, 1.0}
 */
Tuple createPoint(const double &x, const double &y, const double &z);

/**
 * Creates a vector from coordinates(x, y, z)
 *
 * @param[in] const double &x
 * @param[in] const double &y
 * @param[in] const double &z
 * @return Tuple{x, y, z, 0.0}
 */
Tuple createVector(const double &x, const double &y, const double &z);

/**
 * Normalizes the <code>Tuple</code> coordinates
 *
 * @param[in] const Tuple &t
 * @return Tuple
 */
Tuple normalize(const Tuple& t);

/**
 * Return the absolute value of a <code>Tuples</code>
 *
 * @param[in] const Tuple &t
 * @return Tuple
 */
Tuple abs(const Tuple &t);

/**
 * Return the magnitude(length) of a <code>Tuple</code>
 *
 * @param const Tuple &v
 * @return double
 */
double magnitude(const Tuple& v);

/**
 * Return the dot product from v1 . v2
 *
 * @param[in] const Tuple &v1
 * @param[in] const Tuple &v2
 * @return double
 */
double dot(const Tuple& v1, const Tuple& v2);

/**
 * Return the cross product of v1 X v2
 *
 * @param[in] const Tuple &v1
 * @param[in] const Tuple &v2
 * @return Tuple
 */
Tuple cross(const Tuple &v1, const Tuple &v2);

/**
 * Return the reflect vector of v
 *
 * @param[in] const Tuple &v
 * @param[in] const Tuple &n
 * @return Tuple
 */
Tuple reflect(const Tuple& v, const Tuple& n);

// Tuple operators
bool operator<(const Tuple& t1, const Tuple& t2);
bool operator<(const Tuple& t1, const double& d1);
bool operator==(const Tuple& t1, const Tuple& t2);
bool operator!=(const Tuple& t1, const Tuple& t2);

Tuple operator-(const Tuple& t1, const Tuple& t2);
Tuple operator-(const Tuple& t1);
Tuple operator+(const Tuple& t1, const Tuple& t2);
Tuple operator*(const Tuple& t1, const double& scalar);
Tuple operator*(const Tuple& t1, const Tuple& t2);
Tuple operator/(const Tuple& t1, const double& scalar);

std::ostream& operator<<(std::ostream& out, const Tuple& t1);

// Color operators
bool operator==(const Color& c1, const Color& c2);
bool operator!=(const Color& c1, const Color& c2);

Color operator-(const Color& c1, const Color& c2);
Color operator+(const Color& c1, const Color& c2);
Color operator*(const Color& c1, const Color& c2);
Color operator*(const Color& c1, const double& scalar);
Color operator/(const Color& c1, const double& scalar);

std::ostream& operator<<(std::ostream& out, const Color& c1);

} // namespace raytracer


#endif //RTC_TUPLE_H
