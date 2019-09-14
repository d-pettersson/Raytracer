#ifndef RTC_TUPLE_H
#define RTC_TUPLE_H

#include<iostream>

namespace raytracer {

class Tuple {
    public:
        Tuple(double x, double y, double z, double w);
        Tuple();

        bool isPoint();
        bool isVector();

        double x;
        double y;
        double z;
        double w;

        double& operator()(size_t index);
        double operator()(size_t index) const;

};

class Color : public Tuple {
    public:
        Color(double r, double g, double b);
        Color();

        double r;
        double g;
        double b;
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

// tuple operators
bool operator<(const Tuple& t1, const Tuple& t2);
bool operator<(const Tuple& t1, const double& d1);
bool operator==(const Tuple& t1, const Tuple& t2);

Tuple operator-(const Tuple& t1, const Tuple& t2);
Tuple operator-(const Tuple& t1);
Tuple operator+(const Tuple& t1, const Tuple& t2);
Tuple operator*(const Tuple& t1, const double& scalar);
Tuple operator/(const Tuple& t1, const double& scalar);

std::ostream& operator<<(std::ostream& out, const Tuple& t1);

// Color operators
bool operator==(const Color& c1, const Color& c2);

Color operator-(const Color& c1, const Color& c2);
Color operator+(const Color& c1, const Color& c2);
Color operator*(const Color& c1, const Color& c2);
Color operator*(const Color& c1, const double& scalar);

std::ostream& operator<<(std::ostream& out, const Color& c1);

} // namespace raytracer


#endif //RTC_TUPLE_H
