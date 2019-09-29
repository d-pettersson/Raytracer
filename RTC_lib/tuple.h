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

#include "constants.h"

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
         * Checks if <code>Tuple</code> is a Point
         *
         * @return bool
         */
        bool isPoint();

        /**
         * Checks if <code>Tuple</code> is a Vector
         *
         * @return bool
         */
        bool isVector();

        double x, y, z, w;

        double& operator()(size_t index);
        double operator()(size_t index) const;
};

/**
 * The <code>Point</code> class inherits from the <code>Tuple</code> class.
 *
 * @param[in] double x
 * @param[in] double y
 * @param[in] double z
 */
class Point : virtual public Tuple {
    public:
        Point(double x, double y, double z);
        Point();

        Point operator-();
};

/**
 * The <code>Vector</code> class inherits from the <code>Tuple</code> class.
 *
 * @param[in] double x
 * @param[in] double y
 * @param[in] double z
 */
class Vector : virtual public Tuple {
    public:
        Vector(double x, double y, double z);
        Vector();
};

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

        double r, g, b;
};

/**
 * Creates a <code>Point</code> from coordinates(x, y, z)
 *
 * @param[in] double x
 * @param[in] double y
 * @param[in] double z
 * @return Tuple{x, y, z, 1.0f}
 */
Tuple createPoint(const double &x, const double &y, const double &z);

/**
 * Creates a <code>Vector</code> from coordinates(x, y, z)
 *
 * @param[in] double x
 * @param[in] double y
 * @param[in] double z
 * @return Tuple{x, y, z, 0.0f}
 */
Tuple createVector(const double &x, const double &y, const double &z);

/**
 * Normalizes the <code>Tuple</code> coordinates
 *
 * @param[in] Tuple t1
 * @return Tuple
 */
Tuple normalize(const Tuple& t1);

/**
 * Normalizes the <code>Vector</code> coordinates
 *
 * @param[in] Vector v1
 * @return Vector
 */
Vector normalize(const Vector& v1);

    /**
 * Return the absolute value of a <code>Tuples</code>
 *
 * @param[in] Tuple t1
 * @return Tuple
 */
Tuple tupleAbs(Tuple *t1);

/**
 * Return the magnitude(length) of a <code>Tuple</code>
 *
 * @param Tuple t1
 * @return double
 */
double magnitude(const Tuple& t1);

/**
 * Return the dot product from t1 . t2
 *
 * @param[in] Tuple t1
 * @param[in] Tuple t2
 * @return double
 */
double dot(const Tuple& t1, const Tuple& t2);

/**
 * Return the cross product of t1 X t2
 *
 * @param[in] Tuple t1
 * @param[in] Tuple t2
 * @return Tuple
 */
Tuple cross(const Tuple& t1, const Tuple& t2);

/**
 * Return the reflect vector of v
 *
 * @param[in] Vector v
 * @param[in] Vector n
 * @return Vector
 */
Vector reflect(const Vector& v, const Vector& n);

/**
 * Compares two <code>Tuple</code> for equality
 *
 * @param[in] Tuple t1
 * @param[in] Tuple t2
 * @return bool
 */
bool isEqual(const Tuple& t1, const Tuple& t2);

// Tuple operators
bool operator<(const Tuple& t1, const Tuple& t2);
bool operator<(const Tuple& t1, const double& d1);
bool operator==(const Tuple& t1, const Tuple& t2);

Tuple operator-(const Tuple& t1, const Tuple& t2);
Tuple operator-(const Tuple& t1);
Tuple operator+(const Tuple& t1, const Tuple& t2);
Tuple operator*(const Tuple& t1, const double& scalar);
Tuple operator*(const Tuple& t1, const Tuple& t2);
Tuple operator/(const Tuple& t1, const double& scalar);

std::ostream& operator<<(std::ostream& out, const Tuple& t1);

// Point operators
Point operator*(const Point& p1, const Point& p2);
Point operator*(const Point& p1, const Vector& p2);
Point operator*(const Point& p1, const double& scalar);
Point operator+(const Point& p1, const Point& p2);
Point operator+(const Point& p1, const Vector& p2);
Vector operator-(const Point& p1, const Point& p2);

std::ostream& operator<<(std::ostream& out, const Point& p1);

// Vector operators
Vector operator*(const Vector& v1, const double& scalar);
Vector operator-(const Vector& v1, const Vector& v2);

// Color operators
bool operator==(const Color& c1, const Color& c2);
bool operator!=(const Color& c1, const Color& c2);

Color operator-(const Color& c1, const Color& c2);
Color operator+(const Color& c1, const Color& c2);
Color operator*(const Color& c1, const Color& c2);
Color operator*(const Color& c1, const double& scalar);

std::ostream& operator<<(std::ostream& out, const Color& c1);

} // namespace raytracer


#endif //RTC_TUPLE_H
