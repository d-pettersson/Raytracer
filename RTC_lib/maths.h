//
// Created by David P on 10.09.19.
//

#ifndef RTC_MATHS_H
#define RTC_MATHS_H
namespace raytracer {

    // number of digits in object
    template <class T>
    T numDigits(T number)
    {
        int digits = 0;
        if (number < 0) {
            digits = 1;
        }
        while (number) {
            number /= 10;
            digits++;
        }
        return digits;
    }
}


#endif //RTC_MATHS_H
