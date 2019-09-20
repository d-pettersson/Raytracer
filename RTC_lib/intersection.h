#ifndef RTC_INTERSECTION_H
#define RTC_INTERSECTION_H

#include "shape.h"

namespace raytracer {
class Intersection {
    public:
        Intersection();
        Intersection(double t, Shape * shape);

        double t;
        Shape shape;

    private:
        std::vector<Intersection> intersectionPair;
};

class Intersections : public Intersection {
    public:
        Intersections();
        Intersections(std::vector<Intersection>& intersections);


        template<typename ... Args>
        void intersections(const Intersection& intersection, Args ... args);

    private:
        std::vector<Intersection> intersectionsColl;


};
} // namespace raytracer



#endif //RTC_INTERSECTION_H
