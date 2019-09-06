#ifndef RTC_TUPLE_H
#define RTC_TUPLE_H


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

private:

};

Tuple createPoint(double x, double y, double z);
Tuple createVector(double x, double y, double z);

Tuple tupleAbs(Tuple t1);

bool isEqual(Tuple t1, Tuple t2);

bool operator<(const Tuple& t1, const Tuple& t2);
bool operator<(const Tuple& t1, const double& d1);
bool operator==(const Tuple& t1, const Tuple& t2);

Tuple operator-(const Tuple& t1, const Tuple& t2);
Tuple operator+(const Tuple& t1, const Tuple& t2);

#endif //RTC_TUPLE_H
