#ifndef RTC_WORLD_H
#define RTC_WORLD_H

#include "light.h"
#include "sphere.h"
#include "tuple.h"
#include "transform.h"
#include "intersection.h"

namespace raytracer {
class World {
    public:
        World();

        void defaultWorld();

        void intersectWorld(const Ray &ray, std::vector<Intersection> * xs) const;
        Color shadeHit(const IntersectionData &intersectionData, int remaining = 5);
        Color colorAt(const Ray &ray, int remaining = 5);
        Color reflectedColor(const IntersectionData &xs, int remaining = 5);
        Color refractedColor(const IntersectionData &xs, int remaining = 5);
//        bool isShadowed(const Point &lightPosition, const Point& point) const;
        bool isShadowed(const Point& point) const;


        void addObject(const std::shared_ptr<Shape>& shape);

        Light light;
        std::vector<std::shared_ptr<Shape> > shapes;
        Transform transform;
    };
} // namespace raytracer



#endif //RTC_WORLD_H
