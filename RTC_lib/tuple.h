/**
 * Raytracer
 *
 * Tuple class
 *
 * Color, Point, Vector subclass
 */
#ifndef RTC_TUPLE_H
#define RTC_TUPLE_H

#include "constants.h"

#include<iostream>

namespace raytracer {

class Tuple {
    public:
        ///
        /// \param x
        /// \param y
        /// \param z
        /// \param w
        Tuple(double x, double y, double z, double w);
        Tuple();

        bool isPoint();
        bool isVector();

        double x, y, z, w;

        double& operator()(size_t index);
        double operator()(size_t index) const;
};

class Point : virtual public Tuple {
    public:
        Point(double x, double y, double z);
        Point();
};

class Vector : virtual public Tuple {
    public:
        Vector(double x, double y, double z);
        Vector();
};

class Color : virtual public Tuple {
    public:
        Color(double r, double g, double b);
        Color();

        double r, g, b;
        int maxValue = 255;
};

Tuple createPoint(const double &x, const double &y, const double &z);
Tuple createVector(const double &x, const double &y, const double &z);

Tuple normalize(const Tuple& t1);
Tuple tupleAbs(Tuple *t1);

double magnitude(const Tuple& t1);
double dot(const Tuple& t1, const Tuple& t2);
Tuple cross(const Tuple& t1, const Tuple& t2);

bool isEqual(const Tuple &t1, const Tuple &t2);

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
