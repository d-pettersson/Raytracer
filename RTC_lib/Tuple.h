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


#endif //RTC_TUPLE_H
