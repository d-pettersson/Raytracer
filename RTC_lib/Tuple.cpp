//
// Created by David P on 06.09.19.
//

#include "Tuple.h"

Tuple::Tuple(double xx, double yy, double zz, double ww)
    :x{xx}, y{yy}, z{zz}, w{ww}
{
}

Tuple::Tuple()
    :x{0.f}, y{0.f}, z{0.f}, w{0.f}
{
}

bool Tuple::isPoint() {
    return w == 1.0;
}

bool Tuple::isVector() {
    return w == 0.0;
}