#ifndef RTC_SHAPE_H
#define RTC_SHAPE_H

#include "ray.h"

#include <iostream>
#include <vector>


namespace raytracer {
class Shape {
    public:
        Shape();
        size_t id;

        std::vector<double> intersect(const Ray &ray);

        int count();

        double getIntersects(const int& index);

        double& operator[](const int &index);
        double operator[](const int &index) const;

    private:
        static size_t nextId;
        std::vector<double> intersects;


};

class Sphere : public Shape {
    public:
        Sphere();
};

bool operator==(const Shape& s1, const Shape& s2);


} // namespace raytracer


#endif //RTC_SHAPE_H
