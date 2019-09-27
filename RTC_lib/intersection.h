#ifndef RTC_INTERSECTION_H
#define RTC_INTERSECTION_H

#include <memory>
#include <vector>

namespace raytracer {
class Shape;

class Intersection {
    public:
        Intersection();
        Intersection(double distance, std::shared_ptr<Shape const> shape);

        double getDistance();
        std::shared_ptr<Shape const> getObject();

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
