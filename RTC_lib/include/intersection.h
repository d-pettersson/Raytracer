#ifndef RTC_INTERSECTION_H
#define RTC_INTERSECTION_H

#include "tuple.h"
#include "ray.h"

#include <memory>
#include <vector>
#include <algorithm>

namespace raytracer {
class Shape;

struct IntersectionData {
    double distance = 0.0;
    std::shared_ptr<Shape const> object;
    Point point;
    Point overPoint;
    Point underPoint;
    Vector eye;
    Vector normal;
    Vector reflect;
    bool inside;
    bool inShadow = false;
    double n1;
    double n2;
};

class Intersection {
    public:
        Intersection();
        Intersection(double distance, std::shared_ptr<Shape const> shape);

        double getDistance() const;
        std::shared_ptr<Shape const> getObject() const;

        IntersectionData prepareComputations(const Ray &ray, const std::vector<Intersection> &xs);

        bool operator==(const Intersection &rhs) const;
        bool operator!=(const Intersection &rhs) const;

        bool operator<(const Intersection &rhs) const;
        bool operator>(const Intersection &rhs) const;
        bool operator<=(const Intersection &rhs) const;
        bool operator>=(const Intersection &rhs) const;

private:
        double distance;
        std::shared_ptr<Shape const> shape;
};

Intersection hit(std::vector<Intersection>const& h);

template <typename T>
std::vector<T> intersections(T d1) {
    std::vector<T> xs{d1};
    std::sort(xs.begin(), xs.end());
    return xs;
}

template <typename T, typename ...Args>
std::vector<T> intersections(T d1, Args... d2) {
    std::vector<T> xs{d1, d2...};
    std::sort(xs.begin(), xs.end());
    return xs;

}

} // namespace raytracer



#endif //RTC_INTERSECTION_H
