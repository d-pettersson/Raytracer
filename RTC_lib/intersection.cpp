#include "intersection.h"

namespace raytracer {
    Intersection::Intersection()
        : t(0.0), shape{}, intersectionPair{}
    {
    }

    Intersection::Intersection(double tt, Shape * s)
        : t(tt), shape{* s}, intersectionPair(0)
    {
    }

    Intersections::Intersections()
        : intersectionsColl{0}
    {
    }

    Intersections::Intersections(std::vector<Intersection>& intersections)
        : intersectionsColl{intersections}
    {
    }

    template<typename ... Args>
    void Intersections::intersections(const Intersection& intersection, Args ... args)
    {
        ((* this).intersectionsColl.push_back(args), ...);
    }


} // namespace raytracer
