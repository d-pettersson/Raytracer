#ifndef RTC_INTERSECTION_H
#define RTC_INTERSECTION_H

#include <memory>

namespace raytracer {
class Shape;

class Intersection {
    public:
        Intersection();
        Intersection(double distance, std::shared_ptr<Shape const> shape);

        double getDistance();
        std::shared_ptr<Shape const> getObject();

    private:
        double distance;
        std::shared_ptr<Shape const> shape;
};

template <typename T>
std::vector<T> intersections(T d1) {
    return std::vector<T> {d1};
}

template <typename T, typename ...Args>
std::vector<T> intersections(T d1, Args... d2) {
    return std::vector<T> {d1, d2...};

}

} // namespace raytracer



#endif //RTC_INTERSECTION_H
