#ifndef RTC_SHAPE_H
#define RTC_SHAPE_H

#include "ray.h"
#include "transform.h"
#include "intersection.h"
#include "material.h"

#include <iostream>
#include <vector>
#include <memory>


namespace raytracer {
class Shape : public std::enable_shared_from_this<Shape> {
    public:
        Shape();
        virtual ~Shape();

        virtual void createGlass() = 0;

        virtual void intersect(const Ray &ray, std::vector<Intersection>& xs) const = 0;
        virtual Vector getNormal(Point worldPoint) const = 0;

        Transform getTransform() const;
        void setTransform(const Transform& t);

        size_t id;
        Material material;

    protected:
        static size_t nextId;

    private:
        std::shared_ptr<Shape> shapePtr;
        Transform transformMat;

};

bool operator==(const Shape& s1, const Shape& s2);


} // namespace raytracer


#endif //RTC_SHAPE_H
